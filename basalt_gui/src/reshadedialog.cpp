#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>
#include <limits>

#include "ignorewheeleventfilter.hpp"
#include "effect_codegen.hpp"
#include "effect_parser.hpp"
#include "effect_preprocessor.hpp"
#include "reshadedialog.hpp"
#include "ui_reshadedialog.h"

ReshadeDialog::ReshadeDialog(nlohmann::json& j, QString* n, QString* d, QWidget* parent) :
    QDialog(parent), ui(new Ui::ReshadeDialog), json(j), name(n), desc(d), mdl(&defs, this)
{
    ui->setupUi(this);
    ui->defsView->setModel(&mdl);

    connect(ui->fileSelect, SIGNAL(clicked(bool)), this, SLOT(fileButtonPressed()));
    connect(ui->fileValue, SIGNAL(textChanged(QString)), this, SLOT(filePathChanged(QString)));
    connect(&mdl, SIGNAL(changed()), this, SLOT(saveDefs()));
    connect(ui->add, SIGNAL(clicked(bool)), this, SLOT(addDefine()));
    connect(ui->del, SIGNAL(clicked(bool)), this, SLOT(delDefine()));

    nlohmann::json& reshade_effect = getReshadeEffect();
    if (reshade_effect.contains("path") && reshade_effect["path"].is_string())
        ui->fileValue->setText(getReshadeEffect()["path"]);
    else
        reshade_effect["path"] = "";
}

ReshadeDialog::~ReshadeDialog()
{
    delete ui;
}

nlohmann::json& ReshadeDialog::getReshadeEffect()
{
    if (json.contains("reshade_effects") && json["reshade_effects"].is_object())
    {
        nlohmann::json& reshade_effects = json["reshade_effects"];
        if (!(reshade_effects.contains(name->toStdString()) && reshade_effects[name->toStdString()].is_object()))
            reshade_effects[name->toStdString()] = nlohmann::json::object({{"path", ""}, {"options", nlohmann::json::object()}});
    }
    else
        json["reshade_effects"] = nlohmann::json::object({{name->toStdString(), nlohmann::json::object()}});
    return json["reshade_effects"][name->toStdString()];
}

nlohmann::json& ReshadeDialog::getOptions()
{
    nlohmann::json& effCfg = getReshadeEffect();

    if (!(effCfg.contains("options") && effCfg["options"].is_object()))
        effCfg["options"] = nlohmann::json::object();

    return json["reshade_effects"][name->toStdString()]["options"];
}

nlohmann::json& ReshadeDialog::getOption(const QString& optname)
{
    return getOption(optname.toStdString());
}

nlohmann::json& ReshadeDialog::getOption(const std::string& optname)
{
    if (!(getOptions().contains(optname) && !getOptions()[optname].is_null()))
        getOptions()[optname] = nlohmann::json();

    return getOptions()[optname];
}

void ReshadeDialog::fileButtonPressed()
{
    QFileDialog dlg(this, tr("Select effect file"));
    dlg.setNameFilters({"Reshade shder file (*.fx)", "Any files (*)"});
    dlg.setFileMode(QFileDialog::ExistingFile);

    if (dlg.exec())
    {
        ui->fileValue->setText(dlg.selectedFiles().at(0));
        getReshadeEffect()["path"] = dlg.selectedFiles().at(0);
    }
}

void ReshadeDialog::filePathChanged(const QString& text)
{
    getReshadeEffect()["path"] = text;
    parseEffect();
}

void ReshadeDialog::parseEffect()
{
    if (json.contains("reshade_effects") && json["reshade_effects"].is_object())
    {
        nlohmann::json& reshade_effects = json["reshade_effects"];
        if (reshade_effects.contains(name->toStdString()) && reshade_effects[name->toStdString()].is_object())
        {
            nlohmann::json& effJ = reshade_effects[name->toStdString()];
            if (effJ.contains("path") && effJ["path"].is_string())
                generateWidgets(effJ["path"]);
            else
            {
                effJ["path"] = "";
                deleteWidgets();
            }
        }
        else
        {
            reshade_effects[name->toStdString()] = nlohmann::json::object({{"path", ""}});
            deleteWidgets();
        }
    }
    else
    {
        json["reshade_effects"] = nlohmann::json::object({{*name, nlohmann::json::object({{"path", ""}})}});
        deleteWidgets();
    }
}

void ReshadeDialog::deleteWidgets()
{
    for (QObject* o : objsToDelete)
        o->deleteLater();

    objsToDelete.clear();
    defs.clear();
    mdl.update();
}

void ReshadeDialog::generateWidgets(QString path)
{
    deleteWidgets();

    reshadefx::preprocessor preprocessor;
    preprocessor.add_macro_definition("__RESHADE__", std::to_string(INT_MAX));
    preprocessor.add_macro_definition("__RESHADE_PERFORMANCE_MODE__", "1");
    preprocessor.add_macro_definition("__RENDERER__", "0x20000");
    preprocessor.add_macro_definition("BUFFER_WIDTH", "1920");
    preprocessor.add_macro_definition("BUFFER_HEIGHT", "1080");
    preprocessor.add_macro_definition("BUFFER_RCP_WIDTH", "(1.0 / BUFFER_WIDTH)");
    preprocessor.add_macro_definition("BUFFER_RCP_HEIGHT", "(1.0 / BUFFER_HEIGHT)");
    preprocessor.add_macro_definition("BUFFER_COLOR_DEPTH", "10");

    nlohmann::json& reshade_effect = getReshadeEffect();

    try
    {
        std::map<std::string, std::string> stddefs = reshade_effect["defs"];
        for (auto const& [key, value] : stddefs)
        {
            defs[key.c_str()] = value.c_str();
            if (value == "%{[(!undef!)]}%")
                preprocessor.remove_macro_definition(key);
            else
                preprocessor.add_macro_definition(key, value);
        }
        mdl.update();
    }
    catch (const std::exception& e)
    {
        reshade_effect["defs"] = nlohmann::json::object();
    }

    if (json.contains("reshadeIncludePath") && json["reshadeIncludePath"].is_array())
    {
        nlohmann::json& reshadeIncludePath = json["reshadeIncludePath"];
        for (const std::string& includePath : reshadeIncludePath)
            preprocessor.add_include_path(includePath);
    }

    if (!preprocessor.append_file(path.toStdString()))
        return;

    reshadefx::parser parser;

    std::string errors = preprocessor.errors();
    if (!errors.empty())
        return;

    std::unique_ptr<reshadefx::codegen> codegen(reshadefx::create_codegen_spirv(true, true, true, true));
    parser.parse(std::move(preprocessor.output()), codegen.get());

    errors = parser.errors();
    if (!errors.empty())
        return;

    reshadefx::module module;
    codegen->write_result(module);

    *desc = tr("Reshade effect %1:\n\tPath: %2\n").arg(*name, path);

    for (const reshadefx::technique_info& t : module.techniques)
    {
        desc->append(tr("\tTechnique '%1':\n").arg(t.name.c_str()));

        for (const reshadefx::annotation& a : t.annotations)
            desc->append(QString("\t\t%1: %2\n").arg(a.name.c_str(), a.value.string_data.c_str()));
    }

    for (const reshadefx::uniform_info& param : module.spec_constants)
    {
        //    bool ui_category_closed = false;
        QString        ui_category;
        QList<QString> ui_items;
        QString        ui_label;
        double         ui_max = std::numeric_limits<int>::max();
        double         ui_min = std::numeric_limits<int>::min();
        //    int ui_spacing = 0;
        double  ui_step = 0.1f;
        QString ui_text;
        QString ui_tooltip;
        QString ui_type;

        for (const reshadefx::annotation& a : param.annotations)
        {
            //            if(a.name == "ui_category_closed")
            //              ui_category_closed = a.value.as_int[0];
            //            else
            if (a.name == "ui_category")
                ui_category = QString::fromStdString(a.value.string_data);
            else if (a.name == "ui_items")
            {
                ui_items = QString::fromStdString(a.value.string_data).split('\0');
                if (ui_items.last().isEmpty())
                    ui_items.pop_back();
            }
            else if (a.name == "ui_label")
                ui_label = QString::fromStdString(a.value.string_data);
            else if (a.name == "ui_max")
                ui_max = a.type.base == reshadefx::type::t_int ? a.value.as_int[0] : a.value.as_float[0];
            else if (a.name == "ui_min")
                ui_min = a.type.base == reshadefx::type::t_int ? a.value.as_int[0] : a.value.as_float[0];
            //      else if(a.name == "ui_spacing")
            //        ui_spacing = a.value.as_int[0];
            else if (a.name == "ui_step")
                ui_step = a.type.base == reshadefx::type::t_int ? a.value.as_int[0] : a.value.as_float[0];
            else if (a.name == "ui_text")
                ui_text = QString::fromStdString(a.value.string_data);
            else if (a.name == "ui_tooltip")
                ui_tooltip = QString::fromStdString(a.value.string_data);
            else if (a.name == "ui_type")
                ui_type = QString::fromStdString(a.value.string_data);
        }

        QGroupBox* grpbox = new QGroupBox(this);
        ui->verticalLayout_2->addWidget(grpbox);
        objsToDelete.append(grpbox);

        grpbox->setTitle((ui_category.isEmpty() ? QString() : '[' + ui_category + "] ") + (ui_label.isEmpty() ? QString() : ui_label + ' ') + '{'
                         + QString::fromStdString(param.name) + '}');
        grpbox->setToolTip(ui_tooltip);

        if (ui_min != std::numeric_limits<int>::min())
            grpbox->setToolTip(tr("Min: %1\n").arg(ui_min) + grpbox->toolTip());
        if (ui_max != std::numeric_limits<int>::max())
            grpbox->setToolTip(tr("Max: %1\n").arg(ui_max) + grpbox->toolTip());

        QVBoxLayout* layout = new QVBoxLayout(grpbox);
        objsToDelete.append(layout);

        if (!ui_text.isEmpty())
        {
            QLabel* lbl = new QLabel(ui_text, grpbox);
            lbl->setWordWrap(true);
            layout->addWidget(lbl);
        }

        nlohmann::json& optJ = getOption(param.name);
        QString         tooltip_default;

        if (ui_type == "color")
        {
            if (param.type.rows <= 1)
            {
                tooltip_default = param.type.base == reshadefx::type::datatype::t_float ? QString::number(param.initializer_value.as_float[0])
                                                                                        : QString::number(param.initializer_value.as_int[0]);

                QDoubleSpinBox* spb = new QDoubleSpinBox(grpbox);
                objsToDelete.append(spb);
                objsToDelete.append(new IgnoreWheelEventFilter(spb));
                layout->addWidget(spb);
                spb->setMaximum(ui_max);
                spb->setMinimum(ui_min);
                spb->setSingleStep(ui_step);
                spb->setDecimals(5);
                if (!optJ.is_number())
                    optJ = param.type.base == reshadefx::type::datatype::t_float ? param.initializer_value.as_float[0]
                                                                                 : param.initializer_value.as_int[0];
                spb->setValue(optJ);

                connect(spb, &QDoubleSpinBox::valueChanged, this, [&optJ](double d) { optJ = d; });
            }
            else
            {
                tooltip_default = QString("%1, %2, %3, %4\n")
                                      .arg(param.initializer_value.as_float[0])
                                      .arg(param.initializer_value.as_float[1])
                                      .arg(param.initializer_value.as_float[2])
                                      .arg(param.initializer_value.as_float[3]);

                QPushButton* btn = new QPushButton(tr("Change color"), grpbox);
                objsToDelete.append(btn);
                layout->addWidget(btn);
                if (!(optJ.is_array() && optJ.size() >= param.type.rows))
                {
                    switch (param.type.rows)
                    {
                        case 3:
                            optJ = nlohmann::json::array(
                                {param.initializer_value.as_float[0], param.initializer_value.as_float[1], param.initializer_value.as_float[2]});
                            break;
                        case 4:
                            optJ = nlohmann::json::array({param.initializer_value.as_float[0],
                                                          param.initializer_value.as_float[1],
                                                          param.initializer_value.as_float[2],
                                                          param.initializer_value.as_float[3]});
                            break;
                        default: optJ = nlohmann::json::array({0, 0, 0, 0});
                    }
                }
                QColor c;
                QColor c2;
                c.setRgbF(optJ[0], optJ[1], optJ[2]);

                if (c.value() > 127)
                    c2.setHsv(c.hsvHue(), c.saturation(), 0);
                else
                    c2.setHsv(c.hsvHue(), c.saturation(), 255);

                btn->setStyleSheet(QString("border-style: outset; background-color: rgb(%1, %2, %3); color: rgb(%4, %5, %6);")
                                       .arg(c.red())
                                       .arg(c.green())
                                       .arg(c.blue())
                                       .arg(c2.red())
                                       .arg(c2.green())
                                       .arg(c2.blue()));
                connect(btn, &QPushButton::clicked, this, [=, &optJ]() mutable {
                    QColorDialog dlg(this);
                    switch (param.type.rows)
                    {
                        case 3: c.setRgbF(optJ[0], optJ[1], optJ[2]); break;
                        case 4:
                            dlg.setOption(QColorDialog::ShowAlphaChannel);
                            c.setRgbF(optJ[0], optJ[1], optJ[2], optJ[3]);
                            break;
                        default: dlg.setOption(QColorDialog::ShowAlphaChannel); break;
                    }
                    dlg.setCurrentColor(c);

                    if (dlg.exec())
                    {
                        c    = dlg.currentColor();
                        optJ = nlohmann::json::array({c.redF(), c.greenF(), c.blueF(), c.alphaF()});

                        if (c.value() > 127)
                            c2.setHsv(c.hsvHue(), c.saturation(), 0);
                        else
                            c2.setHsv(c.hsvHue(), c.saturation(), 255);

                        btn->setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(%4, %5, %6);")
                                               .arg(c.red())
                                               .arg(c.green())
                                               .arg(c.blue())
                                               .arg(c2.red())
                                               .arg(c2.green())
                                               .arg(c2.blue()));
                    }
                });
            }
        }
        else if (ui_type == "combo" || ui_type == "radio" || ui_type == "list")
        {
            tooltip_default =
                ui_items.size() > param.initializer_value.as_int[0]
                    ? QString("%1(%2)\n").arg(QString::number(param.initializer_value.as_int[0]), ui_items[param.initializer_value.as_int[0]])
                    : QString("%1\n").arg(param.initializer_value.as_int[0]);

            QComboBox* cmb = new QComboBox(grpbox);

            objsToDelete.append(cmb);
            objsToDelete.append(new IgnoreWheelEventFilter(cmb));
            layout->addWidget(cmb);
            cmb->addItems(ui_items);
            switch (param.type.base)
            {
                case reshadefx::type::datatype::t_bool:
                    if (!optJ.is_boolean())
                        optJ = static_cast<bool>(param.initializer_value.as_int[0]);

                    cmb->setCurrentIndex(optJ.get<bool>() ? 1 : 0);
                    break;
                default:
                    if (!optJ.is_number())
                        optJ = param.initializer_value.as_int[0];

                    cmb->setCurrentIndex(optJ);
                    break;
            }

            connect(cmb, &QComboBox::currentIndexChanged, this, [=, &optJ](int index) mutable {
                optJ = param.type.base == reshadefx::type::datatype::t_bool ? static_cast<bool>(index) : index;
            });
        }
        else // if(ui_type == "drag" || ui_type == "drag2" || ui_type == "input" || ui_type == "slider")
        {
            for (uint i = 0; i < param.type.rows; ++i)
            {
                if (ui_items.length() > i)
                {
                    QLabel* lbl = new QLabel(ui_items[i], grpbox);
                    objsToDelete.append(lbl);
                    layout->addWidget(lbl);
                }

                switch (param.type.base)
                {
                    case reshadefx::type::datatype::t_float:
                    {
                        tooltip_default.append(' ' + QString::number(param.initializer_value.as_float[i]) + ' ');

                        QDoubleSpinBox* spb = new QDoubleSpinBox(grpbox);
                        objsToDelete.append(spb);
                        objsToDelete.append(new IgnoreWheelEventFilter(spb));
                        layout->addWidget(spb);
                        spb->setMaximum(ui_max);
                        spb->setMinimum(ui_min);
                        spb->setSingleStep(ui_step);
                        spb->setDecimals(5);

                        if (param.type.rows <= 1)
                        {
                            if (!optJ.is_number())
                                optJ = param.initializer_value.as_float[i];
                            spb->setValue(optJ);
                        }
                        else
                        {
                            if (!(optJ.is_array() && optJ.size() >= param.type.rows))
                            {
                                optJ = nlohmann::json::array();
                                for (uint a = i; a < param.type.rows; ++a)
                                {
                                    optJ.push_back(param.initializer_value.as_float[a]);
                                }
                            }
                            spb->setValue(optJ[i]);
                        }

                        connect(spb, &QDoubleSpinBox::valueChanged, this, [=, &optJ](double d) {
                            if (param.type.rows <= 1)
                                optJ = d;
                            else
                                optJ[i] = d;
                        });
                    }
                    break;
                    case reshadefx::type::datatype::t_bool:
                    {
                        tooltip_default.append(' ' + QString::number(param.initializer_value.as_int[i]) + ' ');

                        QCheckBox* chb = new QCheckBox(grpbox);
                        objsToDelete.append(chb);
                        layout->addWidget(chb);

                        if (param.type.rows <= 1)
                        {
                            if (!optJ.is_boolean())
                                optJ = static_cast<bool>(param.initializer_value.as_int[i]);
                            chb->setChecked(optJ);
                        }
                        else
                        {
                            if (!(optJ.is_array() && optJ.size() >= param.type.rows))
                            {
                                optJ = nlohmann::json::array();
                                for (uint a = i; a < param.type.rows; ++a)
                                {
                                    optJ.push_back(static_cast<bool>(param.initializer_value.as_int[a]));
                                }
                            }
                            chb->setChecked(optJ[i]);
                        }

                        connect(chb, &QCheckBox::stateChanged, this, [=, &optJ](int state) mutable {
                            switch (state)
                            {
                                case Qt::Unchecked:
                                    if (param.type.rows <= 1)
                                        optJ = false;
                                    else
                                        optJ[i] = false;
                                    break;
                                default:
                                    if (param.type.rows <= 1)
                                        optJ = true;
                                    else
                                        optJ[i] = true;
                            }
                        });
                    }
                    break;
                    default:
                    {
                        tooltip_default.append(' ' + QString::number(param.initializer_value.as_int[i]) + ' ');

                        QSpinBox* spb = new QSpinBox(grpbox);
                        objsToDelete.append(spb);
                        objsToDelete.append(new IgnoreWheelEventFilter(spb));
                        layout->addWidget(spb);
                        spb->setMaximum(ui_max);
                        spb->setMinimum(ui_min);
                        if (param.type.rows <= 1)
                        {
                            if (!optJ.is_number())
                                optJ = param.initializer_value.as_int[i];
                            spb->setValue(optJ);
                        }
                        else
                        {
                            if (!(optJ.is_array() && optJ.size() >= param.type.rows))
                            {
                                optJ = nlohmann::json::array();
                                for (uint a = i; a < param.type.rows; ++a)
                                {
                                    optJ.push_back(param.initializer_value.as_int[a]);
                                }
                            }
                            spb->setValue(optJ[i]);
                        }

                        connect(spb, &QSpinBox::valueChanged, this, [=, &optJ](int in) {
                            if (param.type.rows <= 1)
                                optJ = in;
                            else
                                optJ[i] = in;
                        });
                    }
                    break;
                }
            }
        }
        grpbox->setToolTip(tr("Default: %1\n").arg(tooltip_default) + grpbox->toolTip());
    }
}

void ReshadeDialog::saveDefs()
{
    std::map<std::string, std::string> stdDefs;

    for (auto const& [key, value] : defs.toStdMap())
        stdDefs[key.toStdString()] = value.toStdString();

    getReshadeEffect()["defs"] = stdDefs;
    mdl.update();
}

void ReshadeDialog::addDefine()
{
    QInputDialog dlg(this);
    dlg.setInputMode(QInputDialog::TextInput);
    dlg.setLabelText(tr("Input define name"));

    if (dlg.exec())
        defs.insert(dlg.textValue(), "");

    saveDefs();
}

void ReshadeDialog::delDefine()
{
    const QItemSelectionModel* smdl = ui->defsView->selectionModel();

    if (smdl->hasSelection())
    {
        defs.remove(defs.keys()[smdl->selectedIndexes().value(0).row()]);
        saveDefs();
    }
}

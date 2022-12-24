#include <QFileDialog>

#include "settingsdialog.hpp"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(nlohmann::json& j, QWidget* parent) :
    QDialog(parent), ui(new Ui::SettingsDialog), json(j), model(reshadeTexturePath, this), inclModel(reshadeIncludePath, this)
{
    ui->setupUi(this);
    ui->reshadeTexturePathView->setModel(&model);
    ui->reshadeIncludePathView->setModel(&inclModel);

    connect(ui->toggleKeyValue, SIGNAL(keySequenceChanged(QKeySequence)), this, SLOT(toggleKeyValueChanged(QKeySequence)));
    connect(ui->reloadKeyValue, SIGNAL(keySequenceChanged(QKeySequence)), this, SLOT(reloadKeyValueChanged(QKeySequence)));
    connect(ui->enableOnLaunchValue, SIGNAL(stateChanged(int)), this, SLOT(enableOnLaunchValueChanged(int)));
    connect(ui->depthCaptureValue, SIGNAL(stateChanged(int)), this, SLOT(depthCaptureValueChanged(int)));
    connect(ui->add, SIGNAL(clicked(bool)), this, SLOT(addClicked()));
    connect(ui->del, SIGNAL(clicked(bool)), this, SLOT(delClicked()));
    connect(ui->addIncl, SIGNAL(clicked(bool)), this, SLOT(addInclClicked()));
    connect(ui->delIncl, SIGNAL(clicked(bool)), this, SLOT(delInclClicked()));

    if (json.contains("toggleKey") && json["toggleKey"].is_string())
        ui->toggleKeyValue->setKeySequence(json["toggleKey"].get<QString>());
    else
        ui->toggleKeyValue->setKeySequence(QString("Home"));

    if (json.contains("reloadKey") && json["reloadKey"].is_string())
        ui->reloadKeyValue->setKeySequence(json["reloadKey"].get<QString>());
    else
        ui->reloadKeyValue->setKeySequence(QString("End"));

    if (json.contains("enableOnLaunch") && json["enableOnLaunch"].is_boolean())
        ui->enableOnLaunchValue->setChecked(json["enableOnLaunch"]);
    else
        ui->enableOnLaunchValue->setChecked(true);

    if (json.contains("depthCapture") && json["depthCapture"].is_string())
        ui->depthCaptureValue->setChecked(json["depthCapture"] == "on");
    else
        ui->depthCaptureValue->setChecked(false);

    if (json.contains("reshadeTexturePath") && json["reshadeTexturePath"].is_array())
    {
        const nlohmann::json& arr = json["reshadeTexturePath"];
        for (const QString strPath : arr)
            reshadeTexturePath.append(strPath);
    }
    else
        json["reshadeTexturePath"] = nlohmann::json::array();

    if (json.contains("reshadeIncludePath") && json["reshadeIncludePath"].is_array())
    {
        const nlohmann::json& arr = json["reshadeIncludePath"];
        for (const QString strPath : arr)
            reshadeIncludePath.append(strPath);
    }
    else
        json["reshadeIncludePath"] = nlohmann::json::array();

    update();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::update()
{
    model.update();
    inclModel.update();

    nlohmann::json arr = nlohmann::json::array();
    for (const QDir& dir : reshadeTexturePath)
        arr.push_back(dir.absolutePath().toStdString());
    json["reshadeTexturePath"] = arr;

    nlohmann::json arr2 = nlohmann::json::array();
    for (const QDir& dir : reshadeIncludePath)
        arr2.push_back(dir.absolutePath().toStdString());
    json["reshadeIncludePath"] = arr2;
}

void SettingsDialog::toggleKeyValueChanged(const QKeySequence& keySequence)
{
    const QString key = keySequence.toString(QKeySequence::NativeText);

    if (key.compare("Home", Qt::CaseInsensitive) == 0)
        json.erase("toggleKey");
    else
        json["toggleKey"] = key;
}

void SettingsDialog::reloadKeyValueChanged(const QKeySequence& keySequence)
{
    const QString key = keySequence.toString(QKeySequence::NativeText);

    if (key.compare("End", Qt::CaseInsensitive) == 0)
        json.erase("reload");
    else
        json["reload"] = key;
}

void SettingsDialog::enableOnLaunchValueChanged(int i)
{
    if (i == Qt::Checked)
        json.erase("enableOnLaunch");
    else
        json["enableOnLaunch"] = false;
}

void SettingsDialog::depthCaptureValueChanged(int i)
{
    if (i == Qt::Checked)
        json["depthCapture"] = "on";
    else
        json.erase("depthCapture");
}

void SettingsDialog::addClicked()
{
    QFileDialog dlg(this, tr("Select reshade textures directory"));
    dlg.setFileMode(QFileDialog::Directory);

    if (dlg.exec() && dlg.directory().exists())
        reshadeTexturePath.append(dlg.directory());

    update();
}

void SettingsDialog::delClicked()
{
    const QItemSelectionModel* mdl = ui->reshadeTexturePathView->selectionModel();
    if (mdl->hasSelection())
        reshadeTexturePath.remove(mdl->selectedRows().value(0).row());

    update();
}

void SettingsDialog::addInclClicked()
{
    QFileDialog dlg(this, tr("Select reshade include directory"));
    dlg.setFileMode(QFileDialog::Directory);

    if (dlg.exec() && dlg.directory().exists())
        reshadeIncludePath.append(dlg.directory());

    update();
}

void SettingsDialog::delInclClicked()
{
    const QItemSelectionModel* mdl = ui->reshadeIncludePathView->selectionModel();
    if (mdl->hasSelection())
        reshadeIncludePath.remove(mdl->selectedRows().value(0).row());

    update();
}

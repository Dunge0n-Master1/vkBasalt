#include "mainwindow.hpp"
#include "reshadeeffect.hpp"
#include "settingsdialog.hpp"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), before(nlohmann::json::object()), json(nlohmann::json::object()), autosaveTimer(this)
{
    ui->setupUi(this);

    avaliableModel = new EffectsList(&avaliableEffects, this);
    usedModel      = new EffectsList(&usedEffects, this);

    ui->avaliableList->setModel(avaliableModel);
    ui->usedList->setModel(usedModel);

    avaliableEffects.append(new CasEffect(json, this));
    avaliableEffects.append(new DlsEffect(json, this));
    avaliableEffects.append(new FxaaEffect(json, this));
    avaliableEffects.append(new SmaaEffect(json, this));
    avaliableEffects.append(new LutEffect(json, this));
    avaliableEffects.append(new DebandEffect(json, this));

    autosaveTimer.setInterval(2000);

    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFileSelectDialog()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(saveFileAsDialog()));
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(newCfg()));
    connect(ui->actionSettings, SIGNAL(triggered(bool)), this, SLOT(openSettings()));
    connect(ui->actionAutoSave, SIGNAL(toggled(bool)), this, SLOT(toggleAutosave(bool)));

    connect(&autosaveTimer, SIGNAL(timeout()), this, SLOT(saveFile()));

    connect(ui->avaliableList, SIGNAL(activated(QModelIndex)), this, SLOT(selectedAvaliable()));
    connect(ui->usedList, SIGNAL(activated(QModelIndex)), this, SLOT(selectedUsed()));

    connect(ui->add, SIGNAL(clicked(bool)), this, SLOT(addEffectDialog()));
    connect(ui->addFromDir, SIGNAL(clicked(bool)), this, SLOT(addEffectsFromDir()));
    connect(ui->deleteAvaliable, SIGNAL(clicked(bool)), this, SLOT(removeEffect()));
    connect(ui->use, SIGNAL(clicked(bool)), this, SLOT(useEffect()));
    connect(ui->deleteUsed, SIGNAL(clicked(bool)), this, SLOT(unuseEffect()));
    connect(ui->edit, SIGNAL(clicked(bool)), this, SLOT(editEffect()));
    connect(ui->up, SIGNAL(clicked(bool)), this, SLOT(upEffect()));
    connect(ui->down, SIGNAL(clicked(bool)), this, SLOT(downEffect()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getAvaliableEffectIndexByName(const QString& name)
{
    for (int i = 0; i < avaliableEffects.size(); ++i)
    {
        if (avaliableEffects[i]->getName() == name)
            return i;
    }
    return -1;
}

QList<int> MainWindow::getUsedEffectsIndexesByName(const QString& name)
{
    QList<int> out;
    for (int i = 0; i < usedEffects.size(); ++i)
    {
        if (usedEffects[i]->getName() == name)
            out.append(i);
    }
    return out;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (before != json)
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this,
                                                                   "vkBasalt gui",
                                                                   tr("Do you really want to close this program without saving the configuration?"),
                                                                   QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes)
            event->ignore();
        else
            event->accept();
    }
}

void MainWindow::openFileSelectDialog()
{
    QFileDialog dlg(this, tr("Open vkBasalt config file"));
    dlg.setNameFilter("Any files (*)");
    dlg.setFileMode(QFileDialog::ExistingFile);
    dlg.setDirectory(QDir::homePath() + "/.local/share/vkBasalt");
    if (dlg.exec())
        openFile(dlg.selectedFiles().at(0));
}

void MainWindow::openFile(QString path)
{
    QFile cfg(path);
    cfg.open(QFile::ReadOnly);
    if (cfg.isReadable())
    {
        json = nlohmann::json::parse(cfg.readAll());

        if (json.is_object())
        {
            configPath = path;
            before     = json;

            for (const Effect* e : avaliableEffects)
                delete e;

            avaliableEffects.clear();
            usedEffects.clear();

            avaliableEffects.append(new CasEffect(json, this));
            avaliableEffects.append(new DlsEffect(json, this));
            avaliableEffects.append(new FxaaEffect(json, this));
            avaliableEffects.append(new SmaaEffect(json, this));
            avaliableEffects.append(new LutEffect(json, this));
            avaliableEffects.append(new DebandEffect(json, this));

            if (json.contains("reshade_effects") && json["reshade_effects"].is_object())
            {
                for (const auto& el : json["reshade_effects"].items())
                {
                    avaliableEffects.append(new ReshadeEffect(QString::fromStdString(el.key()), json, this));
                }
            }

            if (json.contains("effects") && json["effects"].is_array())
            {
                for (const auto& val : json["effects"])
                {
                    if (val.is_string())
                        usedEffects.append(avaliableEffects[getAvaliableEffectIndexByName(val)]);
                }
            }

            updateViews();
            updateJson();

            return;
        }
    }
    QMessageBox msgBox(this);
    msgBox.setText(tr("Open failed"));
    msgBox.setIcon(QMessageBox::Warning);

    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();
}

void MainWindow::saveFile()
{
    if (configPath.isEmpty())
        saveFileAsDialog();
    else if (before != json)
        saveFileAs(configPath);
}

void MainWindow::saveFileAsDialog()
{
    QFileDialog dlg(this, tr("Save vkBasalt config file"));
    dlg.setNameFilter("Any files (*)");
    dlg.setFileMode(QFileDialog::AnyFile);
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setDirectory(QDir::homePath() + "/.local/share/vkBasalt");
    if (dlg.exec())
        saveFileAs(dlg.selectedFiles().at(0));
}

void MainWindow::saveFileAs(QString path)
{
    QFile cfg(path);
    if (cfg.open(QFile::WriteOnly))
    {
        cfg.write(json.dump(4).c_str());
        configPath = path;
        before     = json;
        return;
    }
    QMessageBox msgBox(this);
    msgBox.setText(tr("Save failed"));
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();
}

void MainWindow::newCfg()
{
    for (const Effect* e : avaliableEffects)
        delete e;

    avaliableEffects.clear();
    usedEffects.clear();
    configPath.clear();

    avaliableEffects.append(new CasEffect(json, this));
    avaliableEffects.append(new DlsEffect(json, this));
    avaliableEffects.append(new FxaaEffect(json, this));
    avaliableEffects.append(new SmaaEffect(json, this));
    avaliableEffects.append(new LutEffect(json, this));
    avaliableEffects.append(new DebandEffect(json, this));

    json   = nlohmann::json::object();
    before = json;

    updateViews();
}

void MainWindow::openSettings()
{
    SettingsDialog dlg(json, this);
    dlg.exec();
}

void MainWindow::toggleAutosave(bool state)
{
    if (state)
        autosaveTimer.start();
    else
        autosaveTimer.stop();
}

void MainWindow::selectedAvaliable()
{
    ui->usedList->clearSelection();
}

void MainWindow::selectedUsed()
{
    ui->avaliableList->clearSelection();
}

void MainWindow::updateViews()
{
    avaliableModel->update();
    usedModel->update();
}

void MainWindow::updateJson()
{
    nlohmann::json arr = nlohmann::json::array();

    for (const Effect* e : usedEffects)
        arr.push_back(e->getName());

    json["effects"] = arr;
}

void MainWindow::addEffectDialog()
{
    QInputDialog dlg(this);
    dlg.setInputMode(QInputDialog::TextInput);
    dlg.setLabelText(tr("Effect name:"));
    if (dlg.exec())
        addEffect(dlg.textValue());
}

void MainWindow::addEffect(QString name)
{
    if (!name.isEmpty() && getAvaliableEffectIndexByName(name) == -1)
        avaliableEffects.append(new ReshadeEffect(name, json, this));
    updateViews();
}

void MainWindow::addEffectsFromDir()
{
    QFileDialog dlg(this, tr("Select directory with *.fx files"));
    dlg.setFileMode(QFileDialog::Directory);
    if (dlg.exec())
    {
        QDir d = dlg.directory();
        if (!d.exists())
            return;

        if (json.contains("reshadeIncludePath") && json["reshadeIncludePath"].is_array())
        {
            nlohmann::json reshadeIncludePath = json["reshadeIncludePath"];
            bool           contains           = false;

            for (const QString includePath : reshadeIncludePath)
                if (includePath == d.absolutePath())
                    contains = true;

            if (!contains)
                reshadeIncludePath.push_back(d.absolutePath());
        }
        else
            json["reshadeIncludePath"] = nlohmann::json::array({d.absolutePath()});

        for (const QFileInfo& f : d.entryInfoList({"*.fx"}, QDir::Files | QDir::Readable))
        {
            if (getAvaliableEffectIndexByName(f.baseName()) == -1)
            {
                avaliableEffects.append(new ReshadeEffect(f.baseName(), json, this));
                if (!(json.contains("reshade_effects") && json["reshade_effects"].is_object()))
                {
                    json["reshade_effects"] = nlohmann::json::object();
                }
                json["reshade_effects"][f.baseName().toStdString()] = nlohmann::json::object({{"path", f.absoluteFilePath()}});
            }
        }
        updateViews();
        updateJson();
    }
}

void MainWindow::removeEffect()
{
    const QItemSelectionModel* mdl = ui->avaliableList->selectionModel();
    if (mdl->hasSelection())
    {
        const Effect* e = avaliableEffects[mdl->selectedRows().value(0).row()];

        if (!e->isReshade())
            return;

        if (json.contains("reshade_effects") && json["reshade_effects"].is_object())
            json["reshade_effects"].erase(e->getName().toStdString());

        QList<int> indexes = getUsedEffectsIndexesByName(e->getName());
        std::sort(indexes.begin(), indexes.end(), std::greater<int>());
        avaliableEffects.remove(mdl->selectedRows().value(0).row());

        foreach (const int i, indexes)
        {
            usedEffects.remove(i);
        }

        delete e;

        updateViews();
        updateJson();
    }
}

void MainWindow::useEffect()
{
    const QItemSelectionModel* mdl = ui->avaliableList->selectionModel();
    if (mdl->hasSelection())
        usedEffects.append(avaliableEffects[mdl->selectedRows().value(0).row()]);
    updateViews();
    updateJson();
}

void MainWindow::unuseEffect()
{
    const QItemSelectionModel* mdl = ui->usedList->selectionModel();
    if (mdl->hasSelection())
        usedEffects.remove(mdl->selectedRows().value(0).row());
    updateViews();
    updateJson();
}

void MainWindow::editEffect()
{
    const QItemSelectionModel* mdl = ui->avaliableList->selectionModel();
    if (mdl->hasSelection())
        avaliableEffects[mdl->selectedRows().value(0).row()]->openSettingsDialog(this);
    updateViews();
}

void MainWindow::upEffect()
{
    const QItemSelectionModel* mdl = ui->usedList->selectionModel();
    if (mdl->hasSelection())
        usedEffects.move(mdl->selectedRows().value(0).row(), mdl->selectedRows().value(0).row() - 1);
    updateViews();
    updateJson();
}

void MainWindow::downEffect()
{
    const QItemSelectionModel* mdl = ui->usedList->selectionModel();
    if (mdl->hasSelection())
        usedEffects.move(mdl->selectedRows().value(0).row(), mdl->selectedRows().value(0).row() + 1);
    updateViews();
    updateJson();
}

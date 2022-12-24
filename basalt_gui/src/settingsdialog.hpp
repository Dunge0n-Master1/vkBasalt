#pragma once

#include <QDialog>
#include <QDir>

#include "nlohmann/json-qt.hpp"
#include "pathlistmodel.hpp"

namespace Ui
{
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(nlohmann::json& json, QWidget* parent = nullptr);
    ~SettingsDialog();

private:
    Ui::SettingsDialog* ui;
    nlohmann::json&     json;
    QList<QDir>         reshadeIncludePath;
    QList<QDir>         reshadeTexturePath;
    PathListModel       model;
    PathListModel       inclModel;

public slots:

    void update();
private slots:
    void toggleKeyValueChanged(const QKeySequence& keySequence);
    void reloadKeyValueChanged(const QKeySequence& keySequence);
    void enableOnLaunchValueChanged(int i);
    void depthCaptureValueChanged(int i);
    void addClicked();
    void delClicked();
    void addInclClicked();
    void delInclClicked();
};

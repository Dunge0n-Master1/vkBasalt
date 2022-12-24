#pragma once

#include "effectslist.hpp"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    int        getAvaliableEffectIndexByName(const QString& name);
    QList<int> getUsedEffectsIndexesByName(const QString& name);

    Ui::MainWindow* ui;

    QString        configPath;
    nlohmann::json before;
    nlohmann::json json;
    QList<Effect*> avaliableEffects;
    QList<Effect*> usedEffects;
    EffectsList*   avaliableModel;
    EffectsList*   usedModel;
    QTimer         autosaveTimer;

public slots:
    void closeEvent(QCloseEvent* event);

    void openFileSelectDialog();
    void openFile(QString path);
    void saveFile();
    void saveFileAsDialog();
    void saveFileAs(QString path);
    void newCfg();
    void openSettings();
    void toggleAutosave(bool state);

    void selectedAvaliable();
    void selectedUsed();
    void updateViews();
    void updateJson();

    void addEffectDialog();
    void addEffect(QString name);
    void addEffectsFromDir();
    void removeEffect();
    void useEffect();
    void unuseEffect();
    void editEffect();
    void upEffect();
    void downEffect();
};

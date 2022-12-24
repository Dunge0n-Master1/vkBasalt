#pragma once

#include <QDialog>

#include "defsmodel.hpp"
#include "nlohmann/json-qt.hpp"

namespace Ui
{
    class ReshadeDialog;
}

class ReshadeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReshadeDialog(nlohmann::json& json, QString* name, QString* desc, QWidget* parent = nullptr);
    ~ReshadeDialog();

private:
    nlohmann::json& getReshadeEffect();
    nlohmann::json& getOptions();
    nlohmann::json& getOption(const QString& optname);
    nlohmann::json& getOption(const std::string& optname);

    Ui::ReshadeDialog* ui;
    nlohmann::json&    json;
    QString*           name;
    QString*           desc;

    QList<QObject*>        objsToDelete;
    DefsModel              mdl;
    QMap<QString, QString> defs;

public slots:
    void fileButtonPressed();
    void filePathChanged(const QString& text);
    void parseEffect();
    void deleteWidgets();
    void generateWidgets(QString path);
    void saveDefs();
    void addDefine();
    void delDefine();
};

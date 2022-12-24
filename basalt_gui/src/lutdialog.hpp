#pragma once

#include <QDialog>

#include "nlohmann/json-qt.hpp"

namespace Ui
{
    class LutDialog;
}

class LutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LutDialog(nlohmann::json& j, QWidget* parent = nullptr);
    ~LutDialog();

private slots:
    void fileSelectClicked();
    void fileValueEditied(const QString& text);

private:
    Ui::LutDialog*  ui;
    nlohmann::json& json;
};

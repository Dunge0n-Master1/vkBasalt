#pragma once

#include <QDialog>

#include "nlohmann/json-qt.hpp"

namespace Ui
{
    class DebandDialog;
}

class DebandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DebandDialog(nlohmann::json& j, QWidget* parent = nullptr);
    ~DebandDialog();

public slots:
    void avgdiffValueChanged(double d);
    void maxdiffValueChanged(double d);
    void middiffValueChanged(double d);
    void rangeValueChanged(double d);
    void iterationsValueChanged(int i);

private:
    Ui::DebandDialog* ui;
    nlohmann::json&   json;
};

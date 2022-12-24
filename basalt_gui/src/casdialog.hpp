#pragma once

#include <QDialog>

#include "nlohmann/json-qt.hpp"

namespace Ui
{
    class CasDialog;
}

class CasDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CasDialog(nlohmann::json& j, QWidget* parent = nullptr);
    ~CasDialog();

public slots:
    void sharpnessValueChanged(double d);

private:
    Ui::CasDialog*  ui;
    nlohmann::json& json;
};

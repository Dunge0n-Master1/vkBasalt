#pragma once

#include <QDialog>

#include "nlohmann/json-qt.hpp"

namespace Ui
{
    class DlsDialog;
}

class DlsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DlsDialog(nlohmann::json& j, QWidget* parent = nullptr);
    ~DlsDialog();

public slots:
    void sharpnessValueChanged(double d);
    void denoiseValueChanged(double d);

private:
    Ui::DlsDialog*  ui;
    nlohmann::json& json;
};

#pragma once

#include <QDialog>

#include "nlohmann/json-qt.hpp"

namespace Ui
{
    class FxaaDialog;
}

class FxaaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FxaaDialog(nlohmann::json& j, QWidget* parent = nullptr);
    ~FxaaDialog();

public slots:
    void subpixValueChanged(double d);
    void edgeThresholdValueChanged(double d);
    void edgeThresholdMinValueChanged(double d);

private:
    Ui::FxaaDialog* ui;
    nlohmann::json& json;
};

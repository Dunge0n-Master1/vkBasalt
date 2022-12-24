#pragma once

#include <QDialog>

#include "nlohmann/json-qt.hpp"

namespace Ui
{
    class SmaaDialog;
}

class SmaaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SmaaDialog(nlohmann::json& j, QWidget* parent = nullptr);
    ~SmaaDialog();

public slots:
    void edgeDetectionValueChanged(const QString& text);
    void thresholdValueChanged(double d);
    void maxSearchStepsValueChanged(int i);
    void maxSearchStepsDiagValueChanged(int i);
    void cornerRoundingValueChanged(int i);

private:
    Ui::SmaaDialog* ui;
    nlohmann::json& json;
};

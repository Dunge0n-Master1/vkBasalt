#include <QJsonObject>

#include "smaadialog.hpp"
#include "ui_smaadialog.h"

SmaaDialog::SmaaDialog(nlohmann::json& j, QWidget* parent) : QDialog(parent), ui(new Ui::SmaaDialog), json(j)
{
    ui->setupUi(this);

    connect(ui->edgeDetectionValue, SIGNAL(currentTextChanged(QString)), this, SLOT(edgeDetectionValueChanged(QString)));
    connect(ui->thresholdValue, SIGNAL(valueChanged(double)), this, SLOT(thresholdValueChanged(double)));
    connect(ui->maxSearchStepsValue, SIGNAL(valueChanged(int)), this, SLOT(maxSearchStepsValueChanged(int)));
    connect(ui->maxSearchStepsDiagValue, SIGNAL(valueChanged(int)), this, SLOT(maxSearchStepsDiagValueChanged(int)));
    connect(ui->cornerRoundingValue, SIGNAL(valueChanged(int)), this, SLOT(cornerRoundingValueChanged(int)));

    if (json.contains("smaaEdgeDetection") && json["smaaEdgeDetection"].is_string())
    {
        if (json["smaaEdgeDetection"] == "luma")
            ui->edgeDetectionValue->setCurrentIndex(0);
        else
            ui->edgeDetectionValue->setCurrentIndex(1);
    }
    if (json.contains("smaaThreshold") && json["smaaThreshold"].is_number())
        ui->thresholdValue->setValue(json["smaaThreshold"]);
    if (json.contains("smaaMaxSearchSteps") && json["smaaMaxSearchSteps"].is_number())
        ui->maxSearchStepsValue->setValue(json["smaaMaxSearchSteps"]);
    if (json.contains("smaaMaxSearchStepsDiag") && json["smaaMaxSearchStepsDiag"].is_number())
        ui->maxSearchStepsDiagValue->setValue(json["smaaMaxSearchStepsDiag"]);
    if (json.contains("smaaCornerRounding") && json["smaaCornerRounding"].is_number())
        ui->cornerRoundingValue->setValue(json["smaaCornerRounding"]);
}

SmaaDialog::~SmaaDialog()
{
    delete ui;
}

void SmaaDialog::edgeDetectionValueChanged(const QString& text)
{
    if (text == "luma")
        json.erase("smaaEdgeDetection");
    json["smaaEdgeDetection"] = text;
}

void SmaaDialog::thresholdValueChanged(double d)
{
    if (d == 0.05f)
        json.erase("smaaThreshold");
    json["smaaThreshold"] = d;
}

void SmaaDialog::maxSearchStepsValueChanged(int i)
{
    if (i == 32)
        json.erase("smaaMaxSearchSteps");
    json["smaaMaxSearchSteps"] = i;
}

void SmaaDialog::maxSearchStepsDiagValueChanged(int i)
{
    if (i == 16)
        json.erase("smaaMaxSearchStepsDiag");
    json["smaaMaxSearchStepsDiag"] = i;
}

void SmaaDialog::cornerRoundingValueChanged(int i)
{
    if (i == 25)
        json.erase("smaaCornerRounding");
    json["smaaCornerRounding"] = i;
}

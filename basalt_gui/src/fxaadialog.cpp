#include "fxaadialog.hpp"
#include "ui_fxaadialog.h"

FxaaDialog::FxaaDialog(nlohmann::json& j, QWidget* parent) : QDialog(parent), ui(new Ui::FxaaDialog), json(j)
{
    ui->setupUi(this);

    connect(ui->subpixValue, SIGNAL(valueChanged(double)), this, SLOT(subpixValueChanged(double)));
    connect(ui->edgeThresholdValue, SIGNAL(valueChanged(double)), this, SLOT(edgeThresholdValueChanged(double)));
    connect(ui->edgeThresholdMinValue, SIGNAL(valueChanged(double)), this, SLOT(edgeThresholdMinValueChanged(double)));

    if (json.contains("fxaaQualitySubpix") && json["fxaaQualitySubpix"].is_number())
        ui->subpixValue->setValue(json["fxaaQualitySubpix"]);

    if (json.contains("fxaaQualityEdgeThreshold") && json["fxaaQualityEdgeThreshold"].is_number())
        ui->edgeThresholdValue->setValue(json["fxaaQualityEdgeThreshold"]);

    if (json.contains("fxaaQualityEdgeThresholdMin") && json["fxaaQualityEdgeThresholdMin"].is_number())
        ui->edgeThresholdMinValue->setValue(json["fxaaQualityEdgeThresholdMin"]);
}

FxaaDialog::~FxaaDialog()
{
    delete ui;
}

void FxaaDialog::subpixValueChanged(double d)
{
    if (d == 0.75f)
        json.erase("fxaaQualitySubpix");
    json["fxaaQualitySubpix"] = d;
}

void FxaaDialog::edgeThresholdValueChanged(double d)
{
    if (d == 0.125f)
        json.erase("fxaaQualityEdgeThreshold");
    json["fxaaQualityEdgeThreshold"] = d;
}

void FxaaDialog::edgeThresholdMinValueChanged(double d)
{
    if (d == 0.0312f)
        json.erase("fxaaQualityEdgeThresholdMin");
    json["fxaaQualityEdgeThresholdMin"] = d;
}

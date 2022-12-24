#include "dlsdialog.hpp"
#include "ui_dlsdialog.h"

DlsDialog::DlsDialog(nlohmann::json& j, QWidget* parent) : QDialog(parent), ui(new Ui::DlsDialog), json(j)
{
    ui->setupUi(this);

    connect(ui->sharpnessValue, SIGNAL(valueChanged(double)), this, SLOT(sharpnessValueChanged(double)));
    connect(ui->denoiseValue, SIGNAL(valueChanged(double)), this, SLOT(denoiseValueChanged(double)));

    if (json.contains("dlsSharpness") && json["dlsSharpness"].is_number())
        ui->sharpnessValue->setValue(json["dlsSharpness"]);

    if (json.contains("dlsDenoise") && json["dlsDenoise"].is_number())
        ui->denoiseValue->setValue(json["dlsDenoise"]);
}

DlsDialog::~DlsDialog()
{
    delete ui;
}

void DlsDialog::sharpnessValueChanged(double d)
{
    if (d == 0.5f)
        json.erase("dlsSharpness");
    json["dlsSharpness"] = d;
}

void DlsDialog::denoiseValueChanged(double d)
{
    if (d == 0.17f)
        json.erase("dlsDenoise");
    json["dlsDenoise"] = d;
}

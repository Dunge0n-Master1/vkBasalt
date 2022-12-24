#include "casdialog.hpp"
#include "ui_casdialog.h"

CasDialog::CasDialog(nlohmann::json& j, QWidget* parent) : QDialog(parent), ui(new Ui::CasDialog), json(j)
{
    ui->setupUi(this);

    connect(ui->sharpnessValue, SIGNAL(valueChanged(double)), this, SLOT(sharpnessValueChanged(double)));

    if (json.contains("casSharpness") && json["casSharpness"].is_number())
        ui->sharpnessValue->setValue(json["casSharpness"]);
}

CasDialog::~CasDialog()
{
    delete ui;
}

void CasDialog::sharpnessValueChanged(double d)
{
    if (d == 0.4f)
        json.erase("casSharpness");
    json["casSharpness"] = d;
}

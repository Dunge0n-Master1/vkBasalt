#include "debanddialog.hpp"
#include "ui_debanddialog.h"

DebandDialog::DebandDialog(nlohmann::json& j, QWidget* parent) : QDialog(parent), ui(new Ui::DebandDialog), json(j)
{
    ui->setupUi(this);

    connect(ui->avgdiffValue, SIGNAL(valueChanged(double)), this, SLOT(avgdiffValueChanged(double)));
    connect(ui->maxdiffValue, SIGNAL(valueChanged(double)), this, SLOT(maxdiffValueChanged(double)));
    connect(ui->middiffValue, SIGNAL(valueChanged(double)), this, SLOT(middiffValueChanged(double)));
    connect(ui->rangeValue, SIGNAL(valueChanged(double)), this, SLOT(rangeValueChanged(double)));
    connect(ui->iterationsValue, SIGNAL(valueChanged(int)), this, SLOT(iterationsValueChanged(int)));

    if (json.contains("debandAvgdiff") && json["debandAvgdiff"].is_number())
        ui->avgdiffValue->setValue(json["debandAvgdiff"]);
    if (json.contains("debandMaxdiff") && json["debandMaxdiff"].is_number())
        ui->maxdiffValue->setValue(json["debandMaxdiff"]);
    if (json.contains("debandMiddiff") && json["debandMiddiff"].is_number())
        ui->middiffValue->setValue(json["debandMiddiff"]);
    if (json.contains("debandRange") && json["debandRange"].is_number())
        ui->rangeValue->setValue(json["debandRange"]);
    if (json.contains("debandIterations") && json["debandIterations"].is_number())
        ui->iterationsValue->setValue(json["debandIterations"]);
}

DebandDialog::~DebandDialog()
{
    delete ui;
}

void DebandDialog::avgdiffValueChanged(double d)
{
    if (d == 3.4f)
        json.erase("debandAvgdiff");
    json["debandAvgdiff"] = d;
}

void DebandDialog::maxdiffValueChanged(double d)
{
    if (d == 6.8f)
        json.erase("debandMaxdiff");
    json["debandMaxdiff"] = d;
}

void DebandDialog::middiffValueChanged(double d)
{
    if (d == 3.3f)
        json.erase("debandMiddiff");
    json["debandMiddiff"] = d;
}

void DebandDialog::rangeValueChanged(double d)
{
    if (d == 16.0f)
        json.erase("debandRange");
    json["debandRange"] = d;
}

void DebandDialog::iterationsValueChanged(int i)
{
    if (i == 4)
        json.erase("debandIterations");
    json["debandIterations"] = i;
}

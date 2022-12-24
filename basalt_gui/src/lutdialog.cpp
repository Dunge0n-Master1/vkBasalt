#include <QFileDialog>

#include "lutdialog.hpp"
#include "ui_lutdialog.h"

LutDialog::LutDialog(nlohmann::json& j, QWidget* parent) : QDialog(parent), ui(new Ui::LutDialog), json(j)
{
    ui->setupUi(this);

    connect(ui->fileSelect, SIGNAL(clicked(bool)), this, SLOT(fileSelectClicked()));
    connect(ui->fileValue, SIGNAL(textEdited(QString)), this, SLOT(fileValueEditied(QString)));

    if (json.contains("lutFile") && json["lutFile"].is_string())
        ui->fileValue->setText(json["lutFile"]);
}

LutDialog::~LutDialog()
{
    delete ui;
}

void LutDialog::fileSelectClicked()
{
    QFileDialog dlg(this, tr("Select LUT file"));
    dlg.setNameFilters({"LUT files (*.png *.cube *.CUBE)", "Any files (*)"});
    dlg.setFileMode(QFileDialog::ExistingFile);
    if (dlg.exec())
    {
        ui->fileValue->setText(dlg.selectedFiles().at(0));
        json["lutFile"] = dlg.selectedFiles().at(0);
    }
}

void LutDialog::fileValueEditied(const QString& text)
{
    json["lutFile"] = text;
}

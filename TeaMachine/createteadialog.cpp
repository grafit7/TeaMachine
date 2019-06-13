#include "ui_createteadialog.h"
#include "createteadialog.h"
#include "tea.h"

#include <QPushButton>

CreateTeaDialog::CreateTeaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTeaDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui->titleLineEdit, &QLineEdit::textChanged,this,&CreateTeaDialog::dataCheck);
    connect(ui->descriptionLineEdit, &QLineEdit::textChanged,this,&CreateTeaDialog::dataCheck);
    connect(ui->timeSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&CreateTeaDialog::dataCheck);
}

CreateTeaDialog::~CreateTeaDialog()
{
    delete ui;
}

void CreateTeaDialog::accept()
{
    Tea *tea = new Tea(ui->titleLineEdit->text(), ui->descriptionLineEdit->text(),
                       ui->timeSpinBox->value());
    emit teaCreated(tea);
    ui->titleLineEdit->clear();
    ui->descriptionLineEdit->clear();
    ui->timeSpinBox->setValue(0);
    QDialog::accept();
}

void CreateTeaDialog::dataCheck()
{
    bool result = false;
    if(!ui->titleLineEdit->text().isEmpty()
            && !ui->descriptionLineEdit->text().isEmpty()
            && ui->timeSpinBox->value() >= 1)
    {
        result = true;
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(result);
}

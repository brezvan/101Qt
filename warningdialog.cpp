include "warningdialog.h"
#include "ui_warningdialog.h"

warningDialog::warningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::warningDialog)
{
    ui->setupUi(this);
}

warningDialog::~warningDialog()
{
    delete ui;
}

#include <QDialog>
#include <QMessageBox>
#include <iostream>
#include "newDepartmentdialog.h"
#include "ui_newDepartmentdialog.h"
newDepartmentdialog::newDepartmentdialog() :

    ui(new Ui::newDepartmentdialog)
{
    ui->setupUi(this);
}

newDepartmentdialog::~newDepartmentdialog()
{
    delete ui;
}

// ok button
void newDepartmentdialog::on_okButton_clicked()
{
    //making sure that the new department has a name
   if(ui->Department->text().isEmpty()){

       QMessageBox msg;
       msg.setText("please enter a name for the department");
       msg.exec();
   }
else{
    Department* dpt=new Department(ui->Department->text());
    newdept=dpt;
    this->accept();

}
}


// cancel button
void newDepartmentdialog::on_cancelButton_clicked()
{   
    this->reject();
}

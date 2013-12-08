#include <iostream>
#include "mainwindow.h"
#include "newEmployeedialog.h"
#include "ui_newEmployeedialog.h"
#include "Department.h"
#include "Employee.h"
newEmployeedialog::newEmployeedialog() :

    ui(new Ui::newEmployeedialog)

{
       ui->setupUi(this);


}
newEmployeedialog::~newEmployeedialog()
{
    delete ui;
}


void newEmployeedialog::on_ok_clicked()
{
    //making sure that the new employee has a name
    if(ui->name->text().isEmpty()){

        QMessageBox msg;
        msg.setText("please enter a name for the employee");
        msg.exec();
    }else{
   Employee* emp=new Employee();
   emp->setName(ui->name->text());
   emp->setAddress(ui->address->text());
   //the restrictions in the field for the salary makes sure that the salary is a positive number
   //so there is no condition here
   emp->setSalary(ui->salary->value());
   newempl=emp;
   accept();
    }
}

void newEmployeedialog::on_cancel_clicked()
{
    reject();
}

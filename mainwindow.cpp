#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "QString"
#include <QVariant>
#include <QDialog>
#include <QDoubleValidator>
#include <QColor>
#include <float.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"ui_movedialog.h"
#include "Company.h"
#include "Department.h"
#include"ItemTypes.h"
#include "treemodel.h"
#include "newEmployeedialog.h"
#include "newDepartmentdialog.h"
#include "movedialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model=new TreeModel();
    model->buildSampleModel();
    ui->treeView->setModel(model);
    //at the beginning all the tabs are disabled
    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
}
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_DeleteButton_clicked()
{
    //Delete
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    if(current.isValid()){
        //using bool QAbstractItemModel::removeRow ( int row, const QModelIndex & parent = QModelIndex() )
        //for this bool QAbstractItemModel::removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() )
        //[virtual] is defined in treemodel.cpp
        //if(   ui->treeView->model()->removeRow(current.row(),current.parent())){
        if(model->getType(item)==CompanyType){
            Company* cmp;
            cmp= item->getItemData()->value<Company*>();
            delete cmp;

            model->removeRow(current.row(),current.parent());

        }else  if(model->getType(item)==DepartmentType){
            //checking if the parent is a company or a department(a department could be
            //a direct department of the company or a subdepartment) so that the right remove function
            //will be used in order to delete the department from the parent's list
            TreeItem* parentItem= item->parent();
            Department* dpt;
            dpt= item->getItemData()->value<Department*>();
            if(model->getType(parentItem)==CompanyType){
                Company* parentCmp=parentItem->getItemData()->value<Company*>();
                parentCmp->removeDepartment(dpt);
            }
            if(model->getType(parentItem)==DepartmentType){
                Department* parentDpt=parentItem->getItemData()->value<Department*>();
                parentDpt->removeSubdepartment(dpt);
            }
            rebuildModel();

        }else if(model->getType(item)==2){
            Employee* empl;
            empl= item->getItemData()->value<Employee*>();
            Department* parentDpt=item->parent()->getItemData()->value<Department*>();
            parentDpt->removeEmployee(empl);
            rebuildModel();
        }

        //updating the view for the tabs

        ui->tabWidget->setTabEnabled(0,false);
        ui->tabWidget->setTabEnabled(1,false);
        ui->tabWidget->setTabEnabled(2,false);

    }
}


void MainWindow::on_treeView_clicked()
{
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    if(model->getType(item)==CompanyType){
        companyTabinUse();
    }
    if(model->getType(item)==DepartmentType){
        departmentTabinUse();
    }
    if(model->getType(item)==EmployeeType){
        employeeTabinUse();
    }
}

void MainWindow::companyTabinUse(){
    ui->tabWidget->setTabEnabled(0,true);
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(0));
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    Company* tmp=item->getItemData()->value<Company*>();
    ui->companyName->setText(tmp->getName());
    QVector<Department*> Depts;
    Depts=tmp->getDepartments();
    //setting the maximum limit of the total Limit (designed by QDoubleSpinBox) to the highest
    //limit for double. The minimum limit is set in mainwindow.ui form
    ui->companyTotal->setMaximum(DBL_MAX);
    ui->companyTotal->setValue(tmp->total());
}

void MainWindow::departmentTabinUse(){
    ui->tabWidget->setTabEnabled(1,true);
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(1));
    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setTabEnabled(2,false);
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    Department* tmp=item->getItemData()->value<Department*>();
    ui->DepartmentName->setText(tmp->getName());
    if(tmp->getManager()!=NULL){
        //if manager exists show it in the tabwidget(in the QLineEdit) with black
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::black);
        ui->Manager->setPalette(*palette);
        ui->Manager->setText(tmp->getManager()->getName());
    }
    else{
        //if manager does not exist show it in the tabwidget(in the QLineEdit) with red
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::red);
        ui->Manager->setPalette(*palette);
        ui->Manager->setText("NO Manager");
    }
    //setting the maximum limit of the total Limit (designed by QDoubleSpinBox) to the highest
    //limit for double. The minimum limit is set in mainwindow.ui form
    ui->DepartmentTotal->setMaximum(DBL_MAX);
    ui->DepartmentTotal->setValue(tmp->total());
}

void MainWindow::employeeTabinUse(){
    ui->tabWidget->setTabEnabled(2,true);
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(2));
    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setTabEnabled(1,false);
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    Employee* tmp=item->getItemData()->value<Employee*>();
    ui->EmployeeName->setText(tmp->getName());
    //setting the maximum limit of the salary Limit (designed by QDoubleSpinBox) to the highest
    //limit for double. The minimum limit is set in mainwindow.ui form
    ui->EmployeeSalary->setMaximum(DBL_MAX);
    ui->EmployeeSalary->setValue(tmp->getSalary());
    ui->EmployeeAddress->setText(tmp->getAddress());
}


//as soon as cut button is clicked the salary resp. total will be cut
void MainWindow::on_CutButton_clicked()
{
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    if(model->getType(item)==CompanyType){
        Company* tmp;

        tmp= item->getItemData()->value<Company*>();
        tmp->cut();
        ui->companyTotal->setValue(tmp->total());

    }
    if(model->getType(item)==DepartmentType){
        Department* tmp;
        tmp= item->getItemData()->value<Department*>();
        tmp->cut();
        ui->DepartmentTotal->setValue(tmp->total());
    }
    if(model->getType(item)==EmployeeType){
        Employee* tmp;
        tmp= item->getItemData()->value<Employee*>();
        tmp->cut();
        ui->EmployeeSalary->setValue(tmp->getSalary());
    }

}

//set the employee(which is clicked on) as manager
void MainWindow::on_setManager_clicked(){
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    TreeItem* parentItem=item->parent();
    if(model->getType(item)==EmployeeType){
        Employee* empl;
        empl=item->getItemData()->value<Employee*>();
        Department* dpt=parentItem->getItemData()->value<Department*>();
        dpt->setManager(empl);

    }
}

void MainWindow::on_SaveButton_clicked()
{
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    if(model->getType(item)==CompanyType){
        Company* tmp;
        tmp=item->getItemData()->value<Company*>();
        //making sure the company has a not empty name
        if(ui->companyName->text().isEmpty()){
            QMessageBox cmpNameWarning;
            cmpNameWarning.setText("the company should have a name");
            cmpNameWarning.exec();
        }
        else{
            tmp->setName(ui->companyName->text());
            item->getItemData()->setValue<Company*>(tmp);
        }
    }
    if(model->getType(item)==DepartmentType){
        Department* tmp;
        tmp=item->getItemData()->value<Department*>();

        tmp->setName(ui->DepartmentName->text());
        if(ui->Manager->text().toStdString()!="NO Manager"){
        Employee* mng=tmp->getManager();
        mng->setName(ui->Manager->text());
        tmp->setManager(mng);
        }
        item->getItemData()->setValue<Department*>(tmp);

    }
    if(model->getType(item)==EmployeeType){
        Employee* tmp;
        tmp=item->getItemData()->value<Employee*>();
        tmp->setName(ui->EmployeeName->text());
        tmp->setAddress(ui->EmployeeAddress->text());
        //restrictions set for the salary field make sure the salary is always positive,so there is
        //no need for a double check
        tmp->setSalary(ui->EmployeeSalary->value());
        item->getItemData()->setValue<Employee*>(tmp);
    }
}
/*
 *slot for the developer's usage ,calling the correspondent
 *toConsole classes for printing the attributes of the object
 */
void MainWindow::on_PrintButton_clicked()
{
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    if(model->getType(item)==CompanyType){
        Company* tmp;
        tmp=item->getItemData()->value<Company*>();
        tmp->toConsole();
    }
    if(model->getType(item)==DepartmentType){
        Department* tmp;
        tmp=item->getItemData()->value<Department*>();

        tmp->toConsole();
    }
    if(model->getType(item)==EmployeeType){
        Employee* tmp;
        tmp=item->getItemData()->value<Employee*>();

        tmp->toConsole();
    }
}

void MainWindow::on_comboBox_activated(int index)
{

    //Insert
    QModelIndex current=ui->treeView->currentIndex();
    if(!current.isValid())
        return;





    //inserting a department for the company chosen on the tree
    if(index==0){
        QModelIndex parentIndex=ui->treeView->currentIndex();
        TreeItem* parentItem=model->getItem(parentIndex);
        if (model->getType(parentItem)!=CompanyType){
            //warning if the company was not clicked
            QMessageBox warning;
            warning.setText("please click on the company if you want to add a new department");
            warning.exec();
        }else{
            newDepartmentdialog* d=new newDepartmentdialog();
            d->exec();
            if(d->result()==QDialog::Accepted){
                //make a new Department using input fields
                Department* dpt=d->newdept;
                //add the new department to the parent company
                Company* cmp=parentItem->getItemData()->value<Company*>();
                cmp->addDepartment(dpt);
                rebuildModel();
            }
            delete d;
        }
    }
    //inserting a subdepartment for the department chosen on the tree
    if(index==1){
        QModelIndex parentIndex=ui->treeView->currentIndex();
        TreeItem* parentItem=model->getItem(parentIndex);
        if (model->getType(parentItem)!=DepartmentType){
            //warning if the department was not clicked
            QMessageBox warning;
            warning.setText("please click on a department if you want to add a new subdepartment");
            warning.exec();
        }

        else{
            newDepartmentdialog* d=new newDepartmentdialog();
            d->exec();
            if(d->result()==QDialog::Accepted){
                //make a new (sub)Department using the input fields
                Department* dpt=d->newdept;
                //add the new subdepartment to the parent department and rebuild the model
                Department* parentDpt=parentItem->getItemData()->value<Department*>();
                parentDpt->addSubDepartment(dpt);
                rebuildModel();
            }
            delete d;
        }
    }
    //inserting an employee for the department chosen on the tree
    if(index==2){
        QModelIndex parentIndex=ui->treeView->currentIndex();
        TreeItem* parentItem=model->getItem(parentIndex);
        if (model->getType(parentItem)!=DepartmentType){
            //warning if the department was not clicked
            QMessageBox warning;
            warning.setText("please click on a department if you want to add a new employee");
            warning.exec();
        }
        else{
            newEmployeedialog* d=new newEmployeedialog();
            d->exec();
            if(d->result()==QDialog::Accepted){
                //make a new Employee using the input fields
                Employee* empl=d->newempl;
                //add the new employee to the department object and rebuild the model
                Department* dpt=parentItem->getItemData()->value<Department*>();
                dpt->addEmployee(empl);
                rebuildModel();
            }
            delete d;
        }
    }
}

void MainWindow::on_Move_clicked()
{
    QModelIndex current=ui->treeView->currentIndex();
    TreeItem* item=model->getItem(current);
    TreeItem* parentItem=item->parent();
    MoveDialog* dialog=new MoveDialog(model);
    dialog->exec();
    //if the item to be moved is an employee
    if(model->getType(item)==EmployeeType){
        //pointer to the employee about to be moved
        Employee* sourceEmpl=item->getItemData()->value<Employee*>();
        if(dialog->result()==QDialog::Accepted){
            TreeItem* targetItem=model->getItem(dialog->getTarget());
            //if the employee is about to be moved under a department do it, otherwise the move action
            //is  not allowed(employee can not go under the company)
            if(model->getType(targetItem)==DepartmentType){
                //pointer to the department the employee is about to be moved to
                Department* targetDpt=targetItem->getItemData()->value<Department*>();
                //pointer to the parent department of the employee about to be moved
                Department* parentDpt=parentItem->getItemData()->value<Department*>();
                parentDpt->moveEmployee(sourceEmpl,targetDpt);
            }
            else{
                QMessageBox targetInvalidWarning;
                targetInvalidWarning.setText("the target of the movement should be a department");
                targetInvalidWarning.exec();
            }
        }
    }
    //if the item to be moved is a department
    //if the department is about to be moved under a department or the company do it, otherwise the move action
    //is  not allowed(subdepartment can not go under the employee)
    if(model->getType(item)==DepartmentType){
        //pointer to the department about to be moved
        Department* sourceDpt=item->getItemData()->value<Department*>();
        if(dialog->result()==QDialog::Accepted){
            TreeItem* targetItem=model->getItem(dialog->getTarget());
            /*
                 *if the target is a department
                 */
            if(model->getType(targetItem)==DepartmentType){
                //pointer to the department the employee is about to be moved to
                Department* targetDpt=targetItem->getItemData()->value<Department*>();
                //if tha parent is a department(department is a subdepartment)
                if(model->getType(parentItem)==DepartmentType){
                    //pointer to the parent department of the subdepartment about to be moved
                    Department* parentDpt=parentItem->getItemData()->value<Department*>();
                    parentDpt->moveSubdepartment(sourceDpt,targetDpt);
                }
                else if(model->getType(parentItem)==CompanyType){


                    //pointer to the parent department of the employee about to be moved
                    Company* parentCmp=parentItem->getItemData()->value<Company*>();
                    parentCmp->moveDepartment(sourceDpt,targetDpt);
                }
            }
            else if((model->getType(targetItem)==CompanyType)){
                /*
                             *if the target is a company
                             */
                Company* targetCmp=targetItem->getItemData()->value<Company*>();
                //if tha parent is a department(department is a subdepartment)
                if(model->getType(parentItem)==DepartmentType){
                    //pointer to the parent department of the subdepartment about to be moved
                    Department* parentDpt=parentItem->getItemData()->value<Department*>();
                    parentDpt->moveSubdepartment(sourceDpt,targetCmp);
                }
                else if(model->getType(parentItem)==CompanyType){

                    //pointer to the parent department of the employee about to be moved
                    Company* parentCmp=parentItem->getItemData()->value<Company*>();
                    parentCmp->moveDepartment(sourceDpt);
                }
            }
            //the target is neither a company nor a department
            else{
                QMessageBox targetInvalidWarning;
                targetInvalidWarning.setText("the target of the movement should be a department or a company");
                targetInvalidWarning.exec();
            }
        }
    }

    //assuming that the company is always the first child of the rootItem
    rebuildModel();
}


void MainWindow::rebuildModel(){
    model->buildModel(model->rootItem->child(0)->getItemData()->value<Company*>());
    ui->treeView->reset();
    ui->treeView->expandToDepth(0);
}


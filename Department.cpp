#include <QVector>
#include <iostream>
#include "Department.h"
#include "Company.h"
#include "Employee.h"
using namespace std;

Department::Department    (QObject *parent) :
    QObject(parent){

}
Department::Department(QString name){
    this->manager = NULL;
    this->name    = name;
}

Department::~Department(){
    removeSubdepartments();
    removeEmployees();
}


void Department::addEmployee(Employee *e)
{
    this->employees.append(e);
}

void Department::addSubDepartment(Department *d)
{
    this->subdepartments.append(d);
}

void Department::setManager(Employee *e)
{
    this->manager = e;
}

Employee *Department::getManager()
{
    return manager;
}
void Department::setName(QString name)
{
    this->name = name;
}

QString Department::getName() const
{
    return name;
}

QVector<Employee*> Department::getEmployees() const
{
    return employees;
}

QVector<Department *> Department::getDepartments()
{
    return subdepartments;
}
//deallocate memory
void Department::removeEmployees(){
    while(!employees.empty()){
        Employee* empl=employees.back();
        employees.pop_back();
        delete empl;
    }
}
//removing all the subdepartments
void Department::removeSubdepartments(){
    while(!subdepartments.empty()){
        Department* dpt=subdepartments.back();
        subdepartments.pop_back();
        delete dpt;
    }
}

void Department::cut()
{
    for(int i=0; i<employees.size(); i++)
    {
        employees.at(i)->cut();
    }
    for(int i=0; i<subdepartments.size(); i++)
    {
        subdepartments.at(i)->cut();
    }
}

double Department::total()
{
    double total = 0.0;
    for(int i=0; i<employees.size(); i++)
    {
        total += employees.at(i)->getSalary();
    }

    for(int i=0; i<subdepartments.size(); i++)
    {

        total += subdepartments.at(i)->total();
    }
    return total;
}

/*
 *this function was implemented for the developer's usage
 *it was used as a slot for the signal emitted by a button named "print" in
 *the mainwindow, if you want to use it just add a button in the mainwindow
 *and name it "print"
 */
void Department::toConsole() const{
    std::cout << "Department: " << name.toStdString() << ", " << employees.size() << " Employees, "
              << subdepartments.size() << " Subdepartments\n";
    for(int i=0; i<employees.size(); i++)
    {
        employees.at(i)->toConsole();
    }
    for(int i = 0; i < subdepartments.size(); i++){
        subdepartments.at(i)->toConsole();
    }
    std::cout << std::endl;
}
void Department::removeEmployee(Employee * empl){
    if(getManager()==empl){
        setManager(NULL);
    }
    int index= employees.indexOf(empl);
    if(index>-1){
        employees.remove(index);
        delete empl;
    }
    else{
        qWarning("THIS SHOULD NOT HAPPEN: could not find employee in department");
    }
}

void Department::removeSubdepartment(Department* dpt){
    int index=subdepartments.indexOf(dpt);
    if(index>-1){
    subdepartments.remove(index);
    delete dpt;
    }
    else{
         qWarning("THIS SHOULD NOT HAPPEN: could not find subdepartment in department");
    }
}

void Department::moveSubdepartment(Department *sourceDpt, Department *targetDpt){
    //if the subdepartment is about to be moved to itself do nothing!
    if(targetDpt!=sourceDpt){
    targetDpt->addSubDepartment(sourceDpt);
    int index=subdepartments.indexOf(sourceDpt);
    subdepartments.remove(index);
    }
}
void Department::moveSubdepartment(Department *sourceDpt, Company *targetCmp){
    targetCmp->addDepartment(sourceDpt);
    int index=subdepartments.indexOf(sourceDpt);
    subdepartments.remove(index);
}

void Department::moveEmployee(Employee *sourceEmpl, Department *targetDpt){
    targetDpt->addEmployee(sourceEmpl);
    int index=employees.indexOf(sourceEmpl);
    employees.remove(index);
    if(manager==sourceEmpl){
        setManager(NULL);
    }
}

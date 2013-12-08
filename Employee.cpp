#include <iostream>
#include "Employee.h"
Employee::Employee
(QObject *parent) :
    QObject(parent){
}
Employee::Employee(QString name, QString address, double salary){
    this->name= name;
    this->address= address;
    this->salary= salary;
}

Employee::~Employee(){}


QString Employee::getName() const
{
    return name;
}

void Employee::setName(QString name)
{
    this->name = name;
}

QString Employee::getAddress()
{
    return address;
}

void Employee::setAddress(QString address)
{
    this->address = address;
}

double Employee::getSalary()
{
    return salary;
}

void Employee::setSalary(double salary)
{
    this->salary = salary;
}

void Employee::cut()
{
    this->salary = salary/2.0;
}
/*
 *this function was implemented for the developer's usage
 *it was used as a slot for the signal emitted by a button named "print" in
 *the mainwindow, if you want to use it just add a button in the mainwindow
 *and name it "print"
 */
void Employee::toConsole() const{
    std::cout << "Employee: " << name.toStdString() << std::endl;
    std::cout << "Salary: " << salary << std::endl;
}


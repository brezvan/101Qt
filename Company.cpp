#include <QString>
#include <QVector>
#include <iostream>
#include "Company.h"
#include "Department.h"

Company::Company(QObject *parent) :
    QObject(parent){

}
Company::Company(QString name){
    m_name=name;
}



Company::~Company(){
    removeDepartments();

}

QString Company::toQString(){
    return getName();
}

void Company::setName(QString name){
    m_name=name;
}
QString Company::getName() const {
    return m_name;
}
void Company::addDepartment(Department* dep)
{
    this->departments.append(dep);
}

QVector<Department*> Company::getDepartments(){
    return departments;
}

void Company::cut()
{
    for(int i=0; i<departments.size(); i++)
    {
        departments.at(i)->cut();
    }
}

double Company::total()
{

    double total = 0.0;
    for(int i=0; i<departments.size(); i++)
    {

        total += departments.at(i)->total();
    }
    return total;
}
//deallocate memory
void Company::removeDepartments(){
    while(!departments.empty()){
        Department* dpt=departments.back();
        departments.pop_back();
        delete dpt;
    }
}
//deallocate memory
void Company::removeDepartment(Department *dpt){
   int index= departments.indexOf(dpt);
   if(index>-1){
    departments.remove(index);
   delete dpt;
}
   else{
        qWarning("THIS SHOULD NOT HAPPEN: could not find department in company");
   }
}
/*
 *this function was implemented for the developer's usage
 *it was used as a slot for the signal emitted by a button named "print" in
 *the mainwindow, if you want to use it just add a button in the mainwindow
 *and name it "print"
 */
void Company::toConsole(){
    std::cout << "Company: " << m_name.toStdString() << ", " << departments.size() << " Departments:\n";
    for (int i = 0; i < departments.size(); i++){
        departments.at(i)->toConsole();
    }
    std::cout << std::endl;
}


void Company::moveDepartment(Department *sourceDpt){
    departments.append(sourceDpt);
    int index=departments.indexOf(sourceDpt);
    departments.remove(index);
}
void Company::moveDepartment(Department *sourceDpt, Department *targetDpt){
    //if the department is about to be moved to itself then do nothing!
    if(targetDpt!=sourceDpt){
    targetDpt->addSubDepartment(sourceDpt);
    int index=departments.indexOf(sourceDpt);
    departments.remove(index);
    }
}

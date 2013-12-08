#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <QtGui>
#include <QtCore>
#include <QObject>
#include <QMetaType>

class Employee;
class Company;

class Department:public  QObject
{
    Q_OBJECT
public:
    explicit Department(QObject* parent=0);
    Department(QString name);
    ~Department();
    void addEmployee(Employee* e);
    void addSubDepartment(Department* d);
    void setManager(Employee* e);
    Employee* getManager();
    void setName(QString name);
    QString getName() const;
    QVector<Employee*> getEmployees() const;
    QVector<Department*> getDepartments();
    void removeSubdepartment(Department* dpt);
    void removeSubdepartments();
    void removeEmployees();
    //remove one single employee
    void removeEmployee(Employee* empl);
    //moving a subdepartment to another department
    void moveSubdepartment(Department* sourceDpt,Department* targetDpt);
    //moving a subdepartment to the company and removing its pointer from the
    //parent's list
    void moveSubdepartment(Department *sourceDpt,Company *targetCmp);
    //moving an employee from the department to another department and removing its pointer
    //from the parent's list
    void moveEmployee(Employee* sourceEmpl,Department* targetDpt);
    void cut();
    double total();
    //for deleloper's usage, printing attributes of the department
    void toConsole() const;

private:
    QString name;
    Employee* manager;
    //feature:Nesting is implemented with two homogenous containers
    QVector<Employee*> employees;
    QVector<Department*> subdepartments;
};

Q_DECLARE_METATYPE(Department*);
QDebug operator<<(QDebug dbg, const Department &department);

#endif // DEPARTMENT_H


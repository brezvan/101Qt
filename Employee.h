#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QtGui>
#include <QtCore>
#include <QObject>
#include <QMetaType>
class Employee:public QObject
{
    Q_OBJECT
public:
    explicit Employee(QObject* parent=0);
    Employee(QString name, QString address, double salary);
    ~Employee();
    void setName(QString name);
    void setAddress(QString address);

    QString getName() const;
    QString getAddress();
    double getSalary();

    void setSalary(double salary);
    void cut();
    //for developer's usage printing the employees attributes
    void toConsole() const;
private:
    QString name;
    QString address;
    double salary;
};
//To enable the type to be used with QVariant
Q_DECLARE_METATYPE(Employee*);
//To allow us to see a readable description of each Employee object
//when it is sent to the debug output stream, we define a streaming operator
QDebug operator<<(QDebug dbg, const Employee &employee);

#endif // EMPLOYEE_H



#ifndef COMPANY_H
#define COMPANY_H
#include <QVector>
#include <QString>
#include <QObject>
#include <QMetaType>

class Department;

class Company:public QObject
{
    Q_OBJECT
private:
    QString m_name;
    QVector<Department*> departments;
public:
    explicit Company(QObject *parent = 0);
    Company(QString name);
    ~Company();
    QString getName() const;
    void setName(QString name);
    void cut();
    double total();
    QString toQString();
    QVector<Department *> getDepartments();
    void addDepartment(Department *dep);
    void removeDepartments();
    void removeDepartment(Department* dpt);
    //move a department to the company and removing its
    //pointer from the parent's list (what happens is that
    //the department will be deleted and appended again but at the end of the
    //departments vector)
    void moveDepartment(Department* sourceDpt);
    void moveDepartment(Department* sourceDpt,Department* targetDpt);
    //for develepor's usage printing certain attributes of the company
    void toConsole();
};
Q_DECLARE_METATYPE(Company*);


#endif // COMPANY_H


#ifndef DIALOG_H
#define DIALOG_H
#include <QString>
#include <QDialog>
#include <QAbstractButton>
#include "Employee.h"
#include "mainwindow.h"
namespace Ui {
/*
 *dialog popping pop when a new employee is about to be inserted
 *getting the name of the new employee
 *
 */
class newEmployeedialog;
}

class newEmployeedialog : public QDialog
{
    Q_OBJECT
    
public:

    ~newEmployeedialog();

    Employee* newempl;

    explicit newEmployeedialog();
private slots:


  void on_ok_clicked();

  void on_cancel_clicked();

private:
    Ui::newEmployeedialog *ui;

};

#endif // DIALOG_H

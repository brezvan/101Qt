#ifndef NEWDEPARTMENT_H
#define NEWDEPARTMENT_H
#include <QDialog>
#include "Department.h"
namespace Ui {
/*dialog popping up when a new Department/Subdepartment
 *is going to be inserted, getting the name of the new department/subdepartment
 */
class newDepartmentdialog;
}

class newDepartmentdialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit newDepartmentdialog();
    ~newDepartmentdialog();
    Department* newdept;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::newDepartmentdialog *ui;
};

#endif // NEWDEPARTMENT_H

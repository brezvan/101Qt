#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "treemodel.h"
#include "newEmployeedialog.h"

namespace Ui {
/*
 *the view in the MV architecture
 */
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    TreeModel *model;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_DeleteButton_clicked();
    void on_treeView_clicked();
    void on_CutButton_clicked();
    void on_SaveButton_clicked();
    //a slot for developer's usage (see toConsole function in Company,Department,Employee classes)
    void on_PrintButton_clicked();

    /*for adding department/subdepartment/employee a combobox is designed
    *the parent node should be clicked on the tree before clicking on
    *the combobox
    *if the wrong type of parent is chosen a warning message will appear
    *ex. if the company is chosen as the parent an addEmployee is clicked
    */
    void on_comboBox_activated(int index);
    /*any time you want to set an employee as the manager or change the manager
    *the button setManager emits a signal and this slot handles it.that is
    *if a manager already exists it will be no more the manager and the chosen
    *employee will be the manager
    */
    void on_setManager_clicked();
    /*Move button will emit the signal and this slot will handle it.
     *a dialog will apear showing the whole company treeView allowing the
     *user to choose a source for the movement, if the movement is structurally possible
     *it will be done
     */
    void on_Move_clicked();
    
private:
    Ui::MainWindow *ui;

/*
 *virtual functions impelemented
 */
//  bool  removeRows( int , int, const QModelIndex &);
//  bool insertRows(int , int , const QModelIndex &);
  void companyTabinUse();
  void departmentTabinUse();
  void employeeTabinUse();
  //rebuilding the model and resetting the view
  void rebuildModel();

};


#endif // MAINWINDOW_H




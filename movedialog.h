#ifndef MOVEDIALOG_H
#define MOVEDIALOG_H
#include <QDialog>
#include"treemodel.h"
#include"treeitem.h"
namespace Ui {
/*
 *Dialog popping up when the Move signal is emitted
 *showing the company tree so the user can choose the source of the movement
 *the target's index will be passed with the getTarget() function
 */
class MoveDialog;
}

class MoveDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MoveDialog();
    MoveDialog(TreeModel*);
    ~MoveDialog();
    QModelIndex getTarget();
private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::MoveDialog *ui;
    QModelIndex m_targetIndex;
    TreeModel* m_model;
};

#endif // MOVEDIALOG_H

#include "movedialog.h"
#include "ui_movedialog.h"
#include "treemodel.h"
#include"mainwindow.h"
#include"iostream"

MoveDialog::MoveDialog(TreeModel* m_model) :
    ui(new Ui::MoveDialog)
{
    ui->setupUi(this);
    ui->treeView->setModel(m_model);
    std::cout<<"Model set in MoveDialog"<<std::endl;
}

MoveDialog::~MoveDialog()
{
    delete ui;
}

void MoveDialog::on_ok_clicked()
{

    QModelIndex current=ui->treeView->currentIndex();
    m_targetIndex=current;

    accept();

}

void MoveDialog::on_cancel_clicked()
{
    reject();
}
QModelIndex MoveDialog::getTarget(){
    return m_targetIndex;
}

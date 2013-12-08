#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QtGui>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "treeitem.h"
#include "ItemTypes.h"
#include "Company.h"
#include "Department.h"
#include "Employee.h"
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit  TreeModel( QObject *parent = 0);
    ~TreeModel();
    //building the default model
    void buildSampleModel();
    //building the model for a certain company
    void buildModel(Company*);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent ) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent ) const;
    int columnCount(const QModelIndex &parent) const;
    bool removeRows(int , int , const QModelIndex &);
    //getting the treeItem by the index of the tree element
    TreeItem *getItem(const QModelIndex &) const;
    TreeItem *rootItem;
    /*
     * Inserts the given child beneath the parrent in the view as well as in the model
     */
    void insertCompany(TreeItem *);
    void insertDepartment(TreeItem * , TreeItem * );
    void insertEmployee(TreeItem* ,TreeItem* );
    void insertSubdepartment(TreeItem* ,TreeItem* );
    //moving a TreeItem
    void moveItem(TreeItem* d,TreeItem* to);
    //getting the type name in form of an enum
    ItemTypes getType(TreeItem*);
};

#endif // TREEMODEL_H

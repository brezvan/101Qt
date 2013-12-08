#ifndef TREEITEM_H
#define TREEITEM_H
#include <QtGui>
#include <QList>
#include <QVariant>
#include <QVector>
#include <QMimeData>
/*
 *items of the QTreeView,containing data of type QVariant
 *they must have a parent except for the rootItem of the tree
 *which has no parent
 */
class TreeItem
{
public:
    TreeItem(const QVariant &data, TreeItem *parent = 0);
    ~TreeItem();
    //used only when the model is first constructed
    void appendChild(TreeItem *child);
    //obtaining info about any child
    TreeItem *child(int row);
    int childCount() const;
    //number of columns asscociated with the item
    int columnCount() const;
    //obtaining data in each column
    QString data() const;
    //row number
    int row() const;
    //get parent
    TreeItem *parent();
     bool removeChildren(int , int );
    //insert certain number of children and grant them certain number of columns
     bool insertChildren(int , int , int);
     QVariant* getItemData();
private:
    QList<TreeItem*> childItems;
    QVariant itemData;
    TreeItem *parentItem;
};


#endif

#include <QVector>
#include <QList>
#include <iostream>
#include "treeitem.h"
#include "Company.h"
#include "Department.h"
#include "Employee.h"
//record the parent and the data in each column
TreeItem::TreeItem(const QVariant &data,TreeItem* parent)
{
    qDebug() << "Constructing TreeItem with QVariant type: " << data.typeName() ;
    parentItem = parent;
    itemData = data;
}
TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}
void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}
//return child at row
TreeItem *TreeItem::child(int row)
{
    return childItems.value(row);
}
int TreeItem::childCount() const
{
    return childItems.size();
}
// reports the item's location within its parent's list of items
int TreeItem::row() const
{
    if (parentItem){
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
    }
    return 0;
}
//number of columnls of data in an item
int TreeItem::columnCount() const
{
    //return itemData.count();
    return 1;
}

//get data in the column(we just have 1 column), return defaul values if column number out of range
QString TreeItem::data( ) const
{
    if(QString(itemData.typeName()).startsWith("QString")){
        QString tmp = itemData.value<QString>();
        return tmp;
    }
    if(QString(itemData.typeName()).startsWith("Company")){
        Company* tmp;
        tmp= (itemData.value<Company*>());
        return tmp->getName();
    }
    if(QString(itemData.typeName()).startsWith("Department")){
        Department* tmp;
        tmp=itemData.value<Department*>();
        return tmp->getName();
    }
    if(QString(itemData.typeName()).startsWith("Employee")){
        Employee* tmp;
        tmp=itemData.value<Employee*>();
        return tmp->getName();
    }
    qDebug()<<"QVariant type could not be resolved: " << itemData.typeName() << ", we are in trouble";
    return QString();
}
//the root item has no parent
TreeItem *TreeItem::parent()
{
    return parentItem;
}
bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QList<QVariant> data;
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}
QVariant* TreeItem::getItemData(){
    return &itemData;
}


#include <QtGui>
#include <iostream>
#include "treemodel.h"
#include "treeitem.h"
#include "Company.h"
#include "Department.h"
#include "Employee.h"
#include"ItemTypes.h"
TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{

    QVariant root;
    QString s="101Companies";
    root.setValue<QString>(s);
    rootItem=new TreeItem(root);
}
TreeModel::~TreeModel()
{
    delete rootItem;
}

void TreeModel::buildSampleModel(){
    Employee* manager1=new Employee("manager1","cologne",12345);
    Employee* manager2=new Employee("manager2","Berlin",12345);
    Company* c=new Company("Google");
    Department*d1=new Department("dep1");
    Department*d2=new Department("dep2");
    Department*d3=new Department("dep3");
    Department*d4=new Department("dep4");
    Employee* emp1=new Employee("Joe","malibu",123);
    Employee* emp2=new Employee("Jack","Koblenz",1234);
    Employee* emp3=new Employee("Dexter","Miami",1234);
    Employee* emp4=new Employee("Walter","Boston",1234);
    c->addDepartment(d1);
    c->addDepartment(d2);
    d1->addSubDepartment(d3);
    d3->addSubDepartment(d4);
    d1->addEmployee(manager1);
    d1->addEmployee(emp1);
    d1->addEmployee(emp2);
    d2->addEmployee(manager2);
    d2->addEmployee(emp3);
    d1->setManager(manager1);
    d2->setManager(manager2);
    d3->addEmployee(emp4);
    d3->setManager(emp4);
    buildModel(c);
}

/*get index for accessing data
indexes are created when referencing components by the row and column and parent modelindex
if an invalid modelindex is specified as the parent, we assume that a top-level item is being
referred to; otherwise, we obtain the data pointer from the model index with its internalPointer()
function and use it to reference a TreeItem object
*/
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
const
{

    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    {
        if (!child.isValid())return QModelIndex();

        TreeItem *childItem = static_cast<TreeItem*>(child.internalPointer());
        TreeItem *parentItem = childItem->parent();

        if (parentItem == rootItem)
            return QModelIndex();

        return createIndex(parentItem->row(), 0, parentItem);
    }
}
int TreeModel::rowCount(const QModelIndex &parent) const
{

    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();

}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data();
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{

    if(rootItem==NULL){
        std::cout << "rootItem is NULL" << std::endl;
    }

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data();

    return QVariant();
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) return item;
    }else{
        qWarning( "TreeModel::getItem Index not Valid" );
    }
    return rootItem;
}
bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

/*bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    bool success;
    beginInsertRows(parent, position, position + rows - 1);
    endInsertRows();
    return success;
}*/

void TreeModel::insertCompany(TreeItem *c){
    rootItem->appendChild(c);
}

void TreeModel::insertEmployee(TreeItem *d, TreeItem *e){

    d->appendChild(e);
    //parentDepartment->addEmployee(newEmployee);
}
void TreeModel::insertSubdepartment(TreeItem *parentItem, TreeItem *childItem){
    Department* childDepartment=childItem->getItemData()->value<Department*>();
    parentItem->appendChild(childItem);
    QVector<Employee*>employees=childDepartment->getEmployees();
    for(int h=0;h<employees.size();h++){
        QVariant employeeVariant;
        employeeVariant.setValue<Employee*>(employees.at(h));
        TreeItem* employeeItem=new TreeItem(employeeVariant,childItem);
        insertEmployee(childItem,employeeItem);
    }
    //parentDepartment->addSubDepartment(newDepartment);
    if(childDepartment->getDepartments().size()!=0){
        QVector<Department*>subSubdpts=childDepartment->getDepartments();
        for(int i=0;i<subSubdpts.size();i++){
            QVariant subDptVariant;
            subDptVariant.setValue<Department*>(subSubdpts.at(i));
            TreeItem* subDptItem=new TreeItem(subDptVariant, childItem);
            insertSubdepartment(childItem,subDptItem);
        }
    }
}
void TreeModel::insertDepartment(TreeItem*c, TreeItem *d){
    c->appendChild(d);
}
void TreeModel::buildModel(Company* company){
    beginResetModel();
    if(rootItem->child(0)){
        rootItem->removeChildren(0,1);
        qDebug()<<"model successfully deleted";
    }
    QVariant cmpVariant;
    cmpVariant.setValue<Company*>(company);
    TreeItem *cmpItem = new TreeItem(cmpVariant, rootItem);
    insertCompany(cmpItem);
    QVector<Department*> departments=company->getDepartments();
    for(int i=0;i<departments.size();i++){
        QVariant departmentVariant;
        departmentVariant.setValue<Department*>(departments.at(i));
        TreeItem* departmentItem=new TreeItem(departmentVariant,cmpItem);
        insertDepartment(cmpItem,departmentItem);
        for(int k=0;k<departments.at(i)->getEmployees().size();k++){
            QVariant employeeVariant;
            employeeVariant.setValue<Employee*>(departments.at(i)->getEmployees().at(k));
            TreeItem* employeeItem=new TreeItem(employeeVariant,departmentItem);
            insertEmployee(departmentItem,employeeItem);
        }
        QVector<Department*> subDepartments=departments.at(i)->getDepartments();
        for(int j=0;j<subDepartments.size();j++){
            QVariant subDepartmentVariant;
            subDepartmentVariant.setValue<Department*>(subDepartments.at(j));
            TreeItem* subDepartmentItem=new TreeItem(subDepartmentVariant,departmentItem);
            insertSubdepartment(departmentItem,subDepartmentItem);
        }
    }
    endResetModel();
}

ItemTypes TreeModel::getType(TreeItem * item){
    if( QString(item->getItemData()->typeName()).startsWith("Company")){
        return CompanyType;
    }
    else  if( QString(item->getItemData()->typeName()).startsWith("Department")){
        return DepartmentType;
    }
    else   if( QString(item->getItemData()->typeName()).startsWith("Employee")){
        return EmployeeType;
    }

    qWarning("type is not valid!");

}

#ifndef COMPANYTREEVIEW_H
#define COMPANYTREEVIEW_H
#include <QTreeView>
/*this class is derived from QTreeView and adds no special functionality to it
 *it is only created and used to make an exclusive QTreeView for the company
 *and for the possible extensions to the QTreeView
 */
class CompanyTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CompanyTreeView(QWidget *parent = 0);

signals:

public slots:
    
};

#endif // COMPANYTREEVIEW_H

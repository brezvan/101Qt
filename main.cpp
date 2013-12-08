#include <QtGui/QApplication>
#include <QVariant>
#include <iostream>
#include <QDoubleValidator>
#include "mainwindow.h"
#include "Company.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

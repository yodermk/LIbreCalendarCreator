#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Yoder Internet Development");
    a.setOrganizationDomain("yoderdev.com");
    MainWindow w;
    w.show();

    return a.exec();
}

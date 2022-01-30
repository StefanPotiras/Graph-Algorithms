#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    QApplication b(argc, argv);
    MainWindow y;
   y.show();
    return b.exec();

}

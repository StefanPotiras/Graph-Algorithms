#include "mainwindow.h"
#include"graf.h"
#include <QApplication>

int main(int argc, char *argv[])
{Graf jj;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

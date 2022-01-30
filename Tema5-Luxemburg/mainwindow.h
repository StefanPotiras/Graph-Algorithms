#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"graf.h"
#include"node.h"
#include"arc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*virtual void mouseReleaseEvent(QMouseEvent*e);
     virtual void mouseMoveEvent(QMouseEvent*e);*/
    virtual void mousePressEvent(QMouseEvent*e);
    virtual void paintEvent(QPaintEvent *event);

   std::unordered_set<int>path;
   void deseneazaDrumul();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Graf g;
    void schimbaCoord();
    Node n1,n2,mid;

};
#endif // MAINWINDOW_H

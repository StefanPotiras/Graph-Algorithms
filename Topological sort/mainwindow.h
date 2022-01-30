#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graf.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent*e);
     virtual void mouseMoveEvent(QMouseEvent*e);
    virtual void mousePressEvent(QMouseEvent*e);
    virtual void paintEvent(QPaintEvent *event);

    ~MainWindow();

private slots:




  const QLineF &returneazaCoordArc(const QLineF &liniePrincipala);
   QLineF returneazaCoordSageata(const QLineF &liniePrincipala);
   void on_pushButton_clicked();

   void on_Random_clicked();

   void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Graf g;
    Node firstNode, secondNode;
    bool drawNode=true,drawArc=true,isOriented=true;
    Node nodCurent;
    int metodaDesen=0;
  int nPaths;
   void generateNRandomPath();
    std::vector<Node> generateRandomParh();
      void giveCoordToPoints();
      void generateAllArcsP(std::vector<Node>arc);
};
#endif // MAINWINDOW_H

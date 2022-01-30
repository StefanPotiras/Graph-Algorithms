#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"node.h"
#include <QMainWindow>
#include"graf.h"
#include<vector>
#include<random>
#include <algorithm>
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Graf g;
    Node firstNode, secondNode;

    bool drawNode=false,drawArc,isOriented;


    void generateNRandomCycles();
    void generateNRandomPath();
    void generateAllArcs(std::vector<Node>arc);
    void giveCoordToPoints();
    int nPaths,nCycles;
    int dimensiuneDesen=0;
};
#endif // MAINWINDOW_H

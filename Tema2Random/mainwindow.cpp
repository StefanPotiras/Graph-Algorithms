#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPointF>
#include<iostream>
#include<QMessageBox>
#include<QDebug>
#include <random>
#include <stdio.h>
#include"node.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->spinBox_2->hide();
    ui->spinBox_3->hide();
    ui->pushButton_2->hide();
    ui->pushButton_4->hide();
     ui->pushButton_6->hide();

}
int myrandom (int i) { return std::rand()%i;}


MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<Node> MainWindow::generateRandomParh()
{
    std::vector<Node> t;
    for(auto &index:g.GetNoduri())
    {
        t.push_back(index);
    }
    std::random_shuffle(t.begin()+1, t.end());
QDebug deb = qDebug();
   deb<<"------------------------------------"<<"\n";
    for(int i=0;i<t.size();i++)
    { if(i<t.size()-1)
       deb<<t[i].getNumber()<<"->";
        else
            deb<<t[i].getNumber()<<"\n";
    }
     deb<<"------------------------------------"<<"\n";
    return t;

}
void MainWindow::generateAllArcsP(std::vector<Node>arc)
{ Node one,two;
    std::vector<Node>temp=g.GetNoduri();
    for(int i=0;i<arc.size()-2;i++)
    {if(arc[i].getNumber()!=temp[temp.size()-1].getNumber())
        {one.setNumber(arc[i].getNumber());
        two.setNumber(arc[i+1].getNumber());
        Arc arcLocal(one,two);
        if(g.existaArc(arcLocal)!=true)
            g.AddArc(arcLocal);
        }
        else
            break;
    }
   /* one.setNumber(arc[arc.size()-2].getNumber());
    two.setNumber(arc[arc.size()-1].getNumber());
    Arc arcLocal(one,two);
    if(g.existaArc(arcLocal)!=true)
        g.AddArc(arcLocal);*/

}
std::vector<Node> MainWindow::generateRandomCycles()
{
    std::vector<Node> t;
    for(auto &index:g.GetNoduri())
    {
        t.push_back(index);
    }
    std::random_shuffle(t.begin(), t.end());
    t.push_back(t[0]);
    QDebug deb = qDebug();
     deb<<"------------------------------------"<<"\n";
        for(int i=0;i<t.size();i++)
        { if(i<t.size()-1)
           deb<<t[i].getNumber()<<"<->";
            else
                deb<<t[i].getNumber()<<"\n";
        }
     deb<<"------------------------------------"<<"\n";

    return t;

}

void MainWindow::generateNRandomCycles()
{
    for(int i=0;i<nCycles;i++)
    {
        generateAllArcs(generateRandomCycles());
    }

    giveCoordToPoints();
}


void MainWindow::generateAllArcs(std::vector<Node>arc)
{ Node one,two;
    for(int i=0;i<arc.size()-2;i++)
    {
        one.setNumber(arc[i].getNumber());
        two.setNumber(arc[i+1].getNumber());
        Arc arcLocal(one,two);
        if(g.existaArc(arcLocal)!=true)
            g.AddArc(arcLocal);
    }
    one.setNumber(arc[arc.size()-2].getNumber());
    two.setNumber(arc[arc.size()-1].getNumber());
    Arc arcLocal(one,two);
    if(g.existaArc(arcLocal)!=true)
        g.AddArc(arcLocal);

}
const QLineF &MainWindow::returneazaCoordArc(QLineF liniePrincipala)
{//arce[arce.size()-1].getFirstPoint().getPoint(),arce[arce.size()-1].getSecondPoint().getPoint()
    QPointF primulPunct,alDoileaPunct;

    qreal length = liniePrincipala.length();
    if (length > qreal(28.)) {
        QPointF edgeOffset((liniePrincipala.dx() * 20) / length,
                           (liniePrincipala.dy() * 20) / length);


        primulPunct = liniePrincipala.p1() + edgeOffset;
        alDoileaPunct = liniePrincipala.p2() - edgeOffset;
    } else {
        primulPunct = alDoileaPunct = liniePrincipala.p1();}
    QLineF linie(primulPunct,alDoileaPunct);
    return linie;
}

QLineF MainWindow::returneazaCoordSageata( QLineF liniePrincipala)
{  QLineF angleline;
    angleline.setP1(liniePrincipala.p2());
    angleline.setLength(10);
    angleline.setAngle(liniePrincipala.angle()-160);
    return angleline;
}
void MainWindow::paintEvent(QPaintEvent *event)
{QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));

    if(drawNode)
    {

        std::vector<Node>noduri=g.GetNoduri();
        for(auto& nod:noduri)
        {
            { QRect r(nod.getPoint().x()-20,nod.getPoint().y()-20,40,40);
                p.setBrush(Qt::SolidPattern);
                p.setBrush(Qt::green);
                p.drawEllipse(r);

                const std::string &str=std::to_string(nod.getNumber());

                QString qstr = QString::fromStdString(str);
                p.drawText(nod.getPoint().x(),nod.getPoint().y()+6,QString(qstr));
            }


        }
        std::vector<Arc> arce=g.GetArce();

        for(auto&arc:arce)
        {

            QLineF linieOrientata(arc.getFirstPoint().getPoint(),arc.getSecondPoint().getPoint());
            linieOrientata=returneazaCoordArc(linieOrientata);
            p.drawLine(linieOrientata);

            QLineF angleline=returneazaCoordSageata(linieOrientata);
            p.drawLine(angleline);
            angleline.setAngle(linieOrientata.angle()+160);
            p.drawLine(angleline);

        }

    }

    update();
}
void MainWindow::giveCoordToPoints()
{
    QPointF centru(1000,530);
    QLineF liniePrincipala;
    liniePrincipala.setP1(centru);
    liniePrincipala.setLength(200);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,360);

    int x=dis(gen);

    int y=x+360;
    for(int i=0;i<g.getNumberOfNodes();i++)
    { if(g.verificaSuprapunereNoduri(liniePrincipala.p2())!=true)
        {   g.modificaNodul(i,liniePrincipala.p2());
            g.modificaArce(i,liniePrincipala.p2());
            if(x!=y)
            { liniePrincipala.setAngle(liniePrincipala.angle()-x);

            }
            else{
                x=y-360+10;
                y=x+360;
                liniePrincipala.setAngle(liniePrincipala.angle()-x);

            }
            x=x+30;
        }
        else
        {i--;
            x=dis(gen);
            y=x+360;
            liniePrincipala.setAngle(liniePrincipala.angle()-x);
        }


        update();
    }
}

void MainWindow::generateNRandomPath()
{
    for(int i=0;i<nPaths;i++)
    {
        generateAllArcsP(generateRandomParh());
    }

    giveCoordToPoints();

}



void MainWindow::on_pushButton_clicked()
{
    QString t;
    t = ui->spinBox->text();

    if(t.toInt()<=0)
    {
        QMessageBox::information(this,"EROARE","Numarul nu este bun!");
    } else if(t.toInt()>0)
    {
        g.introduceNoduri(t.toInt());
        ui->spinBox->hide();
        ui->pushButton->hide();
        ui->pushButton_4->show();
        ui->pushButton_6->show();
    }
 drawNode=false;
}


void MainWindow::on_pushButton_2_clicked()
{



    QString t;t = ui->spinBox_2->text();
    nPaths=t.toInt();
    generateNRandomPath();
    drawNode=true;
     g.GenerareListaAdiacenta();
    update();
}


void MainWindow::on_pushButton_3_clicked()
{


    QString t;t = ui->spinBox_3->text();
    nCycles=t.toInt();
    generateNRandomCycles();
    drawNode=true;
     g.GenerareListaAdiacenta();
    update();
}





void MainWindow::on_pushButton_5_clicked()
{
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->spinBox_2->hide();
    ui->spinBox_3->hide();
    ui->pushButton_2->hide();
    ui->pushButton_4->hide();
    ui->spinBox->show();
    ui->pushButton->show();
    ui->pushButton_6->hide();
     drawNode=false;
    g.clear();
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->spinBox_3->show();
    ui->pushButton_3->show();
    ui->pushButton_6->hide();
    ui->pushButton_4->hide();
     drawNode=false;
}




void MainWindow::on_pushButton_4_clicked()
{
    ui->pushButton_2->show();
       ui->pushButton_3->hide();
       ui->spinBox_2->show();
       ui->pushButton_4->hide();

        drawNode=false;
}


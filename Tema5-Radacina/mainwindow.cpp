#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include<QDebug>
#include<QMessageBox>
#include <random>
#include <ctime>
#include <stdio.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    drawNode=false;
        drawArc=false;
        if(e->button()==Qt::RightButton )
        {int index=0;


            Node n(e->pos());
            if(g.GetNoduri().size()==0)
            {
                n.setNumber(1);
                g.AddNod(n);
                drawNode=true;
                update();
                firstNode=Node();
            }
            else if(g.GetNoduri().size()>0)
            {

                if(g.verificaSuprapunereNoduri(n.getPoint())==false)
                {  index=g.GetLastNode().getNumber();
                    n.setNumber(index++);
                    g.AddNod(n);
                    drawNode=true;
                    update();
                    firstNode=Node();

                }
            }

        }
        else
        {
            QPointF p= e->localPos();
            std::vector<Node> noduri=g.GetNoduri();
            Node foundNode;
            for(auto&n:noduri)
            {
                if(fabs(n.getPoint().x()-p.x())<40 &&fabs(n.getPoint().y()-p.y())<40)
                {
                    foundNode=n;
                    break;
                }
            }
            if(foundNode.getNumber()==-1)
                return ;
            if(firstNode.getNumber()==-1)
            { firstNode=foundNode;

            }
            else if(g.verifyMultiGraf(firstNode,foundNode)==false && foundNode.getNumber()!=firstNode.getNumber()) {

                secondNode=foundNode;
                //g.modificaArce(firstNode,coordFin);
                g.AddArc(Arc(firstNode,secondNode));
                firstNode=Node();
                secondNode=Node();
                drawArc=true;
                update();
            }
            else if(g.verifyMultiGraf(firstNode,foundNode)==true)
            {
                firstNode.setNumber(-1);
            }
        }

        if(e->button()==Qt::LeftButton && g.verificaSuprapunereNoduriDrag(e->pos(),nodCurent)&& nodCurent.getNumber()!=-1)
        {

            qDebug()<<e->pos().x()<<"-";
            g.modificaNodul(nodCurent.getNumber(),nodCurent.getPoint());
            qDebug()<<e->pos().x()<<"-"<<e->pos().y();
            g.modificaArce(nodCurent,nodCurent.getPoint());
            update();


        }

        nodCurent.setNumber(-1);

}
const QLineF &MainWindow::returneazaCoordArc(const QLineF &liniePrincipala)
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

QLineF MainWindow::returneazaCoordSageata(const QLineF &liniePrincipala)
{  QLineF angleline;
    angleline.setP1(liniePrincipala.p2());
    angleline.setLength(30);
    angleline.setAngle(liniePrincipala.angle()-160);
    return angleline;
}

void MainWindow::paintEvent(QPaintEvent *event)
{  QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::black,3,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));

   if(g.getNumberOfNodes())
    {

        std::vector<Node>noduri=g.GetNoduri();
        for(auto& nod:noduri)
        { if(nod.getNumber()!=nodCurent.getNumber())
            { QRect r(nod.getPoint().x()-20,nod.getPoint().y()-20,40,40);
                p.setBrush(Qt::SolidPattern);
                p.setBrush(Qt::green);
                p.drawEllipse(r);

                const std::string &str=std::to_string(nod.getNumber());

                QString qstr = QString::fromStdString(str);

                p.drawText(nod.getPoint().x(),nod.getPoint().y()+6,QString(qstr));
            }
            else if(nod.getNumber()==nodCurent.getNumber())
            {
                QRect r(nod.getPoint().x()-20,nod.getPoint().y()-20,40,40);
                p.setBrush(Qt::SolidPattern);
                p.setBrush(Qt::yellow);
                p.drawEllipse(r);

                const std::string &str=std::to_string(nod.getNumber());

                QString qstr = QString::fromStdString(str);

                p.drawText(nod.getPoint().x(),nod.getPoint().y()+6,QString(qstr));

            }
        }

        for(auto&arc:g.GetArce())
        {

            QLineF linieOrientata(arc.getFirstPoint().getPoint(),arc.getSecondPoint().getPoint());
            linieOrientata=returneazaCoordArc(linieOrientata);

            p.drawLine(linieOrientata);

            QLineF angleline=returneazaCoordSageata(linieOrientata);

            p.drawLine(angleline);
            angleline.setAngle(linieOrientata.angle()+160);
            p.drawLine(angleline);

        }
        update();

        if(g.GetLastNode().getNumber()!=nodCurent.getNumber())
        {
            Node n=g.GetLastNode();
            p.setPen(QPen(Qt::black));
            p.setBrush(Qt::SolidPattern);
            p.setBrush(Qt::red);
            QRect r(n.getPoint().x()-20,n.getPoint().y()-20,40,40);
            p.drawEllipse(r);
            const std::string &str=std::to_string(n.getNumber());

            QString qstr = QString::fromStdString(str);
            p.drawText(n.getPoint().x(),n.getPoint().y()+6,QString(qstr));
        }
        else  if(drawArc)
        {
            p.setPen(QPen(Qt::green));


            QLineF linieOrientata(g.GetArce()[g.GetArce().size()-1].getFirstPoint().getPoint(),g.GetArce()[g.GetArce().size()-1].getSecondPoint().getPoint());
            linieOrientata=returneazaCoordArc(linieOrientata);

            QLineF angleline=returneazaCoordSageata(linieOrientata);
            p.drawLine(angleline);
            angleline.setAngle(linieOrientata.angle()+160);
            p.drawLine(angleline);


        }
    }

update();
}
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        QPoint coord=e->pos();
        for(auto&n:g.GetNoduri())
        {
            if(fabs(n.getPoint().x()-coord.x())<40 &&fabs(n.getPoint().y()-coord.y())<40)
            { qDebug()<<"Nodul"<<n.getNumber()<<"a fost selectat!";
                nodCurent=n;
                update();
                break;
            }
        }

    }

}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton)&& nodCurent.getNumber()>=0)
    {
        g.modificaNodul(nodCurent.getNumber(),e->pos());
        update();
        g.modificaArce(nodCurent,e->pos());
        //coordFin=e->pos();
        update();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_verificaRadacina_clicked()
{
    g.GenerareListaAdiacenta();
    g.gasesteRadacina();
    g.clear();
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include<QDebug>
#include<QMessageBox>
#include <random>
#include <ctime>
#include <stdio.h>
#include<queue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g.readFromXML();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons()==Qt::RightButton)
    { int ok=0;
        QPointF temp=e->pos();
        for(auto index: g.GetNoduri())
        {
            if(fabs(index.getCoordDesen().x()-temp.x())<3 &&fabs(index.getCoordDesen().y()-temp.y())<3)
            {
                n1=index;
                ok=1;
                qDebug()<<"nu";
                update();
                break;
            }
        }
        if(ok==0)
        { std::pair<int,float>pereche;
            pereche.second=3.40282e+038;
            qDebug()<<"da";
            for (auto index:g.GetNoduri())
            {
                float distanta = sqrt((temp.x() - index.getCoordDesen().x()) * (temp.x() - index.getCoordDesen().x())) +
                        ((temp.y() - index.getCoordDesen().y()) * (temp.y() - index.getCoordDesen().y()));
                if(distanta<pereche.second)
                {
                    pereche.second=distanta;
                    pereche.first=index.getNumber();
                }
            }
            n1=g.GetNoduri()[pereche.first];
            qDebug()<<n1.getNumber();
            update();
        }

    }
    else if(e->buttons()==Qt::LeftButton )
    {int ok=0;
        QPointF temp=e->pos();

        for(auto index: g.GetNoduri())
        {
            if(fabs(index.getCoordDesen().x()-temp.x())<3 &&fabs(index.getCoordDesen().y()-temp.y())<3)
            {
                n2=index;
                ok=1;
                qDebug()<<"nu";
                update();
                break;
            }
        }
        if(ok==0)
        { std::pair<int,float>pereche;
            pereche.second=3.40282e+038;
            qDebug()<<"da";
            for (auto index:g.GetNoduri())
            {
                float distanta = sqrt((temp.x() - index.getCoordDesen().x()) * (temp.x() - index.getCoordDesen().x())) +
                        ((temp.y() - index.getCoordDesen().y()) * (temp.y() - index.getCoordDesen().y()));
                if(distanta<pereche.second)
                {
                    pereche.second=distanta;
                    pereche.first=index.getNumber();
                }
            }
            n2=g.GetNoduri()[pereche.first];
            qDebug()<<n1.getNumber();
            update();
        }
    }

    else if(e->button()==Qt::MidButton)
    { int ok=0;
        QPointF temp=e->pos();

        for(auto index: g.GetNoduri())
        {
            if(fabs(index.getCoordDesen().x()-temp.x())<3 &&fabs(index.getCoordDesen().y()-temp.y())<3)
            {
                mid=index;
                ok=1;
                qDebug()<<"nu";
                update();
                break;
            }
        }
        if(ok==0)
        { std::pair<int,float>pereche;
            pereche.second=INFINITY;
            qDebug()<<"da";
            for (auto index:g.GetNoduri())
            {
                float distanta = sqrt((temp.x() - index.getCoordDesen().x()) * (temp.x() - index.getCoordDesen().x())) +
                        ((temp.y() - index.getCoordDesen().y()) * (temp.y() - index.getCoordDesen().y()));
                if(distanta<pereche.second)
                {
                    pereche.second=distanta;
                    pereche.first=index.getNumber();
                }
            }
            mid=g.GetNoduri()[pereche.first];
            qDebug()<<mid.getNumber();
            update();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    update();
    int imp=300;
    float point=1;
    QPainter p(this);
    p.setBrush(Qt::SolidPattern);
    p.setBrush(Qt::red);

    for(auto& index:g.GetNoduri())
    {
        float x = width() / ((g.longMax - g.longMin) / imp) *((index.getPoint().y() - g.longMin) / imp);
        x += 100;
        float y = height() / ((g.latMax - g.latMin) / imp) * ((g.latMax - index.getPoint().x()) / imp);
        y += 100;
        if(index.getNumber()!=n1.getNumber())

        {   QPen pen;

            pen.setColor(Qt::black);
            p.setPen(pen);
            g.modificaNodul(index.getNumber(),QPointF(x,y));
            p.drawEllipse(x - point / 2,y - point / 2, point, point);
        }
        if(index.getNumber()==n1.getNumber())
        {   QPen pen;
            pen.setWidth(10);
            p.setBrush(Qt::red);
            pen.setColor(Qt::red);
            p.setPen(pen);
            g.modificaNodul(index.getNumber(),QPointF(x,y));
            p.drawEllipse(x - point / 2,y - point / 2, point, point);
            update();
        }
        if(index.getNumber()==n2.getNumber())
        {QPen pen;
            pen.setWidth(10);
            p.setBrush(Qt::red);
            pen.setColor(Qt::red);
            p.setPen(pen);
            g.modificaNodul(index.getNumber(),QPointF(x,y));
            p.drawEllipse(x - point / 2,y - point / 2, point, point);
            update();
        }
        if(index.getNumber()==mid.getNumber())
        {
            QPen pen;
            pen.setWidth(10);
            p.setBrush(Qt::red);
            pen.setColor(Qt::red);
            p.setPen(pen);
            g.modificaNodul(index.getNumber(),QPointF(x,y));
            p.drawEllipse(x - point / 2,y - point / 2, point, point);
            update();
        }


    }
    QPainter t(this);
    t.setRenderHint(QPainter::Antialiasing);
    for (auto arc : g.GetArce())
    {
        float x = width() / ((g.longMax - g.longMin) / imp) * ((arc.getFirstPoint().getPoint().y() - g.longMin) / imp);
        x += 100;
        float y = height() / ((g.latMax - g.latMin) / imp) * ((g.latMax - arc.getFirstPoint().getPoint().x()) / imp);
        y += 100;

        float x2 = width() / ((g.longMax - g.longMin) / imp) * ((arc.getSecondPoint().getPoint().y() - g.longMin) / imp);
        x2 += 100;
        float y2 = height() / ((g.latMax - g.latMin) / imp) * ((g.latMax-arc.getSecondPoint().getPoint().x()) / imp);
        y2 += 100;


        if(path.find(arc.getFirstPoint().getNumber())!=path.end() &&
              path.find(arc.getSecondPoint().getNumber())!=path.end())
        {
            QPen pen(Qt::red,0.8);
            t.setPen(pen);
            t.drawLine(x, y, x2, y2);
              update();
        }
        else
        {
            QPen pen(Qt::black, 0.3);
            t.setPen(pen);
            t.drawLine(x, y, x2, y2);
              update();
        }

    }

}


void MainWindow::schimbaCoord()
{ int imp=300;
    for(auto& index:g.GetNoduri())
    {
        float x = width() / ((g.longMax - g.longMin) / imp) *((index.getPoint().y() - g.longMin) / imp);
        x += 100;
        float y = height() / ((g.latMax - g.latMin) / imp) * ((g.latMax - index.getPoint().x()) / imp);
        y += 100;
        g.modificaNodul(index.getNumber(),QPointF(x,y));

    }

    update();
}


void MainWindow::on_pushButton_clicked()
{
    path.clear();
    path=g.returnPath(n1,n2,true);
    qDebug()<<"main";
    path.insert(path.begin(),n1.getNumber());

}


void MainWindow::on_pushButton_2_clicked()
{   path.clear();
    path=g.returnPath(mid,n2,false);
    path.insert(path.begin(),mid.getNumber());

}


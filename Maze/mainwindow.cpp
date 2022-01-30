#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    int x=80,y=100,latura=40;
    paint.setPen(Qt::cyan);
    for(auto& index:g.getMatrice())
    {
        for(auto& index1:index)
        {

            if(index1==0)
            {     paint.setPen(Qt::cyan);
               paint.setBrush(Qt::black);

                paint.drawRect(QRect(x,y,latura,latura));
            }
            else if(index1==1)
            { paint.setPen(Qt::cyan);
                paint.setBrush(Qt::white);
                paint.drawRect(QRect(x,y,latura,latura));
            }
            else if(index1==2)
            {
                paint.setBrush(Qt::red);
                paint.drawRect(QRect(x,y,latura,latura));
                paint.setPen(Qt::black);
                paint.drawText(QPointF(x+10,y+23),"Exit");
            }
            else if(index1==3)
            {
                paint.setBrush(Qt::cyan);
                paint.drawRect(QRect(x,y,latura,latura));
                paint.setPen(Qt::black);
                paint.drawText(QPointF(x+2,y+23),"Intrare");
            }
            else if(index1==4)
            { paint.setPen(Qt::cyan);
                paint.setBrush(Qt::green);
                paint.drawRect(QRect(x,y,latura,latura));
            }
            x+=latura;
        }
        y+=latura;
        x=80;
    }

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));

    int distance = 60;
    int begin = x*(dimensiuneDesen/2+3);

    for (auto& arc: g.GetArce()) {
        p.setPen(Qt::black);
        QPointF firstPoint = arc.getFirstPoint().getPoint();
        QPointF secondPoint = arc.getSecondPoint().getPoint();
        QLineF lineBetween;
        lineBetween.setLine(firstPoint.y()*distance + begin + 20, firstPoint.x()*distance + 70, secondPoint.y()*distance + begin + 20, secondPoint.x()*distance + 70);
        p.drawLine(lineBetween);
    }


    for (auto& nod : g.GetNoduri()) {

        if(nod.getEnd()==true)
        { p.setBrush(Qt::red);
            QRect r(nod.getPoint().y()*distance + begin ,nod.getPoint().x()*distance + 50, 40,40);
            p.drawEllipse(r);
        }
        else if(nod.getStart()==true)
        {
            p.setBrush(Qt::blue);
            QRect r(nod.getPoint().y()*distance + begin ,nod.getPoint().x()*distance + 50, 40,40);
            p.drawEllipse(r);
        }
        else if(nod.getPath()==true)
        {
            p.setBrush(Qt::green);
            QRect r(nod.getPoint().y()*distance + begin ,nod.getPoint().x()*distance + 50, 40,40);
            p.drawEllipse(r);
        }
        else
        {
            p.setBrush(Qt::white);
            QRect r(nod.getPoint().y()*distance + begin ,nod.getPoint().x()*distance + 50, 40,40);
            p.drawEllipse(r);
        }
        p.setPen(Qt::black);
        p.drawText(QPointF(nod.getPoint().y()*distance + begin + 15, nod.getPoint().x()*distance + 70), QString::number(nod.getNumber()));
    }


    update();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    g.readMatrice();
    g.transformareInGraf();
    g.GenerareListaAdiacenta();
    dimensiuneDesen=g.returneazaDimensiuneLinie();
    //qDebug()<<dimensiuneDesen;

}

void MainWindow::on_pushButton_2_clicked()
{
    std::vector<Node>final=g.returneazaNoduriSfarsit();

    Node start=g.returneazaNodStar();

    std::vector<Node>path=g.formeazaDrum(start);

    for(auto& finish:final)
    {
        while(finish.getNumber()!=start.getNumber())
        {
            //qDebug()<<finish.getNumber();
            g.modificaNodul(finish.getNumber());
            g.modificaMatrice(finish.getPoint());
            finish=path[finish.getNumber()];
        }
    }
}


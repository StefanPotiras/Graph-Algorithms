#include "graf.h"
#include<iostream>
#include"node.h"
#include<fstream>
#include<QFile>
#include<QDebug>
#include<QTextStream>

#include<QMessageBox>
#include<unordered_map>

bool Graf::verificaSuprapunereNoduri(QPointF curentCoord)
{

    for(auto&n:noduri)
    {
        if(fabs(n.getPoint().x()-curentCoord.x())<40 &&fabs(n.getPoint().y()-curentCoord.y())<40)

        {  return true;

        }
    }
    return false;
}
bool Graf::existaArc(Arc localArc)
{
    for(auto &index:arce)
    {
        if(localArc.getFirstPoint().getNumber()==index.getFirstPoint().getNumber() &&localArc.getSecondPoint().getNumber()==index.getSecondPoint().getNumber())
        {
            return true;
        }
    }
    return false;
}

void Graf::introduceNoduri(const int &numarNoduri)
{
    for (int i=0;i<numarNoduri;i++)
    {
        Node n(i);
        noduri.push_back(n);

    }
}


void Graf::GenerareListaAdiacenta()
{listaAdiacenta.clear();
    listaAdiacenta.resize(noduri.size());
    for(int i=0;i<noduri.size();i++)
    {
        for(auto &index:arce)
        {
            if(index.getFirstPoint().getNumber()==i)
            {
                listaAdiacenta[i].push_back(index.getSecondPoint());
               // qDebug()<<index.getSecondPoint().getNumber();
            }


        }
    }
    int nr=0;
    std::ofstream out("C:\\Users\\stefa\\Documents\\Tema2Random\\out.txt");
    out<<"Numarul de noduri-->"<<noduri.size()<<"\n";
    for(auto& index1:listaAdiacenta)
    { out<<nr<<"-->";
        for  (auto& index:index1)
        {
            out<<index.getNumber()<<" ";
        }
        nr++;
        out<<"\n";
    }
    out<<"\n";
}


void Graf::clear()
{
    noduri.clear();
    arce.clear();
}

void Graf::modificaNodul(int index,QPointF temp_point)
{
    noduri[index].setPoint( temp_point);
}

void Graf::modificaArce(int index1,QPointF coord)
{
    for (auto &index:arce)
    {
        if(index.getFirstPoint().getNumber()==index1)
        {
            index.modificaCoordF1(coord);
        }
        else if(index.getSecondPoint().getNumber()==index1)
        {
            index.modificaCoordF2(coord);
        }
    }
}


bool Graf::verificaSuprapunereNoduriDrag(QPointF curentCoord, Node curentNod)
{
    for(auto&n:noduri)
    {
        if(fabs(n.getPoint().x()-curentCoord.x())<40 &&fabs(n.getPoint().y()-curentCoord.y())<40 && curentNod.getNumber()!=n.getNumber())
        {  return true;

        }
    }
    return false;
}

std::vector<Arc> Graf::GetArce()
{   //this->GenerareMatriceAdiacenta();
    return arce;
}

std::vector<Node> Graf::GetNoduri()
{    //this->GenerareMatriceAdiacenta();
    return noduri;
}

void Graf::AddNod(Node n)
{
    n.setNumber(noduri.size());
    noduri.push_back(n);
}

void Graf::AddArc(Arc a)
{
    arce.push_back(a);
}

void Graf::DrawGraf(QPainter *p)
{

}

Node Graf::GetLastNode()
{
    return noduri[noduri.size()-1];
}

int Graf::getNumberOfNodes()
{
    return noduri.size();
}

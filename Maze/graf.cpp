#include "graf.h"
#include<iostream>
#include"node.h"
#include<fstream>
#include<QFile>
#include<QDebug>
#include<QTextStream>
#include<queue>
#include<QMessageBox>
#include<map>

bool Graf::verificaSuprapunereNoduri(QPointF curentCoord)
{

    for(auto&n:noduri)
    {
        if(fabs(n.getPoint().x()-curentCoord.x())<20 &&fabs(n.getPoint().y()-curentCoord.y())<20)

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

Node Graf::returneazaNodul(QPointF coord)
{
    for(auto index:noduri)
    {
        if(index.getPoint()==coord )
            return index;
    }

}

void Graf::afiseazaArcele()
{std::ofstream out("C:\\Users\\stefa\\Documents\\Maze\\out.txt");

    for(auto index:arce)
    {
        out<<index.getFirstPoint().getNumber()<<"--"<<index.getSecondPoint().getNumber()<<"\n";
    }

}

std::vector<Node> Graf::returneazaNoduriSfarsit()
{std::vector<Node>finalNodes;
   for(auto&index:noduri)
   {
       if(index.getEnd()==true)
           finalNodes.push_back(index);
   }
   return finalNodes ;
}

Node Graf::returneazaNodStar()
{
    for(auto&index:noduri)
    {
        if(index.getStart()==true)
            return index;
    }
}

void Graf::modificaNodul(int nr)
{
    for(auto& index:noduri)
    {
        if(index.getNumber()==nr)
            index.setPath(true);
    }
}



void Graf::modificaMatrice(QPointF temp)
{
    if( matriceGraf[temp.x()][temp.y()]!=2)
        matriceGraf[temp.x()][temp.y()]=4;
}

int Graf::returneazaDimensiuneLinie()
{
    return matriceGraf[0].size();
}

std::vector<Node> Graf::formeazaDrum(Node start)
{

    std::vector<bool>visited;
    std::vector<Node>predecesori;
    std::vector<Node>toateNodurile;

   for(int i=0;i<getNumberOfNodes();i++)
   {
       visited.push_back(false);
   }

    for (int i=0;i<getNumberOfNodes();i++)
    {
        Node temp(-1);
        temp.setStart(false);
        temp.setEnd(false);
        temp.setPoint(QPointF(-1,-1));
        predecesori.push_back(temp);
    }
    std::queue<Node>coada;
    coada.push(start);
    Node top=start;

    while(!coada.empty())

    {  top=coada.front();
        coada.pop();
        if(visited[top.getNumber()]==false)
        {
            //toateNodurile.push_back(top);
            visited[top.getNumber()]=true;
        }

       for(auto& index:listaAdiacenta[top.getNumber()])
        {
            Node nodCurent=index;
            if(visited[nodCurent.getNumber()]==false)
                coada.push(nodCurent);

            if(nodCurent.getNumber()!=top.getNumber()&& predecesori[nodCurent.getNumber()].getNumber()==-1)
                predecesori[nodCurent.getNumber()]=top;
        }
    }
    return predecesori;
}

void Graf::introduceNoduri(const int &numarNoduri)
{
    for (int i=0;i<numarNoduri;i++)
    {   Node n(i);
        noduri.push_back(n);

    }
}

void Graf::transformareInGraf()
{  Node temp;
    QPointF coord;
    int p=0;
    for (int i=0;i<matriceGraf.size();i++)
    {
        for (int j=0;j<matriceGraf[i].size();j++)
        {
            if(matriceGraf[i][j]==2)
            {
                temp.setEnd(true);
                temp.setStart(false);
                coord.setX(i);
                coord.setY(j);
                temp.setPoint(coord);
                temp.setNumber(p);
                p++;
                noduri.push_back(temp);

            }
            else if(matriceGraf[i][j]==1)
            {
                temp.setEnd(false);
                temp.setStart(false);
                coord.setX(i);
                coord.setY(j);
                temp.setPoint(coord);
                temp.setNumber(p);
                p++;
                noduri.push_back(temp);
            }
            else if(matriceGraf[i][j]==3)
            {
                temp.setEnd(false);
                temp.setStart(true);
                coord.setX(i);
                coord.setY(j);
                temp.setPoint(coord);
                temp.setNumber(p);
                p++;
                noduri.push_back(temp);
            }


        }
    }
    formareArce();
}

void Graf::formareArce()
{Node t1,t2;
    QPointF coord;

    for (int i=0;i<matriceGraf.size();i++)
    {
        for (int j=0;j<matriceGraf[i].size()-1;j++)
        {
            if(matriceGraf[i][j+1]!=0 && matriceGraf[i][j]!=0)
            {  coord.setX(i);
                coord.setY(j);
                t1=returneazaNodul(coord);
                coord.setY(j+1);
                t2=returneazaNodul(coord);
                Arc arcTemp(t1,t2);
                if(existaArc(arcTemp)==false)
                    arce.push_back(Arc(t1,t2));
            }

        }
    }
    for (int i=1;i<matriceGraf.size();i++)
    {
        for (int j=0;j<matriceGraf[i].size();j++)
        {
            if(matriceGraf[i-1][j]!=0 &&matriceGraf[i][j]!=0)
            {
                coord.setX(i);
                coord.setY(j);
                t1=returneazaNodul(coord);
                coord.setX(i-1);
                t2=returneazaNodul(coord);
                Arc arcTemp(t1,t2);
                if(existaArc(arcTemp)==false)
                    arce.push_back(Arc(t1,t2));
            }
        }
        afiseazaArcele();
    }
}


void Graf::GenerareListaAdiacenta()
{listaAdiacenta.clear();
    listaAdiacenta.resize(getNumberOfNodes());
    for(int i=0;i<noduri.size();i++)
    { std::vector<Node>temp;
        for(auto &index:arce)
        {
            if(index.getFirstPoint().getNumber()==i)
            {
                listaAdiacenta[i].push_back(index.getSecondPoint());
            }
            else if(index.getSecondPoint().getNumber()==i)
                 listaAdiacenta[i].push_back(index.getFirstPoint());

        }

    }
    int nr=0;



    QFile file ("C:\\Users\\stefa\\Documents\\Maze\\out.txt");
    if(file.open(QIODevice::WriteOnly|QIODevice::Text| QIODevice::Append |QFile::Truncate))
    {
        QTextStream stream(&file);
        stream<<"Numarul de noduri-->"<<noduri.size()<<"\n";
        for(auto& index1:listaAdiacenta)
        { stream<<nr<<"-->";
            for  (auto index:index1)
            {
                stream<<index.getNumber()<<" ";
            }
            nr++;
            stream<<"\n";
        }
        stream<<"\n";
        file.close();
    }

}

void Graf::readMatrice()
{int nrCol,nrLine,temp;
    std::ifstream fin("C:\\Users\\stefa\\Documents\\Maze\\in.txt");
    fin>>nrCol>>nrLine;
    matriceGraf.resize(nrCol);
    for(int i=0;i<nrCol;i++)
    { for(int j=0;j<nrLine;j++)
        {
            fin>>temp;
            matriceGraf[i].push_back(temp);

        }

    }

}

std::vector<std::vector<int> > Graf::getMatrice()
{
    return matriceGraf;
}
bool Graf::verifyMultiGraf(Node firstNode, Node secondNode)
{
    for(auto &a:arce)
    {
        if(a.getFirstPoint().getNumber()==firstNode.getNumber()&& a.getSecondPoint().getNumber()== secondNode.getNumber())
        {

            return true;
        }

    }
    return false;
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

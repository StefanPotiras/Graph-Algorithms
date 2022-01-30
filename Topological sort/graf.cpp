#include "graf.h"
#include<iostream>
#include"node.h"
#include<fstream>
#include<QFile>
#include<QDebug>
#include<QTextStream>

#include <QMessageBox>
#include <queue>
#include <stack>
#include<unordered_map>

void Graf::GenerareMatriceAdiacenta(const bool &isOrin)
{matriceAdiacenta.clear();
    if(isOrin==false)
    {
        for(int i=0;i<noduri.size();i++)
        { std::vector<int>tempVect(noduri.size(),0);
            for(auto index:arce)
            {
                if(index.getFirstPoint().getNumber()==i )
                {
                    tempVect[index.getSecondPoint().getNumber()]=1;
                }
                else if(index.getSecondPoint().getNumber()==i)
                {
                    tempVect[index.getFirstPoint().getNumber()]=1;
                }
            }
            matriceAdiacenta.push_back(tempVect);

        }
    }
    else if(isOrin==true)
    {
        for(int i=0;i<noduri.size();i++)
        { std::vector<int>tempVect(noduri.size(),0);
            for(auto index:arce)
            {
                if(index.getFirstPoint().getNumber()==i )
                {
                    tempVect[index.getSecondPoint().getNumber()]=1;
                }
            }
            matriceAdiacenta.push_back(tempVect);

        }
    }
    QFile file ("C:\\Users\\stefa\\Documents\\Tema1_Potiras\\out.txt");

    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
    {
        QTextStream stream(&file);
        for(auto index:matriceAdiacenta)
        {
            for(auto index1:index)
            {
                stream<<index1<<" ";
            }
            stream<<"\n";
        }
        stream<<"\n";
        file.close();
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
    std::ofstream out("C:\\Users\\stefa\\Documents\\Tema1_Potiras\\out.txt");
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

void Graf::updateGraf()
{

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

void Graf::modificaArce(Node nodulCurent,QPointF coord)
{
    for (auto &index:arce)
    {
        if(index.getFirstPoint().getNumber()==nodulCurent.getNumber())
        {
            index.modificaCoordF1(coord);
        }
        else if(index.getSecondPoint().getNumber()==nodulCurent.getNumber())
        {
            index.modificaCoordF2(coord);
        }
    }
}

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



bool Graf::isCyclic()
{
    std::queue<int>coadaVerificare;
    std::vector<int>vectorVerificare(getNumberOfNodes(),0);
    int n=getNumberOfNodes();
    for(int i=0;i<n;i++)
    {
        for(auto index:listaAdiacenta[i])
        {
            vectorVerificare[index.getNumber()]++;
        }
    }
    for(int i=0;i<n;i++)
    {
        if(vectorVerificare[i]==0)
        {
            coadaVerificare.push(i);
        }
    }
    int numarSurse=0;
    while(!coadaVerificare.empty())
    {
        int val=coadaVerificare.front();
        coadaVerificare.pop();
        numarSurse++;
        for(auto index:listaAdiacenta[val])
        {
            vectorVerificare[index.getNumber()]--;
            if(vectorVerificare[index.getNumber()]==0)
            {
                coadaVerificare.push(index.getNumber());
            }
        }
    }
    if(numarSurse==n)
    {
        return false;
    }
    return true;
}
bool Graf::allTrue(std::vector<bool>allTrue1)
{
    for(auto index:allTrue1)
    {
        if(index==false)
            return true ;
    }
    return false;
}
Node Graf::returneazaNodul(int n)
{
    for (auto index:noduri)
    {
        if(index.getNumber()==n)
            return index;
    }

}


void Graf::adaugaArcPtSortare(int n1, int n2)
{
    Node nod1,nod2;
    nod1=returneazaNodul(n1);
    nod2=returneazaNodul(n2);
    arce.push_back(Arc(nod1,nod2));
}



void Graf::introduceNoduri(const int &numarNoduri)
{
    for (int i=0;i<numarNoduri;i++)
    {
        Node n;
        n.setNumber(i);
        noduri.push_back(n);

    }
}

void Graf::DFS(std::stack<std::pair<int, int> > &stack, std::vector<std::pair<int, int> > &arceTemp, std::vector<bool> &visited, std::vector<bool> &visitedSource)
{
    while (!stack.empty())
    {

        int s = stack.top().first;
        int plecare=stack.top().second;
        stack.pop();
        if (!visited[s])
        {
            visited[s] = true;
            arceTemp.push_back(std::make_pair(s,plecare));

        }

        for(auto& index:listaAdiacenta[s])
        {
            if(!visited[index.getNumber()] && visitedSource[index.getNumber()]==false)

            {   stack.push(std::make_pair(index.getNumber(),s));
                visitedSource[index.getNumber()]=true;
            }
        }
    }
}
void Graf::sortareTopologica()
{

    std::vector<bool> visited(getNumberOfNodes(), false);
    std::vector<bool> visitedSource(getNumberOfNodes(), false);

    std::stack<std::pair<int,int>> stack;
    std::vector<std::pair<int,int>>arceTemp;


    std::stack<int>sort;
    if(isCyclic()==false)
    {while(allTrue(visited))
        {
            for(int i=0;i<visited.size();i++)
            {
                if(visited[i]==false)
                {
                    stack.push(std::make_pair(i,-1));
                    break;
                }
            }

            if(arceTemp.size()>0)
            {
                for(int i=0;i<arceTemp.size()-1;i++)
                {  if(arceTemp[i+1].second==arceTemp[i].first)
                        adaugaArcPtSortare(arceTemp[i].first,arceTemp[i+1].first);
                    else
                        adaugaArcPtSortare(arceTemp[i+1].second,arceTemp[i+1].first);

                }
                for(int i=arceTemp.size()-1;i>=0;i--)
                {
                    sort.push(arceTemp[i].first);
                }

                arceTemp.clear();

            }

            DFS(stack,arceTemp,visited,visitedSource);

        }
        if(arceTemp.size()>0)
        {
            for(int i=0;i<arceTemp.size()-1;i++)
            {  if(arceTemp[i+1].second==arceTemp[i].first)
                    adaugaArcPtSortare(arceTemp[i].first,arceTemp[i+1].first);
                else
                    adaugaArcPtSortare(arceTemp[i+1].second,arceTemp[i+1].first);

            }
            for(int i=arceTemp.size()-1;i>=0;i--)
            {
                sort.push(arceTemp[i].first);
            }

        }
        std::ofstream out("C:\\Users\\stefa\\Documents\\Tema1_Potiras\\sortare.out");

        while(sort.empty()==0)
        {
            out<<sort.top()<<" ";
            sort.pop();
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0, "UPSI", "GRAFUL NU TREBUIE SA CONTINA CICLURI!");
        messageBox.setFixedSize(800, 700);
        noduri.clear();
    }
}

void Graf::clearCicluri()
{
    arce.clear();
}

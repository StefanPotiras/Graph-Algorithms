#include "graf.h"
#include<QtXml/QDomDocument>
#include<QtXml/QDomCDATASection>
// Library needed for processing files
#include <QFile>
#include<QDebug>
#include<QPair>
#include<fstream>
#include <queue>
#include <unordered_set>
Graf::Graf()
{

}

void Graf::readFromXML()
{ //int id;
    QDomDocument xmlBOM;
    longMin =INT_MAX;
    longMax = 0;
    latMin = INT_MAX;
    latMax = 0;

    QFile f("C:\\Users\\stefa\\Documents\\Tema5-Luxemburg\\Luxemburg.xml");
    if (!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error while loading file";
        return;
    }
    xmlBOM.setContent(&f);
    f.close();

    QDomElement root = xmlBOM.documentElement();
    QDomElement Component = root.firstChild().toElement();

    QDomNodeList nodes = root.elementsByTagName("node");


    while (!Component.isNull())
    {
        if (Component.tagName() == "nodes")
        {

            QDomElement Child = Component.firstChild().toElement();

            float id, x, y;

            while (!Child.isNull())
            {

                id = Child.attribute("id").toFloat();

                x = Child.attribute("latitude").toFloat();


                y = Child.attribute("longitude").toFloat();

                if (x > latMax)
                    latMax = x;
                else
                    if (x < latMin)
                        latMin = x;

                if (y > longMax)
                    longMax = y;
                else
                    if (y < longMin)
                        longMin = y;

                Node v(QPointF(x, y), id);
                noduri.emplace_back(v);

                Child = Child.nextSibling().toElement();

            }

        }
        else
            if (Component.tagName() == "arcs")
            {
                QDomElement Child = Component.firstChild().toElement();

                float from, to,dist;

                while (!Child.isNull())
                {

                    from = Child.attribute("from").toFloat();

                    //std::cout << Child.attribute("to").toStdString() << "\n";
                    to = Child.attribute("to").toFloat();

                    dist=Child.attribute("length").toFloat();

                    Arc t(noduri[from], noduri[to],dist);
                    arce.emplace_back(t);

                    mapCost[noduri[from].getNumber()].insert(std::make_pair( noduri[to].getNumber(),dist));
                    mapCost[noduri[to].getNumber()].insert(std::make_pair( noduri[from].getNumber(),dist));


                    Child = Child.nextSibling().toElement();
                }

            }
        Component = Component.nextSibling().toElement();
    }

}


std::vector<std::vector<Node> > Graf::returneazaLista()
{
    return listaAdiacenta;
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
    noduri[index].setCoordDesen( temp_point);
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


Node Graf::GetLastNode()
{
    return noduri[noduri.size()-1];
}

int Graf::getNumberOfNodes()
{
    return noduri.size();
}



std::pair<std::vector<int>,std::vector<int>> Graf::Disk(Node source, Node n2 , bool varianta)
{
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>>priorityQu;

    std::vector<bool>vis(getNumberOfNodes(),false);
    std::vector<int>dist(getNumberOfNodes(),2147483647);
    std::vector<int>prev(getNumberOfNodes(),NULL);

    dist[source.getNumber()]=0;
    priorityQu.push(std::make_pair(0,source.getNumber()));

    while(!priorityQu.empty())
    {
        std::pair<int,int>temp=priorityQu.top();
        priorityQu.pop();
        if(temp.second==n2.getNumber() && varianta==true)
            break;

        if(vis[temp.second]==false)
        {vis[temp.second]=true;
        for(auto& index:mapCost[temp.second])
        {
            if(vis[index.first]==false)
            {
                int newDist=dist[temp.second]+index.second;
                if(newDist<dist[index.first])
                {  prev[index.first]=temp.second;
                    dist[index.first]=newDist;
                    priorityQu.push(std::make_pair(newDist,index.first));

                }
            }
        }
        }

    }

    return std::make_pair(dist,prev);
}

std::unordered_set<int> Graf::returnPath(Node source, Node final,bool varianta)
{
    std::pair<std::vector<int>,std::vector<int>>perecheVect=Disk(source,final,varianta);
    std::unordered_set<int>path;
    qDebug()<<"ia";
    if(varianta==false)
    {std::pair<int,int>pereche;
        pereche.first=2147483647;
        for(int i=0;i<perecheVect.first.size();i++)
        {
            if(perecheVect.first[i]<pereche.first && i!=source.getNumber())
            { pereche.first=perecheVect.first[i];
                pereche.second=i;
            }
        }
        if(perecheVect.first[pereche.second]==INFINITY)
                    return path;
                for(auto at=pereche.second;at!=NULL;at=perecheVect.second[at])
                {
                    path.insert(at);
                }

                return path;
    }
    else if(varianta==true)

    {
        if(perecheVect.first[final.getNumber()]==INFINITY)
            return path;
        for(auto at=final.getNumber();at!=NULL;at=perecheVect.second[at])
        {
            path.insert(at);
        }
        return path;
    }
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











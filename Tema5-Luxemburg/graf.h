#ifndef GRAF_H
#define GRAF_H

#include "node.h"
#include "arc.h"
#include<set>

#include <stack>
#include <unordered_map>
#include <unordered_set>
class Graf
{
private:
    std::vector<Node> noduri;
    std::vector<Arc> arce;
    std::unordered_map<int,std::set<std::pair<int,int>>>mapCost;
    std::pair<std::vector<int>,std::vector<int>> Disk(Node source,Node n2,bool varianta);



   std::vector<std::vector<int>>matriceAdiacenta;
   std::vector<std::vector<Node>>listaAdiacenta;

   bool allTrue(std::vector<bool>allTrue1);
   void adaugaArcPtSortare(int n1,int n2);
   Node returneazaNodul(int n);

public:

   int longMin,longMax,latMin,latMax;
 std::unordered_set<int> returnPath(Node source,Node final,bool varianta);
    Graf();
    void readFromXML();
    std::vector<Arc> GetArce();
    std::vector<Node>GetNoduri();
    void AddNod(Node n);
    void AddArc(Arc a);

    Node GetLastNode();
    int getNumberOfNodes();
    bool verifyMultiGraf(Node firstNode, Node secondNode);
    void updateGraf();

    void clear();

    void modificaNodul(int index,QPointF temp_point);
    void modificaArce(Node nodulCurent,QPoint coord);

    void GenerareListaAdiacenta();
     std::vector<std::vector<Node>> returneazaLista();
};

#endif // GRAF_H

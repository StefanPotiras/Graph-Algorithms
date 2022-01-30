#ifndef GRAF_H
#define GRAF_H

#include "node.h"
#include "arc.h"

#include <stack>

class Graf
{
    std::vector<Node> noduri;
    std::vector<Arc> arce;


   std::vector<std::vector<int>>matriceAdiacenta;
   std::vector<std::vector<Node>>listaAdiacenta;

   bool allTrue(std::vector<bool>allTrue1);
   void adaugaArcPtSortare(int n1,int n2);
   Node returneazaNodul(int n);

public:
void DFS(std::stack<std::pair<int,int>>&stack, std::vector<std::pair<int,int>>&arceTemp,std::vector<bool>&visited,std::vector<bool>&visitedSource);

void introduceNoduri(const int& numarNoduri);
void sortareTopologica();
void clearCicluri();

void GenerareMatriceAdiacenta(const bool &isOrin);
void GenerareListaAdiacenta();

bool existaArc(Arc localArc);
bool isCyclic();

std::vector<Arc> GetArce();
std::vector<Node>GetNoduri();
void AddNod(Node n);
void AddArc(Arc a);

void DrawGraf(QPainter *p);

Node GetLastNode();
int getNumberOfNodes();
bool verifyMultiGraf(Node firstNode, Node secondNode);
void updateGraf();

void clear();

void modificaNodul(int index,QPointF temp_point);
void modificaArce(Node nodulCurent,QPointF coord);

bool verificaSuprapunereNoduri(QPointF curentCoord);
bool verificaSuprapunereNoduriDrag(QPointF curentCoord,Node curentNod);
};

#endif // GRAF_H

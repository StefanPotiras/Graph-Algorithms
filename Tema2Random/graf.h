#ifndef GRAF_H
#define GRAF_H

#include "node.h"
#include "arc.h"

class Graf
{
    std::vector<Node> noduri;
    std::vector<Arc> arce;

   std::vector<std::vector<int>>matriceAdiacenta;
   std::vector<std::vector<Node>>listaAdiacenta;
public:
bool existaArc(Arc localArc);

void introduceNoduri(const int& numarNoduri);


void GenerareListaAdiacenta();

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
void modificaArce(int index1,QPointF coord);

bool verificaSuprapunereNoduri(QPointF curentCoord);
bool verificaSuprapunereNoduriDrag(QPointF curentCoord,Node curentNod);
};

#endif // GRAF_H

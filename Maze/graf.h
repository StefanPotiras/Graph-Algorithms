#ifndef GRAF_H
#define GRAF_H

#include "node.h"
#include "arc.h"

class Graf
{
    std::vector<Node> noduri;
    std::vector<Arc> arce;

    std::vector<std::vector<int>>matriceAdiacenta;
    std::vector<std::vector<int>>matriceGraf;
    std::vector<std::vector<Node>>listaAdiacenta;
public:
    bool existaArc(Arc localArc);
    Node returneazaNodul(QPointF coord);
    void afiseazaArcele();
    std::vector<Node> returneazaNoduriSfarsit();
    Node returneazaNodStar();
    void modificaNodul(int nr);
    void modificaMatrice(QPointF temp);
    int returneazaDimensiuneLinie();

    std::vector<Node> formeazaDrum(Node start);

    void introduceNoduri(const int& numarNoduri);
    void transformareInGraf();

    void formareArce();

    void GenerareListaAdiacenta();
    void readMatrice();
    std::vector<std::vector<int>> getMatrice();


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

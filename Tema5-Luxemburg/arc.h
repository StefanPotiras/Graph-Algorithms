#ifndef ARC_H
#define ARC_H
#include "node.h"

class Arc
{
    Node firstNode,secondNode;
    float distanta;
public:
    Arc(Node n1,Node n2,float distanta);
    Node getFirstPoint();
    Node getSecondPoint();
    void modificaCoordF1(QPointF coord);
    void modificaCoordF2(QPointF coord);
};

#endif // ARC_H

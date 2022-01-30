#ifndef ARC_H
#define ARC_H
#include "node.h"
#include<QPointF>
class Arc
{
    Node firstNode,secondNode;
public:
    Arc(Node n1,Node n2);
    Node getFirstPoint();
    Node getSecondPoint();
    void modificaCoordF1(QPointF coord);
    void modificaCoordF2(QPointF coord);
};

#endif // ARC_H

#include "node.h"

Node::Node()
{
    number=-1;

}

Node::Node(QPointF p,int number)
{
point =p;
this->number=number;
}

QPointF Node::getPoint()
{
    return point;
}

void Node::setPoint( QPointF t)
{
    point=t;
}

QPointF Node::getCoordDesen()
{
    return coordDesen;
}

void Node::setCoordDesen(QPointF t)
{
    coordDesen=t;
}

int Node::getNumber()
{
    return number;
}

void Node::setNumber(int number)
{
    this->number=number;
}

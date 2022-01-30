#include "node.h"

Node::Node()
{
    number=-1;

}

Node::Node(QPointF p)
{
point =p;
}

QPointF Node::getPoint()
{
    return point;
}

void Node::setPoint(const QPointF& t)
{
    point=t;
}

int Node::getNumber()
{
    return number;
}

void Node::setNumber(int number)
{
    this->number=number;
}

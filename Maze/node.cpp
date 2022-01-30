#include "node.h"

Node::Node()
{
    number=-1;

}

Node::Node(int number)
{
 this->number=number;
}

QPointF Node::getPoint()
{
    return point;
}

void Node::setPath(bool path)
{
    this->path=path;
}

bool Node::getPath()
{
    return path;
}

void Node::setPoint(const QPointF& t)
{
    point=t;
}

int Node::getNumber()
{
    return number;
}

void Node::setStart(bool start)
{
    this->start=start;
}

void Node::setEnd(bool end)
{
    this->end=end;
}

bool Node::getStart()
{
    return start;
}

bool Node::getEnd()
{
    return end;
}

void Node::setNumber(int number)
{
    this->number=number;
}

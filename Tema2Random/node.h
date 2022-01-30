#ifndef NODE_H
#define NODE_H

#include <QPainter>


class Node
{

    QPointF point;
    int number;
public:
    Node();
    Node(int number);
    QPointF getPoint();
    void setPoint(const QPointF& t);
    int getNumber();
    void setNumber(int number);
};

#endif // NODE_H

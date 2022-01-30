#ifndef NODE_H
#define NODE_H

#include <QPainter>


class Node
{

    QPointF point;
    int number;
public:
    Node();
    Node(QPointF p);
    QPointF getPoint();
    void setPoint(const QPointF& t);
    int getNumber();
    void setNumber(int number);
};

#endif // NODE_H

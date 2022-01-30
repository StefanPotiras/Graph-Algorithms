#ifndef NODE_H
#define NODE_H

#include <QPainter>


class Node
{

    QPointF point;
    QPointF coordDesen;
    int number;
public:
   Node();
    Node(QPointF p, int number);
    QPointF getPoint();

    void setPoint(QPointF t);

    QPointF getCoordDesen();
    void setCoordDesen(QPointF t);
    int getNumber();
    void setNumber(int number);
};

#endif // NODE_H

#ifndef NODE_H
#define NODE_H

#include <QPainter>


class Node
{

    QPointF point;
    int number;
    bool start;
    bool end;
    bool path;
public:
    Node();
    Node(int number);
    QPointF getPoint();
     void setPath(bool path);
     bool getPath();

    void setPoint(const QPointF& t);
    int getNumber();
    void setStart(bool start);

    void setEnd(bool end);
    bool getStart();

    bool getEnd();
    void setNumber(int number);
};

#endif // NODE_H

#ifndef EDGE_H
#define EDGE_H
#include "point.h"
struct edge{
    point beg, end;
    edge(point& ob1, point& ob2):beg(ob1.x, ob1.y), end(ob2.x, ob2.y){}
    double length();
    bool operator==(edge e);
};
#endif // EDGE_H

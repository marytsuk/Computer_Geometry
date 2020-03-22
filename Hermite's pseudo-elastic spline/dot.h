#ifndef DOT_H
#define DOT_H
#include <vector>
#include "point.h"
struct Dot
{
    Point center;
    int width;
    std::vector<Point> layout;
    Dot(double x, double y);
};

#endif // DOT_H

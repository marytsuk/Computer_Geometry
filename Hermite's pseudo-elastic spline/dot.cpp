#include "dot.h"
#include "point.h"
#include <vector>

Dot::Dot(double x, double y):center(x, y)
{
    width = 10;

    layout.push_back(Point(x - width/2, y - width/2));
    layout.push_back(Point(x - width/2, y + width/2));
    layout.push_back(Point(x + width/2, y + width/2));

    layout.push_back(Point(x - width/2, y - width/2));
    layout.push_back(Point(x + width/2, y + width/2));
    layout.push_back(Point(x + width/2, y - width/2));
}

#include "edge.h"
#include "point.h"
#include <cmath>

double edge::length()
{
    return sqrt((beg.x-end.x)*(beg.x-end.x)+(beg.y-end.y)*(beg.y-end.y));
}
bool edge::operator==(edge e)
{
    return (beg == e.beg || beg == e.end) && (end == e.end || end == e.beg);
}

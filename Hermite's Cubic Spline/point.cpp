#include "point.h"
#include <math.h>
Point::Point(double xT, double yT)
{
    x = xT;
    y = yT;
}
Point Point::operator*(double d)
{
    return Point(x*d, y*d);
}
Point Point::operator/(double d)
{
    return Point(x/d, y/d);
}
Point Point::operator+(Point ob)
{
        return Point(x + ob.x, y + ob.y);
}
Point Point::operator-(Point ob)
{
    return Point(x - ob.x, y - ob.y);
}
double Point::lenP()
{
    return sqrt(x*x + y*y);
}

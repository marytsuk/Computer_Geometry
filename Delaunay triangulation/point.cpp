#include "point.h"
#include <cmath>

#define RIGHT 0
#define LEFT 1
#define BETWEEN 2
point::point()
{
    x = 0;
    y = 0;
}
point::point(double xT, double yT)
{
    x = xT;
    y = yT;
}
int point::side(point A, point B)
{
    double des = -((B.x-A.x)*(y-A.y) - (x-A.x)*(B.y-A.y));

    if(des < 0){
        return RIGHT;
    }
    else if(des > 0){
        return LEFT;
    }
    else
        return BETWEEN;
}
double point::dist(double xT, double yT)
{
    return sqrt((x-xT)*(x-xT)+(y-yT)*(y-yT));
}
bool point::operator==(point p)
{
    return (x == p.x) && (y == p.y);
}
bool point::operator<(point b)
{
    return (x < b.x) && (y < b.y);
}

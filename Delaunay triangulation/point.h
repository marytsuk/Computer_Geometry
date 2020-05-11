#ifndef POINT_H
#define POINT_H
struct point
{
    double x, y;
    point();
    point(double xT, double yT);
    int side(point A, point B);
    double dist(double xT, double yT);
    bool operator==(point p);
    bool operator<(point b);
};

#endif // POINT_H

#ifndef POINT_H
#define POINT_H


struct Point
{
    double x, y;

    Point(double xT, double yT);

    Point operator*(double d);

    Point operator/(double d);

    Point operator+(Point ob);

    Point operator-(Point ob);

    // |P|
    double lenP();
};

#endif // POINT_H

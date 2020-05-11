#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include "edge.h"
#include "point.h"
#include <limits>
#include <QVector>
#include <QList>
#include <cmath>
#include <QPen>
#include <limits>
#include <QPoint>
#include <stdlib.h>
#define RIGHT 0
#define LEFT 1
#define BETWEEN 2
#define n 20
using namespace std;
QVector<point> triangles;
QList<edge> liveEd;
point S[n];
edge startEdge()
{
    point P = S[0];
    int m = 0;

    for(int i = 0; i < n; i++)
        if(S[i] < P)
            P = S[i];

    for(int i = 2; i < n; i++)
    {
        int c = S[i].side(P, S[m]);
        if(!(P == S[i])
         && (c == LEFT
         || (c == BETWEEN && P.dist(S[m].x, S[m].y) >= P.dist(S[i].x, S[i].y))))
            m = i;
    }

    return edge(P, S[m]);
}

void updateList(edge e)
{
    QList<edge>::iterator it;

    for(it = liveEd.begin(); it != liveEd.end(); it++)
        if(*it == e)
        {
            liveEd.erase(it);
            return;
        }

    liveEd.push_back(e);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(425, 450);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)
{
   /* S[0] = point(457, 439);
    S[1] = point(115, 61);
    S[2] = point(393, 368);
    S[3] = point(793, 110);
    S[4] = point(528, 369);
    S[5] = point(472, 312);
    S[6] = point(136, 556);
    S[7] = point(783, 626);*/

    QPainter painter(this);
    QPen pen;

   /* painter.drawLine(457, 439, 457, 439);
    painter.drawLine(115, 61, 115, 61);
    painter.drawLine(393, 368, 393, 368);
    painter.drawLine(793, 110, 793, 110);
    painter.drawLine(528, 369, 528, 369);
    painter.drawLine(472, 312, 472, 312);
    painter.drawLine(136, 556, 136, 556);
    painter.drawLine(783, 626, 783, 626);*/
    //srand(300);
    for (int i = 0; i < n; i++)
    {
        S[i] = point(rand() % 400, rand() % 400 + 25);
      //  painter.drawLine(S[i].x, S[i].y, S[i].x, S[i].y);
    }

    edge l = startEdge();

    pen.setColor(Qt::blue);
    pen.setWidth(2);
    painter.setPen(pen);
    liveEd.push_back(startEdge());
    while(!liveEd.empty())
    {
            edge e = liveEd.front();
            liveEd.pop_front();

            double min = numeric_limits<double>::max();
            point p(-1, 0);
            for(int i = 0; i < n; i++)
                if(S[i].side(e.beg, e.end) == RIGHT)
                {
                    double xC, yC;

                    if(!(e.end.x-e.beg.x))
                    {
                        double mb = (S[i].y-e.end.y)/(S[i].x-e.end.x);
                        xC = (mb*(S[i].y-e.beg.y)+e.end.x+S[i].x)/2;
                        yC = (e.beg.y+e.end.y)/2;
                    } else if(!(S[i].x-e.end.x))
                    {
                        double ma = (e.end.y-e.beg.y)/(e.end.x-e.beg.x);
                        xC = (ma*(-S[i].y+e.beg.y)+e.end.x+e.beg.x)/2;
                        yC = (e.end.y+S[i].y)/2;
                    } else
                    {
                        double ma = (e.end.y-e.beg.y)/(e.end.x-e.beg.x);
                        double mb = (S[i].y-e.end.y)/(S[i].x-e.end.x);
                        xC = (ma*mb*(e.beg.y-S[i].y)+mb*(e.beg.x+e.end.x)-ma*(e.end.x+S[i].x))/(2*(mb-ma));
                        yC = -(xC-(e.beg.x+e.end.x)/2)/ma+(e.beg.y+e.end.y)/2;
                    }
                    point C(xC, yC);
                    double rad = C.dist((e.beg.x+e.end.x)/2, (e.beg.y+e.end.y)/2);
                    if(C.side(e.beg, e.end) == LEFT) rad = -rad;

                    //cout << a << " " << b << endl;
                    //cout << S[i].x << " " << S[i].y << endl;
                    //cout << rad << endl;

                    if(rad < min)
                    {
                        min = rad;
                        p = S[i];
                    }
                }

      //      cout << endl;

            if(p.x != -1)
            {
                updateList(edge(e.beg, p));
                updateList(edge(p, e.end));
                triangles.push_back(e.beg);
                triangles.push_back(e.end);
                triangles.push_back(p);

                //for(list<edge>::iterator it = liveEd.begin(); it != liveEd.end(); it++)
                //	cout << it->beg.x << " " << it->beg.y << " " << it->end.x << " " << it->end.y << endl;


 //               cout << e.beg.x << " " << e.beg.y << endl;
   //             cout << e.end.x << " " << e.end.y << endl;
    //            cout << p.x << " " << p.y << endl << endl;
            }
        }
        for (int i = 0; i < triangles.size() - 2; i++)
        {
            if (i % 3 != 0)
                continue;
            painter.drawLine(triangles.at(i).x, triangles.at(i).y, triangles.at(i + 1).x, triangles.at(i + 1).y);
            painter.drawLine(triangles.at(i + 1).x, triangles.at(i + 1).y, triangles.at(i + 2).x, triangles.at(i + 2).y);
            painter.drawLine(triangles.at(i).x, triangles.at(i).y, triangles.at(i + 2).x, triangles.at(i + 2).y);
        }
       // pen.setColor(Qt::green);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine(l.beg.x, l.beg.y, l.end.x, l.end.y);
        pen.setColor(Qt::red);
        pen.setWidth(5);
        painter.setPen(pen);
        for (int i = 0; i < n; i++)
        {
            painter.drawLine(S[i].x, S[i].y, S[i].x, S[i].y);
        }
        triangles.clear();

}

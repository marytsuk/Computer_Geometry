#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include "point.h"
#include <QVector>
#include <vector>
#include <stdlib.h>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QTextEdit>
#include <QString>
using namespace std;
vector<Point> points;
vector<Point> P;
vector<Point> Q;
double *T;
int N = 5;
double g0(double w)
{
    return 1 - 3*w*w + 2*w*w*w;
}

double g1(double w)
{
    return w - 2*w*w + w*w*w;
}

double h0(double w)
{
    return 3*w*w - 2*w*w*w;
}

double h1(double w)
{
    return -w*w + w*w*w;
}
//Function computing value of r[i] at t
Point lineF(int i, double t)
{

    double w = (t - T[i])/(T[i+1] - T[i]);

    return P[i]*g0(w) + Q[i]*g1(w) + P[i+1]*h0(w) + Q[i+1]*h1(w);
}
//Function computing values of r[i] with delta
void makePoints(int i, double delta)
{

    points.push_back(lineF(i, T[i]));

    for(double j = T[i] + delta; j < T[i+1] - delta; j += delta){
        points.push_back(lineF(i, j));
        //points.push_back(lineF(i, j));
    }

    points.push_back(lineF(i, T[i+1]));
}
void finishP()
{
    for(int i = 0; i < P.size() - 1; i++)
        makePoints(i, 0.01);
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(400, 400);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

  //  N = ui->lineEdit->text().toInt();
    delete ui;
}
void Hermit3()
{
    double d = 1.0 / (P.size() - 1);
    double k = 0;
    int size = P.size();

    T = new double [size];

    //Calculating parametres
    for(int i = 0; i < size; k += d, i++)
        T[i] = k;

   //Calculating derivatives
    Q.push_back((P[1] - P[0])*2 - (P[2] - P[0])/(T[2] - T[0]));//Q0
    for(int i = 1; i < size - 1; i++)
    {
        double s1 = (P[i] - P[i-1]).lenP();
        double s2 = (P[i+1] - P[i]).lenP();
        Point QT = (P[i] - P[i-1])/(s1 + s2)*s1 + (P[i+1] - P[i])/(s1 + s2)*s2;
        Q.push_back(QT);
    }
    Q.push_back((P[size-1] - P[size-2])*2 - Q[size-2]);

                //Calculating points based on T's and Q's
    finishP();
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
 //   srand(400);

    for (int i = 0; i < N; i++)
    {
        P.push_back(Point(rand() % 300 + 25, rand() % 200 + 50));
    }

   /*double temp;
    for (int i = 0; i < P.size() - 1; i++)
    {
        for (int j = 0; j < P.size() - i - 1; j++)
        {
            if (P.at(j).x > P.at(j + 1).x)
            {
                temp = P.at(j).x;
                P.at(j).x = P.at(j + 1).x;
                P.at(j + 1).x = temp;
            }
        }
    }*/
    Hermit3();

        for (int i = 0; i < points.size() - 1; i++)
        {
            painter.drawLine(points.at(i).x, points.at(i).y, points.at(i + 1).x, points.at(i + 1).y);
        }
        pen.setWidth(5);
        pen.setColor(Qt::red);
        painter.setPen(pen);
        for (int i = 0; i < P.size(); i++)
        {
            painter.drawLine(P.at(i).x, P.at(i).y, P.at(i).x, P.at(i).y);
        }
        P.clear();
        points.clear();
}


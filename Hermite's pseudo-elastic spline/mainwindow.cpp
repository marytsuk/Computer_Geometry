#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include "point.h"
#include "dot.h"
using namespace std;
vector<Point> points;
vector<Dot> D;
vector<Point> P;
vector<Point> Q;
double *T;
int W, H;
int N = 6;
vector<Point> rightMat;
int movedPoint = -1;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(400, 400);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*void solve(double** mat)
{

    double a[H];
    vector<Point> B(H);
    double y = mat[0][0];
    a[0] = -mat[0][1] / y;
    B.push_back(rightMat[0] / y)  ;
    for (int i = 1; i < H; i++)
    {
        y = mat[i][i] + mat[i][i - 1] * a[i - 1];
        a[i] = -mat[i][i + 1] / y;
        B.push_back((rightMat[i] - B[i - 1]*mat[i][i - 1]) / y);
    }
    Q[H] = (rightMat[H] - B[H - 1]*mat[H][H - 1]) / (mat[H][H] + mat[H][H - 1] * a[H - 1]);
    for (int i = H - 1; i >= 0; i--)
    {
         Q[i] = Q[i + 1]*a[i] + B[i];
    }
}*/

void addMul(double **mat, int k1, int k2, double d)
{
    for(int i = 0; i < W; i++)
        mat[k1][i] += d*mat[k2][i];

    rightMat[k1] = rightMat[k1] + rightMat[k2]*d;
}

//Solving tri-diagonal matrix and adding derivatives
void solve(double **mat)
{

    for(int i = 0; i < H - 1; i++)
        addMul(mat, i+1, i, -mat[i+1][i]/mat[i][i]);

    for(int i = H-1; i > 0; i--)
        addMul(mat, i-1, i, -mat[i-1][i]/mat[i][i]);

    for(int i = 0; i < H; i++)
        Q.push_back(rightMat[i]/mat[i][i]);
}

//k[i]
double k(int i)
{
    double a = (P[i] - P[i-1]).lenP();
    double b = (P[i+1] - P[i]).lenP();
    return a/b;
}

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

    for(double j = T[i] + delta; j < T[i+1] - delta; j += delta)
    {
        points.push_back(lineF(i, j));
        //points.push_back(lineF(i, j));
    }

    points.push_back(lineF(i, T[i+1]));
}

//Function computing all r's
void finishP()
{
    for(int i = 0; i < P.size() - 1; i++)
        makePoints(i, 0.01/(P.size()-1));
}
void PseudoSP()
{
    double d = 1.0f/(P.size() - 1);
        double tmp = 0;
        int size = P.size();

        W = H = size;

        T = new double [size];

        //Calculating parametres
        for(int i = 0; i < size; tmp += d, i++)
            T[i] = tmp;

        //Calculating right part of matrix
        rightMat.push_back((P[1] - P[0])*3);
        for(int i = 1; i < size - 1; i++)
            rightMat.push_back((P[i] - P[i-1])*3 + (P[i+1]-P[i])*3*k(i)*k(i));
        rightMat.push_back((P[size-1] - P[size-2])*3);

        double **mat = new double* [H];

        for(int i = 0; i < H; i++){
            mat[i] = new double [W];
            for(int j = 0; j < W; j++)
                mat[i][j] = 0;
        }

        //Calculating left part of matrix
        mat[0][0] = 2;
        mat[0][1] = k(1);

        for(int i = 1; i < H - 2; i++){
            mat[i][i-1] = 1;
            mat[i][i] = 2*(k(i) + k(i)*k(i));
            mat[i][i+1] = k(i)*k(i)*k(i+1);
        }

        if(W - 3 >= 0){
            mat[H-2][W-3] = 1;
            mat[H-2][W-2] = 2*(k(H-2) + k(H-2)*k(H-2));
            mat[H-2][W-1] = k(H-2)*k(H-2)*k(H-1);
        }

        mat[H-1][W-2] = 1;
        mat[H-1][W-1] = 2;

        //Finding solution
        solve(mat);


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
    PseudoSP();

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

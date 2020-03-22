#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
struct Point 
{
	long double x;
	long double y;
};
bool pnpoly(int npol, Point* p, long double x, long double y)
{
	bool c=false;
	for (int i=0, j=npol-1; i<npol; j=i++)
	{
		if ((((p[i].y<=y) && (y<p[j].y)) || ((p[j].y<=y) && (y<p[i].y))) && (x>(p[j].x-p[i].x)*(y-p[i].y)/(p[j].y-p[i].y)+p[i].x))
			c=!c;
	}
	return c;
}
long double GetArea(Point *p, int n)
{
	int k=0;
	int flag=0;
	long double s=0;
	long double a;
	for (int i=1; i<=n-2; i++)
	{
/*		if (pnpoly(n, p, p[i+1].x, p[i+1].y) && (k==0))
		{
			k++;
			continue;
			flag=1;
		}*/
		a=(p[i].x-p[0].x)*(p[i+1].y-p[0].y)-(p[i].y-p[0].y)*(p[i+1].x-p[0].x);
	//	cout << a << endl;
	/*	if (flag)
			s=s-a;
		else*/
			s=s+a;
	}
	return abs(0.5*s);
}

int main()
{
	Point* mas=(Point*)malloc(sizeof(struct Point));
	string str;
	int i, k1;
	int k=0;
	int m=0;
	string num;
	long double a, xA, yA, xC, yC, xB, yB, xD, yD;
	ifstream file("input3");
	if (!file)
	{
		cout << "not opened" << endl;
		return -1;
	}
	else
	{
		while (file)
		{
			k1=0;
			i=0;
			getline(file, str);
			if (str!="")
			{
				for (int j=0; str[i]!='#'; )
				{

					if ((k%2)==0)
					{
						mas=(Point*)realloc(mas, (m+1)*sizeof(struct Point));
					}

					num="";
					while (i<str.length())
					{
						if (str[i]==' ')
						{
							num=str.substr(k1, i-k1);
							k1=i+1;
							i++;
							break;
						}
						i++;
					}
					
					a=atof(num.c_str());
					if ((k%2)==0)
					{
						mas[m].x=a;
					}
					else
					{
						mas[m].y=a;
						m++;
					}
					k++;
				}

				if (pnpoly(m-1, mas, mas[m-1].x, mas[m-1].y))
					cout << "Inside" << endl;
				else
				cout << "Outside" << endl;
				cout << "The area : " << GetArea(mas, (m-1)) << endl;
				free(mas);
				m=0;
				k=0;
			}	
		}
		return 0;
	}
}


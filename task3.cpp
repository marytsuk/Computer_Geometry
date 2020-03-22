#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int IsInside(long double x1, long double y1, long double x2, long double y2, long double x3, long double y3, long double x4, long double y4)
{
	int a1, a2, a3, b1, b2, b3, c1, c2, c3;
	int d1, d2, d3;
	a1=y1-y2;
	b1=x2-x1;
	c1=y1*(x1-x2)-x1*(y1-y2);
	a2=y3-y2;
	b2=x2-x3;
	c2=y2*(x3-x2)-x2*(y3-y2);
	a3=y1-y3;
	b3=x3-x1;
	c3=y3*(x1-x3)-x3*(y1-y3);
	d1=a1*x4+b1*y4+c1;
	d2=a2*x4+b2*y4+c2;
	d3=a3*x4+b3*y4+c3;
	if ((x4==x1) && (y4==y1))
		cout << "Point at the top A" << endl;
	else
		if ((x4==x2) && (y4==y2))
			cout << "Point at the top B" << endl;
		else
			if ((x4==x3) && (y4==y3))
				cout << "Point at the top C" << endl;
			else
			{
				if ((d1*d2*d3)<0)
					cout << "Point inside the triangle" << endl;
				else
					if ((d1*d2*d3)==0)
					{
						if (d1==0)
							cout << "Point on the AB side" << endl;
						if (d2==0)
							cout << "Point on the BC side" << endl;
						if (d3==0)
							cout << "Point on the AC side" << endl;
					}
					else
						cout << "Point outside the triangle" << endl;
			}
	
}
long double GetArea(long double x1, long double y1, long double x2, long double y2, long double x3, long double y3)
{
	return (0.5*((x1-x2)*(y3-y2)-(y1-y2)*(x3-x2)));
}
int main()
{
	string str;
	int i, k1;
	int k=0;
	string num;
	long double a, xA, yA, xC, yC, xB, yB, xD, yD;
	ifstream file("input2");
	if (!file)
	{
		cout << "not opened" << endl;
		return -1;
	}
	else
	{
		while (file)
		{
			k++;
			k1=0;
			i=0;
			getline(file, str);
			if (str!="")
			{
				for (int j=0; j<8; j++)
				{
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
					switch (j)
					{
						case 0: xA=a; break;
						case 1: yA=a; break;
						case 2: xB=a; break;
						case 3: yB=a; break;
						case 4: xC=a; break;
						case 5: yC=a; break;
						case 6: xD=a; break;
						case 7: yD=a; break;
						default: break;	
					};
				}
			cout << "Test#" << k << endl;
			IsInside(xA, yA, xB, yB, xC, yC, xD, yD);
			}
		}
		cout << endl << "The area of a triangle : " << GetArea(xA, yA, xB, yB, xC, yC) << endl;

		return 0;
	}
}

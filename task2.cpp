#include <iostream>
#include <string>
#include <fstream>
using namespace std;
long double GetA(long double x1, long double y1, long double x2, long double y2, long double x3, long double y3)
{
	return ((x2-x1)*(y3-y1)-(y2-y1)*(x3-x1));
}
int main()
{
	string str;
	int i, k1;
	int k=0;
	string num;
	long double a, xA, yA, xC, yC, xB, yB;
	ifstream file("input1");
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
				for (int j=0; j<6; j++)
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
						default: break;	
					};
				}
			cout << "Test#" << k << endl;
			if (GetA(xA, yA, xB, yB, xC, yC)>0)
			{
				cout << "Point to the left" << endl;
			}
			else 
				if (GetA(xA, yA, xB, yB, xC, yC)<0)
				{
					cout << "Point to the right" << endl;
				}
				else
				{
					if ((yC>yB) || (xC>xB))
						cout << "Above the segment" << endl;
					else
						if ((yC<yA) || (xC<xA))
							cout << "Under the segment" << endl;
						else
							cout << "On a segment" << endl;
				}
			}
		}
		return 0;
	}
}

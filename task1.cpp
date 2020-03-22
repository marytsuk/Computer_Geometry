#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

class LongDouble
{
	int sign;
	vector<int> digits;
	long exponent;
	void removeZeroes();
public:
	friend ostream& operator<<(ostream& os, const LongDouble& value);
	LongDouble operator+(const LongDouble& x) const;
	LongDouble operator-(const LongDouble& x) const; //вычитание
	LongDouble operator*(const LongDouble& x) const;
	LongDouble operator-() const; //унарный минус
	bool operator>(const LongDouble& x) const; //сравнение > <
	bool operator==(const LongDouble& x) const;
	LongDouble();
	LongDouble(const LongDouble& x);
	LongDouble(const string& value);
};

LongDouble::LongDouble()
{
	sign=1;
	digits=vector<int>(1, 0);
	exponent=1;
};

LongDouble::LongDouble(const LongDouble& x)
{
	sign=x.sign;
	exponent=x.exponent;
	digits=vector<int>(x.digits);
};
LongDouble::LongDouble(const string& value)
{
	int index;
	if (value[0]=='-')
	{
		sign=-1;
		index=1;
	}
	else
	{
		sign=1;
		index=0;
	}
	exponent=value.length()-index;
	while (index<value.length())
	{
		if (value[index]=='.')
			exponent=sign==1 ? index : index-1;
		else
			digits.push_back(value[index]-'0');
		index++;
	}
};

void LongDouble::removeZeroes()
{
	int n=max((long) 1, exponent);
	while (digits.size()>n && digits[digits.size()-1]==0)
		digits.erase(digits.end()-1);
	while (digits.size()>1 && digits[0]==0)
	{
		digits.erase(digits.begin());
		exponent--;
	}
	while (digits.size()>1 && digits[digits.size()-1]==0)
		digits.erase(digits.end()-1);
	if (digits.size()==1 && digits[0]==0)
	{
		exponent=1;
		sign=1;
	}
};

ostream& operator<<(ostream& os, const LongDouble& value)
{
	if (value.sign==-1)
		os << "-";
	if (value.exponent>0)
	{
		int i=0;
		int e=value.exponent;
		while (i<value.digits.size() && i<e)
			os << value.digits[i++];
		while (i<e)
		{
			os << "0";
			i++;
		}
		if (i<value.digits.size())
		{
			os << ".";
			while (i<value.digits.size())
				os << value.digits[i++];
		}
	}
	else
	{
		os << "0.";
		for (long i=0; i<-value.exponent; i++)
			os << "0";
		for (int i=0; i<value.digits.size(); i++)
			os << value.digits[i];
	}
	return os;
};
LongDouble LongDouble::operator*(const LongDouble& x) const
{
	int len=digits.size()+x.digits.size();
	LongDouble res;
	res.sign=sign*x.sign;
	res.digits=vector<int>(len, 0);
	res.exponent=exponent+x.exponent;
	for (int i=0; i<digits.size(); i++)
		for (int j=0; j<x.digits.size(); j++)
			res.digits[i+j+1]+=digits[i]*x.digits[j];
	for (int i=len-1; i>0; i--)
	{
		res.digits[i-1]+=res.digits[i]/10;
		res.digits[i]%=10;
	}
	res.removeZeroes();
	return res;
}
LongDouble LongDouble::operator-() const
{
	LongDouble res;
	res.sign=-sign;
	res.exponent=exponent;
	res.digits=vector<int>(digits);
	return res;
}
bool LongDouble::operator>(const LongDouble& x) const
{
	if (sign!=x.sign)
		return sign>x.sign;
	if (exponent!=x.exponent)
		return (exponent>x.exponent)^(sign==-1);
	vector<int> d1(digits);
	vector<int> d2(x.digits);
	int size=max(d1.size(), d2.size());
	while (d1.size()!=size)
		d1.push_back(0);
	while (d2.size()!=size)
		d2.push_back(0);
	for (int i=0; i<size; i++)
		if (d1[i]!=d2[i])
			return (d1[i]>d2[i])^(sign==-1);
	return false;
}
bool LongDouble::operator==(const LongDouble& x) const
{
	if (sign!=x.sign)
		return false;
	vector<int> d1(digits);
	vector<int> d2(x.digits);
	int size=max(d1.size(), d2.size());
	while (d1.size()!=size)
		d1.push_back(0);
	while (d2.size()!=size)
		d2.push_back(0);
	for (int i=0; i<size; i++)
		if (d1[i]!=d2[i])
			return false;
	return true;
}
LongDouble LongDouble::operator+(const LongDouble& x) const
{
	if (sign==x.sign)
	{
		long exp1=exponent;
		long exp2=x.exponent;
		long exp=max(exp1, exp2);
		vector <int> d1(digits);
		vector <int> d2(x.digits);
		while (exp1!=exp)
		{
			d1.insert(d1.begin(), 0);
			exp1++;
		}
		while (exp2!=exp)
		{
			d2.insert(d2.begin(), 0);
			exp2++;
		}
		int size=max(d1.size(), d2.size());
		while (d1.size()!=size)
			d1.push_back(0);
		while (d2.size()!=size)
			d2.push_back(0);
		int len=1+size;
		LongDouble res;
		res.sign=sign;
		res.digits=vector<int>(len, 0);
		for (int i=0; i<size; i++)
			res.digits[i+1]=d1[i]+d2[i];
		for (int i=len-1; i>0; i--)
		{
			res.digits[i-1]+=res.digits[i]/10;
			res.digits[i]%=10;
		}
		res.exponent=exp+1;
		res.removeZeroes();
		return res;
	}
	if (sign==-1)
		return x-(-(*this));
	return *this-(-x);
}
LongDouble LongDouble::operator-(const LongDouble& x) const
{
	if (sign==1 && x.sign==1)
	{
		bool cmp=*this>x;
		long exp1=cmp ? exponent : x.exponent;
		long exp2=cmp ? x.exponent : exponent;
		long exp=max(exp1, exp2);
		vector<int> d1(cmp ? digits : x.digits);
		vector<int> d2(cmp ? x.digits : digits);
		while (exp1!=exp)
		{
			d1.insert(d1.begin(), 0);
			exp1++;
		}
		while (exp2!=exp)
		{
			d2.insert(d2.begin(), 0);
			exp2++;
		}
		int size=max(d1.size(), d2.size());
		while (d1.size()!=size)
			d1.push_back(0);
		while (d2.size()!=size)
			d2.push_back(0);
		int len=1+size;
		LongDouble res;
		res.sign=cmp ? 1 : -1;
		res.digits=vector<int>(len, 0);
		for (int i=0; i<size; i++)
			res.digits[i+1]=d1[i]-d2[i];
		for (int i=len-1; i>0; i--)
		{
			if (res.digits[i]<0)
			{
				res.digits[i]+=10;
				res.digits[i-1]--;
			}
		}
		res.exponent=exp+1;
		res.removeZeroes();
		return res;
	}
	if (sign==-1 && x.sign ==-1)
		return (-x)-(-(*this));
	return *this+(-x);
}
LongDouble delta(LongDouble x1, LongDouble y1, LongDouble x2, LongDouble y2, LongDouble x3, LongDouble y3, LongDouble x4, LongDouble y4)
{
	return ((x2-x1)*(y3-y4)-(x3-x4)*(y2-y1));
}
LongDouble delta1(LongDouble x1, LongDouble y1, LongDouble x3, LongDouble y3, LongDouble x4, LongDouble y4)
{
	return ((x3-x1)*(y3-y4)-(x3-x4)*(y3-y1));
}
LongDouble delta2(LongDouble x1, LongDouble y1, LongDouble x2, LongDouble y2, LongDouble x3, LongDouble y3)
{
	return ((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));
}
LongDouble vecp(LongDouble x1, LongDouble y1, LongDouble x2, LongDouble y2)
{
	return (x1*y2-x2*y1);
}
void reverse(LongDouble& x1, LongDouble& y1, LongDouble& x2, LongDouble& y2, LongDouble& x3, LongDouble& y3, LongDouble& x4, LongDouble& y4)
{
	LongDouble zero("0.0");
	if (!(x1>zero) && !(y1>zero) && !(x2>zero) && !(y2>zero) && !(x3>zero) && !(y3>zero) && !(x4>zero) && !(y4>zero))
	{
		x1=-x1;
		x2=-x2;
		x3=-x3;
		x4=-x4;
		y1=-y1;
		y2=-y2;
		y3=-y3;
		y4=-y4;
	}
	else
		return;
}
bool Get(LongDouble x1, LongDouble y1, LongDouble x2, LongDouble y2, LongDouble x3, LongDouble y3)
{
	LongDouble zero("0.0");
	LongDouble a=((x2-x1)*(y3-y1)-(y2-y1)*(x3-x1));
	if (a==zero)
	{
		if (!(x3>x2) && (x3>x1) && !(y3>y2) && (y3>y1))
			return 1;
	}
	else 
		return 0;
/*	if ((a>zero) || !(a>zero))
		return 0;
	else
		if (!(x3>x2) && (x3>x1) && !(y3>y2) && (y3>y1))
			return 1;
		else
			return 0;*/
}
int main()
{
	string str;
/*	cin >> st;
	bool f;
	LongDouble a("0.5");
	LongDouble b(st);
	LongDouble c;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	c=a+b;
	cout << "c = " << c << endl;
	f=a>b;
	cout << f << endl;*/
	int i, k1;
	int k=0;
	int m=0;
	int r=0;
	LongDouble zero("0.0");
	LongDouble xA, yA, xB, yB, xC, yC, xD, yD, d, d1, d2;
	LongDouble xV1, yV1, xV2, yV2, xV3, yV3, xV4, yV4, xV5, yV5, xV6, yV6, vp1, vp2, vp3, vp4;
	int answ, q;
	string num;
	ifstream file("input");
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
				for (int j=0; j<9; j++)
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
					switch (j)
					{
						case 0: xA=num; break;
						case 1: yA=num; break;
						case 2: xB=num; break;
						case 3: yB=num; break;
						case 4: xC=num; break;
						case 5: yC=num; break;
						case 6: xD=num; break;
						case 7: yD=num; break;
						case 8: answ=atof(num.c_str());
						default: break;
					};
				}
				cout << "Test#" << k << endl;
				
				cout << "The coordinates of the points : " << endl << "A : " << xA << ' ' << yA << endl << "B : " << xB << ' ' << yB << endl << "C : " << xC << ' ' << yC << endl <<"D : " << xD << ' ' << yD << ' ' << endl;
				reverse(xA, yA, xB, yB, xC, yC, xD, yD);

				xV1=xB-xA;
				yV1=yB-yA;
				xV2=xD-xC;
				yV2=yD-yC;
				xV3=xB-xC;
				yV3=yB-yC;
				xV4=xD-xA;
				yV4=yD-yA;
				xV5=xD-xB;
				yV5=yD-yB;
				xV6=xC-xA;
				yV6=yC-yA;
				vp1=vecp(xV1, yV1, xV3, yV3);
				vp2=vecp(xV2, yV2, xV4, yV4);
				vp3=vecp(xV1, yV1, xV5, yV5);
				vp4=vecp(xV1, yV1, xV6, yV6);
				d=delta(xA, yA, xB, yB, xC, yC, xD, yD);
			//	cout<<vp1<<' '<<vp2<<endl;
			//	cout<<vp3<<' '<<vp4<<endl;
				d1=delta1(xA, yA, xC, yC, xD, yD);
				d2=delta2(xA, yA, xB, yB, xC, yC);
				if ((d==zero) && (!(d1==zero) || !(d2==zero)))
					q=4;
				else
					if ((d1==zero) && (d2==zero) && (d==zero))
					{
						if (xB==xC)
							q=7;
						else
							if ((xC>xA || xC==xA) && !(xC>xB) && (xD>xA) && (!(xD>xB) || (xD==xB)))
								q=6;
							else
								if ((xC>xA) && !(xC>xD) && (xB>xA) && !(xB>xD) && !(xC>xB))
									q=5;
								else 
									q=8;
						// 5, 6, 7, 8 лежат на одной прямой
					}
					else
						if (!(d==zero))
						{
							if (!((vp1*vp2)>zero) && !((vp3*vp4)>zero) && !((vp1*vp2)==zero) && !((vp3*vp4)==zero))
							{
								q=1;
								if ((xC>xA) && (xC>xB))
								       q=0;	
							}
							
							else
								if ((((vp1*vp2)==zero) || ((vp3*vp4)==zero)) && ((xA==xC) || (xB==xC)))
									q=3;
								else
									if (((vp1*vp2)==zero) || ((vp3*vp4)==zero))
									{
										q=2;
// cout << Get(xA, yA, xB, yB, xC, yC) << ' ' << Get(xA, yA, xB, yB, xC, yC) << endl;
										if (!Get(xA, yA, xB, yB, xC, yC) || !Get(xA, yA, xB, yB, xC, yC))
										{
											q=0;
										}
									}
									else
										q=0; //не пересекаются
						}
				if (q==answ)
				{
					r++;
					cout << "OK" << ' ' << q << endl;
				}
				else
				{	
					m++;
					cout << "MISTAKE!" <<  endl << "my answer : " << q << endl << "your answer : " << answ << endl;
				}
			}
		}
		cout << "Correct : " << r << endl << "Not Correct : " << m << endl;
		return 0;
	}
}

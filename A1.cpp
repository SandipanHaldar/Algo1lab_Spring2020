#include<iostream>
#include<math.h>
using namespace std;
double hirec(int);
double lorec(int);
typedef struct _hilo
{
	double h;
	double l;
}hilo;
double hirec(int n)
{
	double hi;double one=1;
	if (n==0)
	{
		return one;
	}
	else
	{
		return (2*hirec(n-1))+lorec(n-1);
	}
	;
}
double lorec(int n)
{
	double lo;double zero=0;
	if(n==0)
	{
		return zero;
	}
	else
	{
		 return lorec(n-1)+hirec(n-1);
	}
	
}
hilo hilorec(int n)
{
	
	hilo ans;
	if(n==0){ans.h=1;ans.l=0;}
	
	else 
	{
		hilo ans1=hilorec(n-1);
		ans.h=(2*ans1.h)+(ans1.l);
		ans.l=(ans1.h)+ans1.l;
	}
	return ans;
}
hilo highformula(int n)
{
	double A1=(5+sqrt(5));A1=A1/10;
	double A2=(3-sqrt(5));A2=A2/2;double pow2;pow2=pow(A2,n+1);
	double A3=(5-sqrt(5));A3=A3/10;
	double A4=(3+sqrt(5));A4=A4/2;double pow4;pow4=pow(A4,n+1);
	hilo ans;
	ans.h=(A1*pow2)+(A3*pow4);
	double B1=(-5-(3*sqrt(5)));B1=B1/10;
	//double A2=(3-sqrt(5));A2=A2/2;double pow2;pow2=pow(A2,n+1);
	double B3=(-5+(3*sqrt(5)));B3=B3/10;
	//double A4=(3+sqrt(5));A4=A4/2;double pow4;pow4=pow(A4,n+1);
	ans.l=(B1*pow2)+(B3*pow4);
	return ans;
}
int main()
{
	int n;cout<<"enter the time ";
	cin>>n;
	
	double hi,lo;
	hi=hirec(n);
	lo=lorec(n);
	cout<<"+++ Method 0"<<endl;
	cout<<"    hi("<<n<<")= "<<hi<<",  lo("<<n<<")= "<<lo<<endl;
	hilo b;b=hilorec(n); 
	cout<<"+++ Method 1"<<endl;
	cout<<"    hi("<<n<<")= "<<b.h<<",  lo("<<n<<")= "<<b.l<<endl; 	
	hilo a;
	a=highformula(n);
	cout<<"+++ Method 2"<<endl;
	cout<<"    hi("<<n<<")= "<<a.h<<",  lo("<<n<<")= "<<a.l<<endl;
	
	
	
}
#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#define INF DBL_MAX

double profit(double p,int m,int s,int t)
{
	double e;
	double res=pow(p,(double)m);
	e=(1-res)*s;
	e+=(res*t);
	return e;
}
void optimalbuy1(int n,int C,int c[],int s[],int t[],double p[])
{
	cout<<"+++Part1: Best buying option"<<endl;int i,j,k;
	double dp[n][C+1];int m[n][C+1];
	for( j=0;j<C+1;j++)
	{
		if(j<c[0])m[0][j]=(int)-INF;
		else m[0][j]=j/c[0]; 
		
	}
	for( i=0;i<C+1;i++)
	{
		if(i<c[0])dp[0][i]=-INF;
		else 
		{
			int m=i/c[0];
			dp[0][i]=profit(p[0],m,s[0],t[0]);
		}
	}
	for( i=1;i<n;i++)
	{
		for( j=0;j<C+1;j++)
		{
			if(j<c[i])dp[i][j]=-INF;
			else
			{
				double tg=0;int ind,newtot;
				for( k=1;k<=j/c[i];k++)
				{
					int price=k*c[i];
					int total=j-price;
					double gain=profit(p[i],k,s[i],t[i]);
					if(dp[i-1][total]+gain >= tg)
					{
						tg=dp[i-1][total]+gain;
						ind=k;newtot=total;
					}


				}
				dp[i][j]=tg;m[i][j]=ind;
			}
		}
	}
	int a[n];int ci=C;
	
	for(i=n-1;i>=0;i--)
	{
		a[i]=m[i][ci];
		ci=ci-(a[i]*c[i]);//cout<<ci<<endl;
		if(ci<0)break;	
	}
	//cout<<m[n-1][C];
	for(i=0;i<n;i++)
	{
		cout<<"Machine "<<i<<": "<<a[i]<<" copies,cost = "<<a[i]*c[i]<<endl;
	}
	cout<<"+++Total buying Cost:  "<<C-ci<<endl;
	cout<<"+++Total profit: " <<setprecision(6)<<dp[n-1][C]<<endl;



}

void optimalbuy2(int n,int C,int c[],int s[],int t[],double p[],int r[],double q[])
{
	cout<<"+++Part2: Best buying option"<<endl;int i,j,k;
	double dp[n][C+1];int m[n][C+1];int hash[n][C+1]={0};
	for( j=0;j<C+1;j++)
	{
		if(j<c[0])m[0][j]=(int)-INF;
		else m[0][j]=j/c[0]; 
		
	}
	for( i=0;i<C+1;i++)
	{
		if(i<c[0])dp[0][i]=-INF;
		else 
		{
			double gain,gain1;
			int m=i/c[0];
			gain=profit(p[0],m,s[0],t[0]);
			gain1=profit(q[0],m,s[0],t[0]);gain1-=(r[0]*m);
			if(gain>gain1)dp[0][i]=gain;
			else 
			{
				dp[0][i]=gain1;hash[0][i]=1;
			}
		}
	}
	for( i=1;i<n;i++)
	{
		for( j=0;j<C+1;j++)
		{
			if(j<c[i])dp[i][j]=-INF;
			else
			{
				double tg=0;int ind,newtot,temp=0;int mt;
				for( k=1;k<=j/c[i];k++)
				{
					temp=0;
					int price=k*c[i];
					int total=j-price;
					double gain=profit(p[i],k,s[i],t[i]);
					double gain1=profit(q[i],k,s[i],t[i]);gain1-=(k*r[i]);
					if(gain>gain1){
					if(dp[i-1][total]+gain >= tg)
					{
						tg=dp[i-1][total]+gain;
						ind=k;newtot=total;mt=temp;
					}}
					else{
					
					if(dp[i-1][total]+gain1 >= tg)
					{
						tg=dp[i-1][total]+gain1;
						ind=k;newtot=total;
						temp=1;mt=temp;
					}}


				}
				dp[i][j]=tg;m[i][j]=ind;if(mt==1){hash[i][j]=1;}
			}
		}
	}
	int a[n],b[n];int ci=C;
	
	for(i=n-1;i>=0;i--)
	{
		a[i]=m[i][ci];if(hash[i][ci])b[i]=1;else b[i]=0;
		ci=ci-(a[i]*c[i]);//cout<<ci<<endl;
		if(ci<0)break;	
	}
	//cout<<m[n-1][C];
	for(i=0;i<n;i++)
	{
		cout<<"Machine "<<i<<": "<<a[i]<<" copies,cost = "<<a[i]*c[i];
		if(b[i]!=0)cout<<"  [maintainence needed]"<<endl;
		else cout<<" [maintainence not needed]"<<endl;
	}
	cout<<"+++Total buying Cost:  "<<C-ci<<endl;
	cout<<"+++Profit :"<<setprecision(6)<<dp[n-1][C];



}

int main(int argc, char const *argv[])
{
	int n;
	//cout<<"n= ";
	cin>>n;
	int C;
	//cout<<"Capital= ";
	cin>>C;
	int c[n];//cout<<"costs: ";
	for(int i=0;i<n;i++)cin>>c[i];
	int s[n];//cout<<"Selling price : ";
	for(int i=0;i<n;i++)cin>>s[i];
	int t[n];//cout<<"Selling price defective: ";
	for(int i=0;i<n;i++)cin>>t[i];
	int r[n];//cout<<"maintainence costs: ";
	for(int i=0;i<n;i++)cin>>r[i];
	double p[n];//cout<<"probabitily: ";
	for(int i=0;i<n;i++)cin>>p[i];
	double q[n];//cout<<"probability after maintainence: ";
	for(int i=0;i<n;i++)cin>>q[i];
	optimalbuy1(n,C,c,s,t,p);	
	optimalbuy2(n,C,c,s,t,p,r,q);
	return 0;
}
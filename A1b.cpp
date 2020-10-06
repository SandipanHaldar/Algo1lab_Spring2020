#include<iostream>
#include<math.h>
using namespace std;

int method0(int s[],int n)
{
	int ans=1;
	for(int a=1;a<=n-2;a++)
	{
		int j=-1;
		
		
		for(int b=a+1;b<=n-1;b++)
		{
			int k=-1;
			
			for(int c=b+1;c<=n;c++)
			{
				int i=-1;
				for(int x=0;x<n;x++)
				{
					if(s[x]==c)i=x;
					else if(s[x]==a)j=x;
					else if(s[x]==b)k=x;
					
					
				}
				if((i<j && j<k))ans=0;
			}
		}
	}
	return ans;
}
int method1(int s[],int n)
{
	int ans=1;
	for(int i=0;i<n-2;i++)
	{
		for(int j=i+1;j<n-1;j++)
		{
			for(int k=j+1;k<n;k++)
			{
				if(s[i]>s[k] && s[j]<s[k]){ans=0;break;}
			}
		}
		
	}
	return ans;
}

int method2(int s[],int n)
{
	int temp,temp1;
	int ans=1;int ind=0;
	for(int i=0;i<n-1;i++)
	{
		ind=0;
		for(int j=i+1;j<n;j++)
		{
			if(s[j]<s[i])
			{
				int lol;
				if(ind==0)
				{
					temp=s[j];
					
				}else{
				lol=temp;
				temp=s[j];
				temp1=lol;
				if(temp1<temp){ans=0;}}
				ind++;
			}
		}
	}
	return ans;
	
}
int method3(int s[],int n)
{
	int a[n+5];int max=0;int ind;int ans=1;
	for(int i=0;i<n;i++)
	{
		a[s[i]]=i;
	}
	for(int i=1;i<n+1;i++)
	{
		if(a[i]>max){max=a[i];ind=i;}
		else 
		{
			if(a[ind-1]>a[i] && ind>1)ans=0;
		}
		
	}
	//cout<<a[5]<<a[2]<<a[1]<<endl;
	return ans;
}
int main()
{
	int n;cout<<"n= ";cin>>n;
	int s[n];cout<<"+++Sequence: ";
	for(int i=0;i<n;i++)
	{
		cin>>s[i];
	}
	
	int flag0;
	flag0=method0(s,n);cout<<"method 0: ";
	if(flag0)cout<<"Algolicious"<<endl;
	else cout<<"unalgolicious"<<endl;
	int flag1;
	flag1=method1(s,n);cout<<"method 1: ";
	if(flag1)cout<<"Algolicious"<<endl;
	else cout<<"unalgolicious"<<endl;
	int flag2;
	flag2=method2(s,n);cout<<"method 2: ";
	if(flag2)cout<<"Algolicious"<<endl;
	else cout<<"unalgolicious"<<endl;
	int flag3;
	flag3=method3(s,n);cout<<"method 3: ";
	if(flag3)cout<<"Algolicious"<<endl;
	else cout<<"unalgolicious"<<endl;
	
	
}
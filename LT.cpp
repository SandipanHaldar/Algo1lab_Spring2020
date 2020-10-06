#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000

const int N=50*50;
// returns of minimum a,b
int min(int a,int b)
{
	if(a<b)return a;
	return b;
}
//returns of maximum a,b 
int max(int a,int b)
{
	if(a>b)return a;
	return b;
}
//finds max possible L for i,j in essquare func 
int findmax(int i,int j,int m,int n)
{
	return min(m-i,n-j);
}
//function to check if a matrix is a checkboard
bool ischessboard(int a[][50],int l1,int l2)
{
	int X[] = { 0, -1, 0, 1 }; 
    int Y[] = { 1, 0, -1, 0 }; 
    bool isValid = true; 
	for(int i=0;i<l1;i++)
	{
		for(int j=0;j<l2;j++)
		{
			for(int k=0;k<4;k++)
			{
				int newx=i+X[k];
				int newy=j+Y[k];
				if(newx<l1 && newy<l2 && newx>=0 && newy>=0 && a[newx][newy]==a[i][j])
					isValid=false;
			}
		}
	}
	return isValid;
}
void essquare(int F[][50],int m,int n)
{
	int ansi,ansj,ansl;int maxl=0;int i,j,l;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			int L=findmax(i,j,m,n);
			for(l=L;l>0;l--)
			{

				int a[50][50];
				for(int i1=i;i1<i+l;i1++)
					for(int j1=j;j1<j+l;j1++)
						a[i1-i][j1-j]=F[i1][j1];
				if(ischessboard(a,l,l))
				{
					//cout<<l<<" "<<i<<" "<<j<<"\n";
					if(l>=maxl)
					{
						maxl=l;
						ansi=i;ansj=j;ansl=l;
					}
					break;
				}
			}
			
		}
		
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i>=ansi && i<ansi+ansl && j>=ansj && j<ansj+ansl)
			{
				if(F[i][j]==1)cout<<"B ";
				else cout<<"W ";
			}
			else cout<<"- ";
		}
		cout<<endl;
	}
	cout<<"Area: "<< ansl*ansl<<"\n";

}

void esrectangle(int F[][50],int m,int n)
{
	int ansi,ansj,ansl,ansk;int maxl=0,maxk=0;int i,j,l,k;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			int L=m-i;
			int K=n-j;
			for(l=L;l>0;l--)
			{
				for(k=K;k>0;k--)
				{
					int a[50][50];
					for(int i1=i;i1<i+l;i1++)
						for(int j1=j;j1<j+k;j1++)
							a[i1-i][j1-j]=F[i1][j1];
					if(ischessboard(a,l,k))
					{
						//cout<<l<<" "<<i<<" "<<j<<"\n";
						if(l*k>=(maxl*maxk))
						{
							maxl=l;maxk=k;
							ansi=i;ansj=j;ansl=l;ansk=k;
						}
						break;
					}
				}
			}
			
		}
		
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i>=ansi && i<ansi+ansl && j>=ansj && j<ansj+ansk)
			{
				if(F[i][j]==1)cout<<"B ";
				else cout<<"W ";
			}
			else cout<<"- ";
		}
		cout<<endl;
	}
	cout<<"Area: "<< ansk*ansl<<"\n";
}

void dpsquare(int F[][50],int m,int n)
{
	int T[50][50]={0};
	for(int j=0;j<n;j++)T[m-1][j]=1;
	for(int i=0;i<m;i++)T[i][n-1]=1;
	for(int i=m-2;i>=0;i--)
	{
		for(int j=n-2;j>=0;j--)
		{
			if(F[i+1][j]==F[i][j] || F[i][j+1]==F[i][j])T[i][j]=1;
			else
			{
				int l1=T[i+1][j];int l2=T[i][j+1];
				if(l1>l2)T[i][j]=l2+1;
				else if(l2>l1)T[i][j]=l1+1;
				else if(l2==l1)
				{
					if(F[i+l1][j+l2]==F[i][j])T[i][j]=l1+1;
					else T[i][j]=l2;
				}
			}

		}
	}
	int maxi=0,ansi,ansj,ansl;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(T[i][j]>=maxi)
			{
				maxi=T[i][j];ansi=i;ansj=j;ansl=maxi;
			}
		}
		
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i>=ansi && i<ansi+ansl && j>=ansj && j<ansj+ansl)
			{
				if(F[i][j]==1)cout<<"B ";
				else cout<<"W ";
			}
			else cout<<"- ";
		}
		cout<<endl;
	}
	cout<<"Area: "<< ansl*ansl<<"\n";
	
}
/*vertical[i][j] stores the maximum possible length of 
a chessboard column in vertical direction from i,j*/
/*horizontal[i][j] stores the maximum possible length of 
a chessboard row in horizontal direction from i,j*/
//T[i][j] is maximum valid area as i,j as top left corner of a chess board
void dprectangle(int F[][50],int m,int n)
{
	int T[50][50]={0};
	T[m-1][n-1]=1;
	int vertical[50][50]={1};int horizontal[50][50]={1};
	int maxl,maxk,ansi,ansj,maxi=0;
	for(int j=0;j<n;j++)
	{
		vertical[m-1][j]=1;
		for(int i=m-2;i>=0;i--)
		{
			if(F[i][j]!=F[i+1][j])vertical[i][j]=vertical[i+1][j]+1;
			else vertical[i][j]=1;
		}
	}
	for(int i=0;i<m;i++)
	{
		horizontal[i][n-1]=1;
		for(int j=n-2;j>=0;j--)
		{
			if(F[i][j]!=F[i][j+1])horizontal[i][j]=horizontal[i][j+1]+1;
			else horizontal[i][j]=1;
		}
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			int mini=horizontal[i][j];
			for(int itr=0;itr<vertical[i][j];itr++)
			{
				mini=min(mini,horizontal[i+itr][j]);
				T[i][j]=max(mini*(itr+1), T[i][j]);
				if(T[i][j]>maxi)
				{
					maxi=T[i][j];
					maxk=mini;maxl=itr+1;ansi=i;ansj=j;
				}
			}
			T[i][j]=max(mini*vertical[i][j],T[i][j]);
			if(T[i][j]>maxi)
			{
				maxi=T[i][j];
				maxk=mini;maxl=vertical[i][j];ansi=i;ansj=j;
			}
			mini=vertical[i][j];
			for(int itr=0;itr<horizontal[i][j];itr++)
			{
				mini=min(mini,vertical[i][j+itr]);
				T[i][j]=max(mini*(itr+1), T[i][j]);
				if(T[i][j]>maxi)
				{
					maxi=T[i][j];
					maxk=itr+1;maxl=mini;ansi=i;ansj=j;
				}
			}
			T[i][j]=max(T[i][j],mini*horizontal[i][j]);
			if(T[i][j]>maxi)
			{
				maxi=T[i][j];
				maxk=horizontal[i][j];maxl=mini;ansi=i;ansj=j;
			}
		}
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i>=ansi && i<ansi+maxl && j>=ansj && j<ansj+maxk)
			{
				if(F[i][j]==1)cout<<"B ";
				else cout<<"W ";
			}
			else cout<<"- ";
		}
		cout<<endl;
	}
	cout<<"Area: "<< maxk*maxl<<"\n";
}



int main()
{
	int m,n;cin>>m>>n;
	int F[50][50];
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			cin>>F[i][j];
	cout<<endl;
	cout<<"+++ Exhaustive search: Square\n";
	essquare(F,m,n);
	cout<<endl<<"+++ Exhaustive search: Rectangle\n";
	esrectangle(F,m,n);
	cout<<endl;
	cout<<"+++ Dynamic Programming: Square\n";
	dpsquare(F,m,n);
	cout<<endl;
	cout<<"+++ Dynamic Programming: Rectangle\n";
	dprectangle(F,m,n);


}
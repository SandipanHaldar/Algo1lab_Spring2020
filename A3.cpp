#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#define INF DBL_MAX
struct line
{
	double m;
	double c;
	int no;

};
struct point
{
	double x,y;
	
};
point solve(line l1,line l2)
{
	point ans;
	ans.y=((l1.m*l2.c)-(l2.m*l1.c))/(l1.m-l2.m);
	ans.x=(l2.c-l1.c)/(l1.m-l2.m);
	return ans;
}
void method1(struct line l[],int n,int M,int m)
{
	double mini=INF;cout<<"+++Method 1"<<endl;
	line current;current=l[m];int visible[n]={0};visible[m]=1;point q;q.x=-INF;q.y=-0.0;
	vector<point> soln;
	while(1)
	{
		int ind;mini=INF;point p;int temp=0;point pans;
		for(int i=0;i<n;i++)
		{
			if(i!=m && visible[i]==0)
			{
				
				p=solve(l[m],l[i]);if(p.x>q.x){temp=1;
				if(p.x<mini){mini=p.x;ind=i;pans=p;}}
			}
		}
		if(temp==0)break;cout<<"Line  "<<m<<" ";
		if(q.x==-INF)cout<<"From MINUS_INF to ("<<pans.x<<" ,"<<pans.y<<")"<<endl;
		else cout<<setprecision(10)<<"From ("<<q.x<<","<<q.y<<")"<<"to ("<<pans.x<<", "<<pans.y<<")"<<endl;
		m=ind;q=pans;
		visible[ind]=1;soln.push_back(pans);

		
	}
	cout<<"Line  "<<m<<" "; cout<<setprecision(10)<<"From ("<<q.x<<","<<q.y<<")"<<"to PLUS_INF"<<endl;
	
	return;

}
void merge(struct line arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 
	line L[n1], R[n2]; 
	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 
	i = 0; 
	j = 0;  
	k = l; 
	while (i < n1 && j < n2) 
	{ 
		if (L[i].m <= R[j].m) 
		{ 
			arr[k] = L[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	while (i < n1) 
	{ 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 
	while (j < n2) 
	{ 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 
void method2(struct line l[],int n)
{
	vector<point> ans;cout<<"+++Method 2"<<endl;
	//cout<<"l[0].m";
	point p;p=solve(l[0],l[1]);
	ans.push_back(p);//cout<<"hi";
	for(int i=2;i<n;i++)
	{
		double d=(ans[ans.size()-1].y-(l[i].m*ans[ans.size()-1].x)-l[i].c);
		/*if(d<ans.push_back(p);
		else
		{
			while(ans[ans.size()-1].x>p.x && ans.size())ans.pop_back();
			ans.push_back(p);
		}*/
	}
	for(int i=0;i<ans.size();i++)
		cout<<ans[i].x<<" "<<ans[i].y<<endl;
  
}

void mergeSort(struct line arr[], int l, int r) 
{ 
	if (l < r) 
	{ 
		
		int m = l+(r-l)/2; 
		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 
		merge(arr, l, m, r); 
	} 
} 


void printline(struct line A[], int size) 
{ 
	int i; 
	for (int i = 0; i < size; ++i)
	{
		cout<<"Line   "<<A[i].no<<": y = "<<A[i].m<<" x + "<<A[i].c<<endl;
	}
	printf("\n"); 
} 

int main()
{
	int n;
	cout<<"n= ";
	cin>>n;line l[n];int M,m;double maxi=-INF;double mini=INF;
	for (int i = 0; i < n; ++i)
	{
		cin>>l[i].m>>l[i].c;l[i].no=i;
		if(l[i].m>maxi){maxi=l[i].m;M=i;}
		if(l[i].m<mini){mini=l[i].m;m=i;}
	}
	cout<<"+++Lines Before sorting"<<endl;
	for (int i = 0; i < n; ++i)
	{
		cout<<"Line   "<<i<<": y = "<<l[i].m<<" x + "<<l[i].c<<endl;
	}
	//point p=solve(l[6],l[4]);cout<<p.x<<" "<<p.y;
	method1(l,n,M,m);
	
	mergeSort(l,0,n-1);
	cout<<"+++Lines After sorting"<<endl;
	printline(l,n);
	method2(l,n);



}
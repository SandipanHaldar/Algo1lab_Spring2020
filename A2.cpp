#include<iostream>
#include<bits/stdc++.h>
#include<string>
#include <vector>
using namespace std;

/*typedef struct _data
{
	string s;
	_data *next;
}data;*/

bool isPrime(int n) 
{ 
    
    if (n <= 1) 
        return false; 
  
     
    for (int i = 2; i < n; i++) 
        if (n % i == 0) 
            return false; 
  
    return true; 
}
vector<int> nature(vector<string> head);
vector<string> findallexp(int n)
{
	vector<string> perm;
	  
	if(n==1)
	{
		string s="1";
		perm.push_back(s);
	}
	else 
	{
		
		vector<string> a;vector<string> b;vector<string> c;vector<int> a1;vector<int> b1;vector<int> c1;
		int i,j;int temp=n/2;
		for(i=1;i<n;i++)
		{
			//cout<<i<<"              ";
			j=n-i;a=findallexp(i);b=findallexp(j);a1=nature(a);b1=nature(b);
			for(int x=0;x<a.size();x++)
			{
				string s;
				for(int y=0;y<b.size();y++)
				{
					
					s=a[x];
					s+=string("+");
					s+=b[y];
				}
				int tem=0;
				for(int q=0;q<perm.size();q++)
				{
					if(s==perm[q]){tem=1;break;}
				}
				if(!tem)perm.push_back(s);
			}
			/*if(n%i==0 && i!=1)
			{
			    int k=n/i;c=findallexp(k);c1=nature(c);
			    for(int w=0;w<a.size();w++){
			    s="";
			    if(a1[w]==1)s+=string("(");
			    
			    s+=a[w];if(a1[w]==1)s+=string(")");
			    for(int z=0;z<c.size();z++)
			    {
			    	
			    	s+=string("*");if(c1[z]==1)s+=string("(");
			    	s+=c[z];if(c1[z]==1)s+=string(")");
			    }
			    perm.push_back(s);}
			    
			}*/
		}
		int res=sqrt(n);//if(res*res ==n)res++;
		for(int i= 2;i<=res;i++)
		{
		
			if(n%i==0 && i!=1)
			{
				string s;
				a=findallexp(i);a1=nature(a);
			    int k=n/i;c=findallexp(k);c1=nature(c);
			    for(int w=0;w<a.size();w++){
			    s="";
			    if(a1[w]==1)s+=string("(");
			    
			    s+=a[w];if(a1[w]==1)s+=string(")");
			    for(int z=0;z<c.size();z++)
			    {
			    	
			    	s+=string("*");if(c1[z]==1)s+=string("(");
			    	s+=c[z];if(c1[z]==1)s+=string(")");
			    }
			    int tem=0;
			    for(int q=0;q<perm.size();q++)
				{
					if(s==perm[q]){tem=1;break;}
				}
				if(!tem)perm.push_back(s);
			    //perm.push_back(s);
			    }
			    
			}	
		}
	}
	return perm;
}
vector<int> nature(vector<string> head)
{
	vector<int> nat;int temp=0;
	for(int i=0;i<head.size();i++)
	{
		temp=0;
		for(int j=0;j<head[i].size();j++)
		{
			if(head[i][j]=='*'){nat.push_back(0);temp=1;break;}
		}
		if(temp==0)nat.push_back(1);
	}
	return nat;
}

void prntallexp(vector<string> head)
{
	for(int i=0;i<head.size();i++)
	cout<<head[i]<<endl;
	cout<<"..."<<head.size()<<"expressions"<<endl;
	return;
}
void Sortprint(vector<string> head)  
{  
    int i, j;int n=head.size();
    for (i = 0; i < n-1; i++)      
      
    
    {   
    	for (j = 0; j < n-i-1; j++) 
    	{
    	int a=0,b=0;
    	for(int x=0;x<head[j].size();i++)
    	{
    		if(head[j][x]=='1')a++;
    	}
    	for(int x=0;x<head[j+1].size();i++)
    	{
    		if(head[j+1][x]=='1')b++;
    	} 
        if (a>b)  
            {
            	string temp;
        		temp=head[j];
        		head[j]=head[j+1];
        		head[j+1]=temp;
    		}
        else if(a==b)
        {
        	if(head[j].size()>head[j+1].size())
        	{	string temp;
        		temp=head[j];
        		head[j]=head[j+1];
        		head[j+1]=temp;
    		}
        	
        }
   		}
    } 
    for(int i=0;i<head.size();i++)
	cout<<head[i]<<endl;
	cout<<"..."<<head.size()<<"expressions"<<endl; 
	return;
}  


int main()
{
	int n;cout<<"n= ";
	cin>>n;cout<<endl<<endl;
	cout<<"+++Before Sorting "<<endl;
	vector<string> head;
	
	head=findallexp(n);
	
	
	prntallexp(head);
	cout<<"+++After Sorting "<<endl;
	Sortprint(head);
	
	return 0;
}
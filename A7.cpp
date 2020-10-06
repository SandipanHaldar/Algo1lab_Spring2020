#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#define INF INT_MAX

typedef struct _tnode {
   struct _tnode *L;
   struct _tnode *R;
   int key;
} tnode;

typedef tnode *BST;
int fact(int n); 
  
int nCr(int n, int r) 
{ 
    return fact(n) / (fact(r) * fact(n - r)); 
} 
  
// Returns factorial of n 
int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
} 
void preorder ( BST T )
{
   if (T == NULL) return;
   
   printf("%d ", T -> key);
   
   
   preorder(T -> L);
   preorder(T -> R);
}

void inorder(BST T)
{
	if(T==NULL)return;
	inorder(T->L);
	printf("%d ", T -> key);
	inorder(T->R);

}
void BSTprn ( BST T )
{
   

   cout<<"---preorder listing"<<endl;
    preorder(T);
    cout<<endl;
    cout<<"---inorder listing"<<endl; 
    inorder(T);cout<<endl;
}

BST BSTins(BST T,int x)
{	
	if(T==NULL)
	{
		T= new tnode;
		T->key=x;
		T->L=NULL;T->R=NULL;
		return T;
	}
	else
	{
		if(T->key<x)T->R=BSTins(T->R,x);
		else T->L=BSTins(T->L,x);
	}
	return T;



}
BST BSTcons(vector<int> a,BST root){
	int n=a.size();
    for(int i=0;i<n;i++)
        root = BSTins(root, a[i]);
    return root;
}

int countseq(vector<int> a)
{
	int n=a.size();
	if(n<=2)return 1;
	vector<int> r;vector<int> l;
	for(int i=1;i<n;i++)
	{
		if(a[i]<a[0])l.push_back(a[i]);
		else r.push_back(a[i]);
	}
	int ans,ansl,ansr;
	ansl=countseq(l);ansr=countseq(r);
	ans=ansl*ansr*nCr(n-1,l.size());
	return ans;

}
vector<int> decToBinary(int n,int t) 
{ 
    int binaryNum[n-1]={0}; vector<int> ans(n-1,0); 
    int i = 0; 
    while (t > 0) { 
  
        
        binaryNum[i] = t % 2; 
        t = t / 2; 
        i++; 
    } 
  
     
    for (int j =0; j<n-1; j++) 
        ans[n-2-j]=binaryNum[j];
    return ans; 
} 
void findallseq(vector<int> a)
{
	int n=a.size();
	if(n<=2)
	{
		for(int i=0;i<n;i++)cout<<a[i]<<" ";
				cout<<endl;
		return;
	}
	vector<int> r;vector<int> l;
	for(int i=1;i<n;i++)
	{
		if(a[i]<a[0])l.push_back(a[i]);
		else r.push_back(a[i]);
	}
	int k=0;
	
	for(int t=0;t<pow(2,n-1);t++)
	{
		vector<int> bin(n-1);
		bin=decToBinary(n,t);int large=0,small=0;
		for(int j=0;j<n-1;j++)
		{
			if(bin[j]==1)large++;
			else if(bin[j]==0) small++;
		}
		
		if(large==r.size() && small==l.size())
		{
			cout<<"Sequence "<<k+1<<"   :";
			int itrl=0,itrr=0;
			cout<<a[0]<<" ";
			for(int z=0;z<n-1;z++)
			{
				if(bin[z]==1){cout<<r[itrr]<<" ";itrr++;}
				else {cout<<l[itrl]<<" ";itrl++;}
			}
			cout<<endl;k++;
		}
		

		
	}

}
void BSTfree(BST T)
{
	if(T==NULL)return;
	BSTfree(T->L);BSTfree(T->R);
	free(T);
}
int BSTsame(BST T1,BST T2)
{
	if(T1==NULL && T2==NULL)return 1;
	if(T1->key!=T2->key)return 0;
	if(BSTsame(T1->L,T2->L) && BSTsame(T1->R,T2->R) && (T1->key==T2->key))return 1;
	return 0;
} 
void checkall(BST T,vector<int> a)
{
	cout<<"+++ Checking all sequences"<<endl;
	int n=a.size();
	if(n<=2)
	{
		for(int i=0;i<n;i++)cout<<a[i]<<" ";
				cout<<endl;
		return;
	}
	vector<int> r;vector<int> l;
	for(int i=1;i<n;i++)
	{
		if(a[i]<a[0])l.push_back(a[i]);
		else r.push_back(a[i]);
	}
	int k=0;int cnt=0;
	
	for(int t=0;t<pow(2,n-1);t++)
	{
		vector<int> bin(n-1);
		bin=decToBinary(n,t);int large=0,small=0;
		for(int j=0;j<n-1;j++)
		{
			if(bin[j]==1)large++;
			else if(bin[j]==0) small++;
		}
		
		if(large==r.size() && small==l.size())
		{
			vector<int> v;v.push_back(a[0]);
			
			int itrl=0,itrr=0;
			
			for(int z=0;z<n-1;z++)
			{
				if(bin[z]==1){v.push_back(r[itrr]);itrr++;}
				else {v.push_back(l[itrl]);itrl++;}
			}
			BST T1=NULL;k++;T1=BSTcons(v,T1);if(BSTsame(T,T1))cnt++;BSTfree(T1);
		}
		

		
	
	
	}
	if(cnt==k)cout<<"All trees match "<<endl;

}

int main()
{
	int n;
	cin>>n;int iso;
	vector<int> a(n);BST T=NULL;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];

	}
	
	iso=countseq(a);
	cout<<"+++Sequence count"<<endl;
	cout<<"Total number of sequences =  "<<iso<<endl;
	cout<<"+++ All sequences"<<endl;findallseq(a);
	cout<<"+++BST constructed from input array"<<endl;
	T=BSTcons(a,T);
	BSTprn(T);
	checkall(T,a);

	

}
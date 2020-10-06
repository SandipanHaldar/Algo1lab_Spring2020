#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#define INF INT_MAX

typedef struct _tnode {
   struct _tnode *L;
   struct _tnode *R;
   int key;
} tnode;

typedef tnode *bintree;

void preorder ( bintree T )
{
   if (T == NULL) return;
   
   printf("%d ", T -> key);
   
   
   preorder(T -> L);
   preorder(T -> R);
}

void inorder(bintree T)
{
	if(T==NULL)return;
	inorder(T->L);
	printf("%d ", T -> key);
	inorder(T->R);

}
void prntree ( bintree T )
{
   

   cout<<"---preorder listing"<<endl;
    preorder(T);
    cout<<endl;
    cout<<"---inorder listing"<<endl; 
    inorder(T);cout<<endl;
}


bintree readtree(int *i)
{
	if(*i==0){
	bintree T;bintree p;
	p=new tnode;T=new tnode;
	p->key= -INF;
	p->L = NULL;
	p->R=T;
	
	}
	bintree T;T=new tnode;
	int k,l,r;
	cin>>k>>l>>r;++(*i);T->key=k;
	if(l==0 && r==0)
	{
		T->L=T->R=NULL;
		return T;
	}
	else if(l==0)
	{
		T->L=NULL;
		T->R=readtree(i);
		
	}
	else if(r==0)
	{
		T->R=NULL;
		T->L=readtree(i);
		
	}
	else
	{
		T->L=readtree(i);
		T->R=readtree(i);
		
	}
	return T;


}

void swapchild(bintree T)
{
	bintree temp;
	temp=T->L;
	T->L=T->R;
	T->R=temp;
	return ;
}
bintree lrotate ( bintree u )
{
   bintree v, w;

   v = u -> R;
   if (v == NULL) {
      cout<<"*** Left rotate not allowed"<<endl;
      return u;
   }
   w = v -> L;
   v -> L = u;
   u -> R = w;
   return v;
}

bintree rrotate ( bintree u )
{
   bintree v, w;

   v = u -> L;
   if (v == NULL) {
      cout<< "*** Right rotate not allowed"<<endl;
      return u;
   }
   w = v -> R;
   v -> R = u;
   u -> L = w;
   return v;
}

bintree makeskew(bintree T)
{
	
	while(T->L!=NULL)
	{
		T=rrotate(T);
	}
	if(T->R==NULL)return T;
	T->R=makeskew(T->R);
	
	return T;
}


bintree swapnode(bintree ptr1, bintree ptr2) 
{ 
    bintree tmp = ptr2->R; 
    ptr2->R = ptr1; 
    ptr1->R = tmp; 
    return ptr2; 
} 

void bSort(bintree *head, int count) 
{ 
    bintree *h; 
    int i, j, swapped; 
  
    for (i = 0; i <= count; i++) { 
  
        h = head; 
        swapped = 0; 
  
        for (j = 0; j < count - i - 1; j++) { 
  
            bintree p1 = *h; 
            bintree p2 = p1->R; 
  
            if (p1->key > p2->key ) { 
  
               
                *h = swapnode(p1, p2); 
                swapped = 1; 
            } 
  
            h = &(*h)->R; 
        } 
  
        
        if (swapped == 0) 
            break; 
    } 
} 


bintree rebalance(bintree T,int n)
{
	int i=0;if(T->L==NULL && T->R==NULL)return T;
	else if(T->L==NULL){
	while(i!=n/2)
	{
		T=lrotate(T);
		i++;
	}}
	else if(T->R==NULL)
	{
		while(i!=n/2)
		{
			T=rrotate(T);
			i++;
		}
	}
	else
	{
		T->L=rebalance(T->L,n/2-1);
		T->R=rebalance(T->R,n/2);
	}
	return T;


}

int main()
{
	int n;cout<<"enter n: "<<endl;
	cin>>n;
	cout<<"n= "<<n<<endl;
	bintree T;int i=0;
	T=readtree(&i);
	cout<<"+++Initial tree"<<endl;
	
	prntree(T);cout<<endl<<endl;

	//bintree S;
	T=makeskew(T);
	cout<<"+++After skewing"<<endl;
	prntree(T);cout<<endl<<endl;



	bSort(&T,n);cout<<"+++After Sorting"<<endl;
	prntree(T);cout<<endl<<endl;

	 
	T=rebalance(T,n);cout<<"+++After rebalancing"<<endl;
	prntree(T);
	


}
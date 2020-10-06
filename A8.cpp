#include<bits/stdc++.h>
using namespace std;


typedef struct 
{
	
	vector<int> v;
}heapnode;

typedef struct 
{
	heapnode *array;
	int capacity;
	int noofkeys;
	int noofnodes;
}heap;

heap initheap ( int n, int p )
{
   heap H;
   int i;

   H.capacity=p;
   H.noofkeys=n;
   H.noofnodes=ceil((double)n/p);
   H.array = (heapnode *)malloc((H.noofnodes+1)*sizeof(heapnode));
   
   return H;
}


heap insert (heap H,int x)
{
	int i,p,n;
	p=H.capacity;
	int  t;
	for(i=1;i<=H.noofnodes;i++)
	{
		if(H.array[i].v.size()<p)break;
	}
	n=i;
	
	H.array[n].v.push_back(x);sort(H.array[n].v.begin(),H.array[n].v.end());
	
	while(1)
	{
		if(i==1)return H;
		p=i/2;int r,q;r=*min_element(H.array[p].v.begin(), H.array[p].v.end());
		q= *max_element(H.array[i].v.begin(), H.array[i].v.end());
		if( r>=q)return H;
		t=H.array[p].v[0];
		H.array[p].v[0]=H.array[i].v[H.array[i].v.size()-1];
		H.array[i].v[H.array[i].v.size()-1]=t;
		sort(H.array[i].v.begin(),H.array[i].v.end());sort(H.array[p].v.begin(),H.array[p].v.end());
		i=p;
	}


	

	return H;
	
	
}



void prnheap(heap H)
{
	for(int i=1;i<=H.noofnodes;i++)
	{
		cout<<"   [";
		for(int j=H.array[i].v.size()-1;j>=0;j--)cout<<H.array[i].v[j]<<" ";
		cout<<"]\n";
	}
	
	return;

}

int findmax(heap H)
{
	if(H.array[1].v.size()==0)return -1;
	return H.array[1].v[H.array[1].v.size()-1];
}

void heapify(heap H,int i)
{
	int q=H.array[1].v[0];int l,r,lmax,rmax,m;int n= H.noofnodes;

	while(1)
	{
		l=2*i;r=2*i+1;
		if(l>n)return;
		if(l==n)m=l;
		else{
		lmax=*max_element(H.array[l].v.begin(), H.array[l].v.end());
		rmax=*max_element(H.array[r].v.begin(), H.array[r].v.end());
		if(lmax>=rmax)
		{
			m=l;
		}
		else m=r;}
		swap(H.array[m].v[H.array[m].v.size()-1],H.array[i].v[0]);
		sort(H.array[i].v.begin(),H.array[i].v.end());sort(H.array[m].v.begin(),H.array[m].v.end());
		i=m;

	}

}
heap deletemax(heap H)
{
	if (H.array[1].v.size() == 0) {
      printf("*** Deletion from empty heap attempted...\n");
      return H;
    }
    int temp=1; int i;int p=H.capacity;
    for( i=1;i<=H.noofnodes;i++)if(H.array[i].v.size()<p){temp=0;break;}
    if(temp!=0)i=H.noofnodes;
    if((H.array[i].v.size()==0))i--;	
    H.array[1].v[H.array[1].v.size()-1]=H.array[i].v[0];H.array[i].v.erase(H.array[i].v.begin());
    sort(H.array[i].v.begin(),H.array[i].v.end());sort(H.array[1].v.begin(),H.array[1].v.end());
    heapify(H,1); 
    return H;  

}


int main()
{
	int p,n;
	cin>>p>>n;
	int a[n];for(int i=0;i<n;i++)cin>>a[i];
	heap H;int i;
	H=initheap(n,p);
	for( i=0;i<n;i++)H=insert(H,a[i]);
	cout<<"+++ "<<i<<" insertions made\n";	
	prnheap(H);
	for( i=0;i<n;i++)
	{
		a[i]=findmax(H);
		H=deletemax(H);
		
	}
	cout<<"+++ "<<i<<" Deletion made\n\n";
	cout<<"+++ Input array sorted\n";
	for(i=n-1;i>=0;i--)if(a[i]!=0)cout<<a[i]<<" ";

	return 0;
	



}
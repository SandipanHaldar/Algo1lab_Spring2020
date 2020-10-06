#include<bits/stdc++.h>
using namespace std;


typedef struct _node
{
	int no;
	struct _node *next;

}node;

typedef struct 
{
	int V;
	vector<char>color;vector<int>idx;
	node **list;
}graph;

graph readgraph()
{
	int n;cin>>n;
	graph G;G.V=n;node *p;
	G.list=(node**)malloc(n*sizeof(node*));
	char c[n];for(int i=0;i<n;i++)cin>>c[i];
	for(int i=0;i<n;i++)G.list[i]=NULL;
	int u,v;
	while(1)
	{
		cin>>u;
		if(u==-1)break;cin>>v;
		p=G.list[u];
		while(p)
		{
			if(p->no==v)break;
			p=p->next;
		}
		if(p)continue;
		p=(node *)malloc(sizeof(node));
		p -> no = v;
	    p -> next = G.list[u];
	    G.list[u] = p;
	    p = (node *)malloc(sizeof(node));
	    p -> no = u;
	    p -> next = G.list[v];
	    G.list[v] = p;


	}
	for(int i=0;i<n;i++){G.color.push_back(c[i]);G.idx.push_back(i);}
	return G;

}

void prntgraph(graph G)
{
	node *p;int n=G.V;
	for(int i=0;i<n;i++)
	{
		p=G.list[i];
		cout<<"   ["<<G.color[i]<<"]";
		cout<<"  "<<G.idx[i]<<" -> ";
		while(p)
		{
			cout<<p->no<<" ";
			p=p->next;
		}
		cout<<"\n";

	}
}



graph getcolgraph(graph G,char c)
{
	graph ans;int temp=0;int n=G.V;node *p,*q;
	for(int i=0;i<n;i++)
	{
		if(G.color[i]==c){temp++;ans.idx.push_back(i);}

	}
	ans.list=(node**)malloc(temp*sizeof(node*));ans.V=temp;
	for(int i=0;i<temp;i++)
		ans.list[i]=NULL;
	for(int i=0;i<temp;i++)
	{
		p=G.list[ans.idx[i]];q=ans.list[i];
		while(p)
		{
			if(G.color[p->no]==c){
			while(q)
			{
				q=q->next;
			}
			q=(node *)malloc(sizeof(node));
			q->no=p->no;
			q->next=ans.list[i];
			ans.list[i]=q;}
			p=p->next;

		}
	}
	for(int i=0;i<temp;i++)ans.color.push_back(c);
	return ans;

}


void DFS(graph G,int *visited,int i,int *parent,int *level)
{
	if(visited[i]==1){//cout<<G.idx[i]<<" ";
		return;
	}
	int n=G.V;
	visited[i]=1;int itr;
	
	node *p=G.list[i];
	while(p)
	{
		for(int t=0;t<n;t++)
		{
			if(G.idx[t]==p->no){itr=t;break;}
		}
		if(visited[itr]==1 && parent[i]!=itr)
		{
			int z=i;
			int hash[G.V]={0};
			while(1)
			{
				cout<<G.idx[z]<<" ";
				z=parent[z];
				if(hash[z]==1)break;
				hash[z]=1;
			}
			cout<<"\n";
			DFS(G,visited,itr,parent,level);
		}
		else
		{
			parent[itr]=i;
			level[itr]=level[i]+1;
			DFS(G,visited,itr,parent,level);
			
		}
		p=p->next;
	}

}

int  *multidfs(graph G)
{
	int *visited,*parent,*level;
	int n=G.V;visited=(int*)malloc(n*sizeof(int));
	parent=(int*)malloc(n*sizeof(int));level=(int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		visited[i]=0;
		parent[i]=-1;
		level[i]=0;
	}
	for(int i=0;i<n;i++)
	{
		if(visited[i]==0)
		{
			level[i]=0;
			DFS(G,visited,i,parent,level);
		}
	}
	//for(int i=0;i<n;i++)cout<<level[i]<<"  hh\n" ;
	return parent;

}

int main()
{
	graph G;
	G=readgraph();
	cout<<"+++ original graph\n";
	prntgraph(G);
	graph GR;
	GR=getcolgraph(G,'r');
	cout<<"\n\n+++red subgraph (GR)\n";
	prntgraph(GR);
	graph GB;
	GB=getcolgraph(G,'b');
	cout<<"\n\n+++blue subgraph (GB)\n";
	prntgraph(GB);
	int *p;
	cout<<"+++Red cycles\n";
	p= multidfs(GR);
	cout<<"+++Blue cycles\n";
	int *q=multidfs(GB);

}
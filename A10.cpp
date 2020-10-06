#include<bits/stdc++.h>
using namespace std;
#define INFTY 1000000000


typedef struct 
{
	int V;
	char **oper;
	int **prices;

}graph;

graph readgraph()
{
	graph G;
	cin>>G.V;int n=G.V;
	
	G.oper=(char **)malloc(n*sizeof(char *));
	G.prices=(int **)malloc(n*sizeof(int *));
	for(int i=0;i<n;i++){G.oper[i]=(char *)malloc(n*sizeof(char));G.prices[i]=(int *)malloc(n*sizeof(int));}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			G.prices[i][j]=INFTY;
			G.oper[i][j]='-';
			if(j==i)G.prices[i][j]=0;

		}
	}	
	int u,v;
	while(1)
	{
		cin>>u;
		if(u==-1)break;cin>>v;
		int p;cin>>p;char c;cin>>c;
		G.oper[u][v]=c;G.prices[u][v]=p;


	}
	return G;

}

void prntgraph(graph G)
{
	int n=G.V;
	for(int i=0;i<n;i++)
	{
		printf("   %2d -> ",i) ;
		
		for(int j=0;j<n;j++)
		{
			if(G.prices[i][j]!=INFTY && G.prices[i][j]!=0)
				cout<<" "<<j<<"("<<G.prices[i][j]<<", "<<G.oper[i][j]<<") ";
		}
		cout<<"\n";

	}
	
}



graph getAIgraph(graph G)
{
	graph ans;
	int n=G.V;ans.V=n;
	ans.oper=(char **)malloc(n*sizeof(char *));
	ans.prices=(int **)malloc(n*sizeof(int *));
	for(int i=0;i<n;i++){ans.oper[i]=(char *)malloc(n*sizeof(char));ans.prices[i]=(int *)malloc(n*sizeof(int));}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			ans.prices[i][j]=INFTY;
			ans.oper[i][j]='-';
			if(j==i)ans.prices[i][j]=0;

		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(G.oper[i][j]=='a')
			{
				ans.oper[i][j]=G.oper[i][j];
				ans.prices[i][j]=G.prices[i][j];
			}
		}
	}
	return ans;	
	
}

int  **APSP(graph G)
{
	int n=G.V;
	int **dist;
	dist=(int **)malloc(n*sizeof(int *));
	for(int i=0;i<n;i++)dist[i]=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)dist[i][j]=G.prices[i][j];
	}
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j]= dist[i][k] + dist[k][j];
			}
		}
	}
	return dist;

}

void APSPone(graph G,int **C1)
{
	int n=G.V;
	int **dist;
	dist=(int **)malloc(n*sizeof(int *));
	for(int i=0;i<n;i++)dist[i]=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)dist[i][j]=C1[i][j];
	}

	for(int l=0;l<n;l++)
	{
		for(int k=0;k<n;k++)
		{
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(C1[i][j]==INFTY && G.prices[k][l]!=INFTY)
					{
						if(C1[i][k]+C1[l][j]+G.prices[k][l]<dist[i][j])
							dist[i][j]=C1[i][k]+C1[l][j]+G.prices[k][l];
					}
				}
			}
		}
	}
	cout<<"         ";
	for(int i=0;i<n;i++)printf("%6d ", i);
	cout<<"\n";
	for(int i=0;i<n;i++)
	{
		printf("   %2d -> ",i); 
		for(int j=0;j<n;j++)
		{
			if(dist[i][j]==INFTY)cout<<"     - ";
			else printf("%6d ",dist[i][j]);
		}
		cout<<"\n";
	}

}
void APSPany(graph G,int **C1)
{
	int n=G.V;
	int **dist;
	dist=(int **)malloc(n*sizeof(int *));
	for(int i=0;i<n;i++)dist[i]=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)dist[i][j]=C1[i][j];
	}
	int **temp=APSP(G);

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(dist[i][j]==INFTY && temp[i][j]!=INFTY)dist[i][j]=temp[i][j];
		}
	}
	cout<<"         ";
	for(int i=0;i<n;i++)printf("%6d ", i);
	cout<<"\n";
	for(int i=0;i<n;i++)
	{
		printf("   %2d -> ",i); 
		for(int j=0;j<n;j++)
		{
			if(dist[i][j]==INFTY)cout<<"     - ";
			else printf("%6d ",dist[i][j]);
		}
		cout<<"\n";
	}
	
}


int main()
{
	graph G;
	G=readgraph();int n=G.V;
	cout<<"+++ original graph\n";
	prntgraph(G);
	graph A=getAIgraph(G);
	cout<<"+++AI subgraph\n";
	prntgraph(A);cout<<"\n";
	cout<<"+++Cheapest AI prices\n";
	int **C1;C1=APSP(A);
	cout<<"         ";
	for(int i=0;i<n;i++)printf("%6d ", i);
	cout<<"\n";
	for(int i=0;i<n;i++)
	{
		printf("   %2d -> ",i) ;
		for(int j=0;j<n;j++)
		{
			if(C1[i][j]==INFTY)cout<<"     - ";
			else printf("%6d ",C1[i][j]);
		}
		cout<<"\n";
	}
	cout<<"\n";
	cout<<"+++Cheapest prices with at most one non-AI leg\n";
	APSPone(G,C1);cout<<"\n";
	cout<<"+++Cheapest prices with any number of non-AI legs\n";
	APSPany(G,C1);


	

}
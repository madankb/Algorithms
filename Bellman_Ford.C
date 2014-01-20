/**************************************************************************************************************************************************************************************
Questions:-

1)Why "V-1" iteration is done in outer for loop?.
  It is upper bound. If "V" no of vertices, then each vertex may have "V-1" edges to other vertex. So in the inner loop each vertex is relaxed, if only one vertex is relaxed in first
  iteration of inner for loop, we need to "V-1" iteration is to relax all other vertices.In some cases all the edges would be relaxed in first iteration and some cases it takes wort 
  case upper bound.
  

2)Why not equal to INT_MAX is checked?.
  Adding INT_MAX and some positive number makes overflow of bit and result become negative number because of the resulting binary number. 
  Eg:- INT_MAX = 2,147,483,647 whose binary represenation is 01111111111111111111111111111111, MSB is "0" for positive number and "1" for negative number through two's complement.
  INT_MAX + 2 = 2,147, 483, 649 which can't be represented in 32 bit integer, so adding 
  01111111111111111111111111111111 + 00000000000000000000000000000010 = 10000000000000000000000000000001 where 1 in MSB is -ive, 
  so +2,147,483,646 two's complement is -2,147,483,646 which is 10000000000000000000000000000001. The result of -2,147,483,646 instead of 2,147, 483, 649 is wrong. 
  
3)What is negative weight cycle?.
  Adding the weight in cycle of vertices gives negative value called as negative weight cycyle.
  
4)Why there is no shortest path in negative weight cycle?.  
  There is no shortest path in negative weight cycle, because the shorest path reduces infinitly as travesing through the cycle again and again. So shortest path can't be found in negative
  weight cycle.Example is in the above link
 
5)How struct members like V,E are accessed from non member function like bellman_ford?.
  Struct are "Public" by default, so it can be accessed anywhere within the program.
  
6)What is worst case of BFA?.
  O(VE).

*****************************************************************************************************************************************************************************************/
#include<iostream>
#include<stdio.h>
#include<limits.h>
using namespace std;
struct Graph
{
	int V,E;
	struct Edge* edge;
};
struct Edge
{
	int src;
	int dest;
	int weight;
};
struct Graph* CreateGraph(int V,int E)
{
	struct Graph* g=new Graph;
	g->V=V;
	g->E=E;
	g->edge=new Edge[E];

	return g;
}
bool Bellman_Ford(struct Graph* g,int source)
{
	int V=g->V;
	int E=g->E;
	
	int dist[V];
	
	for (int i=0;i<V;i++)
	{
		dist[i]=INT_MAX;
	}

	dist[source]=0;
	
	for(int i=1;i<=V-1;i++)
	{
		for(int j=0;j<E;j++)
		{
			int s=g->edge[j].src;
			int d=g->edge[j].dest;
			int w=g->edge[j].weight;
			
			if(dist[s] != INT_MAX && dist[d] > dist[s] + w)
			{
				dist[d]=dist[s]+w;
			}	
		}	
	}
	
	for(int j=0;j<E;j++)// Negative weight cycle can be relaxed or shortest path can be found infinetly. There is no end of finding the shortest path in negative weight cycle.
	{
		int s=g->edge[j].src;
		int d=g->edge[j].dest;
		int w=g->edge[j].weight;
		
		if(dist[s] != INT_MAX && dist[d] > dist[s] + w)
		{
			dist[d]=dist[s]+w;
			printf("Distance [%d] is reduced further from [%d] to [%d] because of negative cycle \n",dist[d],s,d);
			return false;
		}	
	}

	for(int i=0;i<V;i++)
	{
		printf("Distance from source [%d] to vertex [%d] is : %d\n",source,i,dist[i]);
	}

	return true;
}	
int main()
{
	int V=5;
	int E=8;
	struct Graph* g=CreateGraph(V,E);
	
	g->edge[0].src=0;
	g->edge[0].dest=1;
	g->edge[0].weight=-1;
	
	g->edge[1].src=0;
	g->edge[1].dest=2;
	g->edge[1].weight=4;
	
	g->edge[2].src=1;
	g->edge[2].dest=2;
	g->edge[2].weight=3;
	
	g->edge[3].src=3;
	g->edge[3].dest=2;
	g->edge[3].weight=5;
	
	g->edge[4].src=3;
	g->edge[4].dest=1;
	g->edge[4].weight=1;
	
	g->edge[5].src=1;
	g->edge[5].dest=3;
	g->edge[5].weight=2;
	
	g->edge[6].src=1;
	g->edge[6].dest=4;
	g->edge[6].weight=2;
	
	g->edge[7].src=4;
	g->edge[7].dest=3;
	g->edge[7].weight=-3;
	
	int source=0;
	if (!Bellman_Ford(g,source))
		printf("Negative cycle exists \n");
	
	struct Graph* n=CreateGraph(5,5);
	
	n->edge[0].src=0;
	n->edge[0].dest=1;
	n->edge[0].weight=1;
	
	n->edge[1].src=1;
	n->edge[1].dest=2;
	n->edge[1].weight=1;
	
	n->edge[2].src=2;
	n->edge[2].dest=3;
	n->edge[2].weight=-3;
	
	n->edge[3].src=3;
	n->edge[3].dest=1;
	n->edge[3].weight=1;
	
	n->edge[4].src=2;
	n->edge[4].dest=5;
	n->edge[4].weight=1;
	
	if (!Bellman_Ford(n,source))
		printf("Negative cycle exists \n");
	
}	

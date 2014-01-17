/*******************************************************************************************************************************************************************************************
Dijsktra algorithm is used to calculate the shortest distance from the source vertex to all the vertices in the graph. In real world, it is calcualting all shortest distance from the home
to all nearby place in your city.

Dijsktra algorithm follows the problem solving paradigm called Greedy algorithm. It finds the optimal solution for the current situation and use that optimal solution to find next optimal
solution in the current situation.

Time complexity :- O(V^2) since it the vertices are represented in matrix.

********************************************************************************************************************************************************************************************/
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<limits.h>
#define V 9
using namespace std;
int mindistance(int dist[V],bool visited[V])
{
	int min=INT_MAX;
	int v=0;
	
	for (int i=0;i<V;i++)
	{
		if (visited[i] == false && dist[i] < min)//Greedily select the shortest distance vertex to find the distance to other vertices.
		{
			min=dist[i];
			v=i;
		}	
	}

	return v;
	
}	
int dikshitra(int G[V][V],int src)
{
	bool visited[V];//If the distance from this vertex to all other vertices are calcualted, then vertext is changed as visited.
	
	int dist[V];
	
	for (int i=0;i<V;i++)
	{
		visited[i]=false;
		dist[i]=INT_MAX;
	}	
	
	dist[src]=0;//Make the source vertex as zero to start from the vertex
	
	cout<<"Distance is :"<<dist[3]<<endl;
	
	for(int v=0;v<V;v++)
	{
		int u=mindistance(dist,visited);//Find the vertex which has the shortest distance from the source.
		
		cout<<"U is :"<<u<<endl;
		
		visited[u]=true;//We have visted it and going to calcualte the distace from it to reachable vertex.
		
		for (int v=0;v<V;v++)
		{
			if (G[u][v] != 0 && visited[v] == false && dist[u] + G[u][v] < dist[v])
				dist[v]=dist[u]+G[u][v];//If the distance to the destination vertex is shorter than distance calcualted from other vertex, then update it.
			
		}	
	}

	for (int i=0;i<V;i++)
	{
		printf("Distance from source [%d] to destination [%d] is : %d\n",src,i,dist[i]);
	}	
	
}	
int main()
{
	int graph[V][V]={{0,4,0,0,0,0,0,8,0},
	                 {4,0,8,0,0,0,0,11,0},
			 {0,8,0,7,0,4,0,0,2},
			 {0,0,2,0,9,15,0,0,0},
			 {0,0,0,9,0,10,0,0,0},
			 {0,0,4,14,10,0,2,0,0},
			 {0,0,0,0,0,2,0,1,6},
			 {8,11,0,0,0,0,1,0,7},
			 {0,0,2,0,0,0,6,7,0}};
	

	int src=0;
			 
	dikshitra(graph,src);		 
 };

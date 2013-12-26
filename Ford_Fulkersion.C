/******************************************************************************************************************************************************************************************

What is Maximum Flow Problem :-
        1) A list of pipes is given, with different flow-capacities. These pipes are connected at their endpoints. 
	   What is the maximum amount of water that you can route from a given starting point to a given ending point?    
        
	2) A company owns a factory located in city X where products are manufactured that need to be transported to the distribution center in city Y. 
	   You are given the one-way roads that connect pairs of cities in the country, and the maximum number of trucks that can drive along each road. 
	   What is the maximum number of trucks that the company can send to the distribution center?
	   
	3) http://www.geeksforgeeks.org/wp-content/uploads/ford_fulkerson11.png   
	  
Terms to understand :- 

        1) Residual( Remaining) capacity :- Number of trucks can be sent after the no of trucks sent. If road has capacity of 5 trucks, 3 trucks are already send. So RC is 2 trucks.
	
	2) Residual graph :- Graph which maintains the residual capacity of the original graph.
	
	3) Augmenting path :- A path exists from "source" to "destination" with some minimum flow.
	
	4) Min s-t cut :- The cut which makes the graph in to two different part and "terminal" t is not reachable from source "s". There may be many cuts like that, but we want the
	                  minimum cut (Minimum value edge). Minimum cut edges = Max flow network (Edges which determines the maximum flow in the network). It is the edges in the
			  residual graph which was previously reachable now it is not reachable. Eg :- trying change edge in opposite direction of 2 to 3.
       
Algorithm steps :-

        1) Do BFS to find any path exists between "s" and "t". If exists track the path in array path[V]. 
	
	2) Find minimum no of trucks can be sent in the path. Eg :- [0]_[1]_[3]_[5] path exists and minimum capacity is 12 between [1]_[3]. It restricts only 12 number of trucks can be
	   sent from 0 to 5 in that path.
	   
	3) Update residual graph by subtracting original capacity from the minimum capacity.  
	
	4) Add the calculated number of minimum number of trucks to find total number of trucks can be sent to destination from source.

        4) Repeat the BFS to find any other path exixts between "s" and "t" in residual graph and update path[V].Do the operation 2,3,4 until there is no path exists between "s" and "t".
	
Time complexity :-

       1) BFS - O(E)
       
       2) Number of augmenting path (while loop) O(VE)
       
       3) O(VE).O(E) - O(VE^2)
       
       http://www.cs.fsu.edu/~asriniva/courses/alg06/Lec28.pdf
       
********************************************************************************************************************************************************************************************/
#include<iostream>
#include<stdio.h>
#include<strings.h>
#include<queue>
#include<limits.h>
#define V 6
using namespace std;
bool BFS(int rG[V][V],int s,int t,int path[V]) //O(E) - Visiting all the edges to find path between vertices.
{
	bool visited[V]; //You made mistake here, by declaring int and BFS was not working.
	memset(visited,0,sizeof(visited));
	
	queue<int> q;
	q.push(s); //Start from source eg:- 0
	visited[s]=true; // To prevent self-loop
	
	path[s]=-1;
	
	while (!q.empty())
	{
		int u=q.front();//edges visited changes everytime
		q.pop();
		
		for(int v=0;v<V;v++)//Try all edges to find the path exists
		{
			if (visited[v]==false && rG[u][v] > 0)
			{
				//cout<<"pushing for "<<u<<" "<<v<<endl;
				q.push(v);
				visited[v]=true;
				path[v]=u;//Source "u" to destination "v".path[5]=1, exists edge from 1 -> 5. Index is destination and value is source.
				// Path is traced in reverse way. If 1 is reachable from 0, it should be path[0]=1, but it is changed as path[1]=0 because from 0 you can reach
				// 1 and 2 same path[0] can't be update as 1 and 2 (only one variable can be hold in array)
                                // but vice versa is possible path[1]=0, path[2]=0 it means from 0 you can reach 1 and 2.
				// You tried the path[0]=1 version below and it did not work. The way mentioned here is exact BFS.
			}	
		}
	}
	
	for(int i=t;i>0;i--)
	{
		if (i != path[i])
			printf("%d ---> %d \n",i,path[i]);
	}	

	//fflush(stdout);
	return visited[t];//Returns true if path exists from source "s" to destination "t"
}
void dfs(int G[V][V],int s,bool visited[V])
{
	visited[s]=true;
	for (int i=0;i<V;i++)
	{
		if (!visited[i] && G[s][i] > 0)
			dfs(G,i,visited);
	}	
}	
int Ford_Fulkersion(int G[V][V],int s,int t)
{
	int path[V]; // Tracks the path from source to destination. Both index and value of array represent edges, eg:- path[0] = 1, it means path exists between edges 0 and 1
	
	int v=0;
	int u=0;
	
	int rG[V][V];
	
	for (int i=0;i<V;i++)
	{
		for (int j=0;j<V;j++)
		{
			rG[i][j]=G[i][j];
		}
	}	
	
	int max_path_flow=0;
	
	while (BFS(rG,s,t,path)) // No of augmenting path - O(VE) - Every time one edge is minimum and taken out of path and visits all other edges.
	{
		printf("[%d]_",t);
		
		int min_path_capacity=INT_MAX;
		for(v=t;v != s;v=path[v]) // Go back from the destination to source to find minimum capcity in the path.
		{
			u=path[v];
			printf("[%d]_",u);
			min_path_capacity=min(rG[u][v],min_path_capacity);
		}
		printf("\n");
		
		printf("Minimum capacity in the path is: [%d] \n",min_path_capacity);
		fflush(stdout);
		
		for (v=t;v!=s;v=path[v])
		{
			u=path[v];
			rG[u][v]=rG[u][v]-min_path_capacity;//One edge would be made zero, because that edge decides minimum path flow, so DFS choose different path every time.
		}
		
		max_path_flow=max_path_flow+min_path_capacity;
	}
	
	bool visited[V];

	memset(visited,false,sizeof(visited));	

	dfs(rG,0,visited);
	//Minimum edge which determines the path flow became zero now in residual graph.DFS finds the reachable vertex from source.If visited[4] is false,it is not reachable from source 0.
	//Miniumm edges are not reachable now because the value in residual graph is zero now. 
	
	for (int i=0;i<V;i++)
	{
		for (int j=0;j<V;j++)
		{
			if (visited[i] && !visited[j] && G[i][j] > 0)//Check is vertex reachable from source 0 and vertex not reachable and previously it was reachable from original graph.
				cout<<"["<<i<<"]"<<" ---> "<<"["<<j<<"]"<<endl; // those are min-cut edges.
		}
	}	
	
	return max_path_flow;
}
bool BFS_V2(int G[V][V],int s,int t,int path[V])
{
	queue<int>q;
	q.push(s);
	
	bool visited[V];
	//visited[s]=true;
	memset(visited,0,sizeof(visited));
	
	int path_t[V];
	
	memset(path,-1,sizeof(path_t));
	//for (int i=0;i<V;i++)
	//path[i]=-1;
	
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		
		for (int v=u;v<V;v++)
		{
			//cout<<"path is :"<<path[v]<<endl;
			
			if (visited[u]==false && path[u] == -1 && G[u][v] > 0)
			{
				cout<<"pushing for "<<u<<" "<<v<<endl;
				q.push(v);
				visited[u]=true;
				path[u]=v;
			}
		}	
	}

	int i=0;
	
	cout<<"here is : "<<G[4][5]<<endl;
	for(i=s;i != t && i != -1;i=path[i])
	{
		cout<<i<<"--->"<<path[i]<<endl;
	}
	
	if (i == t)
		return true;
	else
		return false;
		
}
int Ford_Fulkersion_V2(int G[V][V],int s,int t)
{
	int path[V]; // Tracks the path from source to destination. Both index and value of array represent edges, eg:- path[0] = 1, it means path exists between edges 0 and 1
	
	int v=0;
	int u=0;
	
	int rG[V][V];
	
	for (int i=0;i<V;i++)
	{
		for (int j=0;j<V;j++)
		{
			rG[i][j]=G[i][j];
		}
	}	
	
	int max_path_flow=0;
	
	while (BFS_V2(rG,s,t,path)) // No of augmenting path - O(VE) - Every time one edge is minimum and taken out of path and visits all other edges.
	{
		printf("[%d]_",s);
		
		int min_path_capacity=INT_MAX;
		for(v=s;v != t;v=path[v]) // Go back from the destination to source to find minimum capcity in the path.
		{
			u=path[v];
			printf("[%d]_",u);
			min_path_capacity=min(rG[v][u],min_path_capacity);
		}
		printf("\n");
		
		printf("Minimum capacity in the path is: [%d] \n",min_path_capacity);
		fflush(stdout);
		
		for (v=s;v !=t;v=path[v])
		{
			u=path[v];
			rG[v][u]=rG[v][u]-min_path_capacity;//One edge would be made zero, because that edge decides minimum path flow, so DFS choose different path every time
			//After the subtraction, some path may have minimum edge(before it was not minimum) when comparing to existing minimum edge in the original graph.
			
			cout<<"Reduced size of "<<v<<" and " << u <<" is : "<<rG[v][u]<<endl;
		}
		
		
		max_path_flow=max_path_flow+min_path_capacity;
	}
	
	return max_path_flow;
}
int main()
{
	int G[V][V]={{0,16,13,0,0,0},
	             {0,0,10,12,0,0},
		     {0,4,0,0,14,0},
		     {0,0,9,0,0,20},
		     {0,0,0,7,0,4},
		     {0,0,0,0,0,0}};
		     
	//BFS_V2(G,0,5);	     
		     
	printf("Maximum path flow is : %d \n",Ford_Fulkersion(G,0,5));
		     
	//printf("Maximum path flow is : %d \n",Ford_Fulkersion_V2(G,0,5));	     
		     
}	

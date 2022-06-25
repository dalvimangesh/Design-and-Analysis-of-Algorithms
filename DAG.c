#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

/* Space to store parameter's */
int entry[500],exitt[500],visited[500],Predecessor[500];
int clk = 0;
bool DAG = true;

/* Singly Linked list */
struct List {
	int item;
	struct List* next;
};
typedef struct List list;

/* Struct to store edge ( Pair of vertex) */
struct Edge {
	int u;
	int v;
	struct Edge* next;
};
typedef struct Edge edge;

/* creating empty stack and empty edge_list */
struct Edge* edges[500];
struct List* stack = NULL;

/* Function to add given value in adjacency list of given value */
list* Attach(list* g,int value)
{
	list* node = (list*) malloc(sizeof(list));
	node -> item = value;
	node -> next = NULL;
	
	if(g==NULL) return node;
	
	list* head = g;
	
	/* adding element in the last by not changing head */
	while(g->next!=NULL) g = g->next;
	g->next = node;
	return head;
}

/* Function to push element in stack */
list* Push(list* g,int value)
{
	list* node = (list*) malloc(sizeof(list));
	node -> item = value;
	node -> next = g;
	return node;
}

/* Function to to push pair of vertex in edge_list */
edge* PushEdge(edge* e,int uu,int vv)
{
	edge* node = (edge*) malloc(sizeof(edge));
	node -> u = uu;
	node -> v = vv;
	node -> next = NULL;
	
	if(e == NULL) return node;
	
	edge* head = e;
	
	/* adding pair in the last by not changing head */
	while(e->next!=NULL) e = e->next;
	e->next = node;
	return head;
}

/* DfsExplore through given vertex */
void DfsExplore(list* g[],int vertex)
{
	visited[vertex] = 1;
	entry[vertex] = clk++;
	
	list* ListPtr = g[vertex];
	if(ListPtr == NULL) {
		exitt[vertex] = clk++; 
		stack = Push(stack,vertex);
		return;
	}
	
	/* Exploring list of current vertex */
	while(ListPtr != NULL)
	{
		if(visited[ListPtr->item] == -1) 
		{
			DfsExplore(g,ListPtr->item);
			Predecessor[ListPtr->item] = vertex;
		}
		else
		{
			/* Condition for back edge */
			if( entry[ListPtr->item] < entry[vertex] 
				&& exitt[ListPtr->item] == -1 && exitt[vertex] == -1 )
			{
				/* Back edge is there so given graph is not DAG */
				DAG=false;
				edges[vertex] = PushEdge(edges[vertex],vertex,ListPtr->item);
			}
		}
		ListPtr = ListPtr->next;
	}
	
	exitt[vertex] = clk++;
	
	/* Pushing element in stack before leaving it */
	stack = Push(stack,vertex);
	return;
}

/* DFS through each vertex if possible */
void DFS(list* g[],int n)
{	
	for(int i=1;i<=n;i++)
	{
		if(visited[i]==-1) DfsExplore(g,i);
	}
}

/* Function to print entry exit time of vertex of back edge */
void PrintBackEdge(int n)
{
    for(int i=1; i<=n;i++)
    {
        edge* ptr = edges[i];
        while(ptr != NULL)
        {
            printf("%d %d %d %d\n",entry[ptr->v],entry[ptr->u],exitt[ptr->u],exitt[ptr->v]);
            ptr = ptr -> next;
        }
    }
}

/* Function to print whole stack */
void PrintStack()
{
	while(stack !=NULL)
	{
		printf("%d\n",stack->item);
		stack = stack -> next;
	}
}

int main()
{	
	/* no of vertex */
	int n = 0;
	scanf(" %d",&n);
	
	/* creating empty graph and taking input for graph */
	list* graph[n+1];
	for(int i=0; i<=n; i++)
	{
		graph[i] = NULL;
        edges[i] = NULL;
	}
	for(int i=1; i<=n; i++)
	{
		int vertex = 0;
		while(true)
		{
			scanf(" %d",&vertex);
			if(vertex==-1) break;
			graph[i] = Attach(graph[i],vertex);
		}
	}
	
	/* making -1 and NULL and 0 to respective values */
	for(int i=0; i<500; i++) {
		entry[i]= -1;exitt[i]= -1;visited[i]= -1;Predecessor[i]= -1;
	}
	DAG = true; //assuming given graph as a DAG
	clk = 0;
	stack = NULL;
	
	/* input for start vertex of dfs */
	int start_point = 0;
	scanf(" %d",&start_point);
	
	/* calling dfs through start vertex */
	DfsExplore(graph,start_point);
	/* dfs through each vertex if possible */
	DFS(graph,n);
	
	//result1
	for(int i=1;i<=n;i++)
	{
		printf("%d %d %d\n", entry[i], exitt[i], Predecessor[i]);
	}
	
	//result2
	/* if dag */
	if(DAG==true) 
	{
		printf("DAG\n");
		
		/* toposort */
		PrintStack();
	}
	else 
	{
		printf("Not a DAG\n");
		
		/* Printing Back edge's */
		PrintBackEdge(n);
	}
	
	return 0;
}

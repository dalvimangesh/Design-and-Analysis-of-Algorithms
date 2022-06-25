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

/* creating empty stack and empty edge_list 
to store edges and space to store no of SCC*/
struct List* stack = NULL;
struct List* order[500];
int SCC = 0;

/* Function to add given value in adjacency list of given value */
list* Attach(list* g,int value)
{
	list* node = (list*) malloc(sizeof(list));
	node -> item = value;
	node -> next = NULL;
	
	if(g==NULL) return node;
	
	list* head = g;
	
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
		/* checking visited or not */
		if(visited[ListPtr->item] == -1) 
		{
			DfsExplore(g,ListPtr->item);
			Predecessor[ListPtr->item] = vertex;
		}
		ListPtr = ListPtr->next;
	}
	exitt[vertex] = clk++;
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

/* Function to print whole stack */
void PrintStack()
{
	while(stack !=NULL)
	{
		printf("%d ",stack->item);
		stack = stack -> next;
	}
}

/* Function to print given graph having vertex == n */
void PrintGraph(list* g[], int n)
{
	for(int i=1;i<=n;i++)
	{
		list* ptr = g[i];
		while(ptr!=NULL)
		{
			printf("%d ",ptr->item);
            ptr=ptr->next;
		}
		printf("-1\n");
	}
}

/* DFS function which stores vertex in it's SCC list*/
void DfsExploreWithOrder(list* g[],int vertex)
{
	visited[vertex] = 1;
	
	/* storing in SCC'th */
	order[SCC] = Attach(order[SCC], vertex);
	
	/* Exploring list of current vertex */
	list* ListPtr = g[vertex];	
	while(ListPtr != NULL)
	{
		/* checking visited or not */
		if(visited[ListPtr->item] == -1) 
		{
			DfsExploreWithOrder(g,ListPtr->item);
		}
		ListPtr = ListPtr->next;
	}
	return;
}

/* Function to get the SCC of given graph through DFS */
void GetSCC(list* g[],int n)
{
	
	list* ptr = stack;
	
	/* assume SCC's = 0 */
    SCC = 0;
	
	/* going via topological order */
	while(ptr!=NULL)
	{
		if(visited[ptr->item] == -1)
		{
			DfsExploreWithOrder(g,ptr->item);
			
			/* incresing count of SCC */
			SCC++;
		}
		ptr = ptr -> next;
	}
	
	return;
}

/* Function to print the SCC in given graph*/
void PrintSCC()
{
	for(int i=0;i<SCC;i++)
	{
		list* ptr = order[i];
		while(ptr->next!=NULL)
		{
			printf("%d ",ptr->item);
            ptr = ptr->next;
		}
		printf("%d\n",ptr->item);
	}
}

int main()
{	
	/* no of vertex */
	int n = 0;
	scanf(" %d",&n);
	
	/* creating empty graph's and taking input for graph given graph*/
	list* graph[200];
    list* reverse_graph[200];
	for(int i=0; i<100; i++)
	{
		graph[i] = NULL;
		reverse_graph[i] = NULL;
        order[i]=NULL;
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
	for(int i=0; i<500; i++) 
	{
		entry[i]= -1;exitt[i]= -1;visited[i]= -1;Predecessor[i]= -1;
	}
	clk = 0;
	stack = NULL;
	
	/* Doing DFS on whole graph with order of vertex */
	DFS(graph,n);
	
	/* creating reverse graph of given graph */
	for(int i=1; i<=n; i++)
	{
		list* ptr = graph[i];
		while(ptr!=NULL)
		{
			reverse_graph[ptr->item] = Attach(reverse_graph[ptr->item],i);
			ptr = ptr->next;
		}
	}
	
	/* printing all the outneighbour's of reverse graph*/
	PrintGraph(reverse_graph,n);
	
	/* for doing dfs on reverse graph making visited as -1 */
    for(int i=0; i<200; i++) visited[i]= -1;
	
	/* Function to get SCC's in graph */
	GetSCC(reverse_graph,n);
	
	/* Function to print SCC's of graph */
	PrintSCC();
	
	return 0;
}

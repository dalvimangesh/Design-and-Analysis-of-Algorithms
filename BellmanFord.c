#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

/* Space to store parameter's */
int d[500],Predecessor[500],LastChanged = -1;

/* Struct to store edge ( Pair of vertex) */
struct Edge {
	int u;
	int v;
	int weight;
	struct Edge* next;
};
typedef struct Edge edge;

/* Singly Linked list */
struct List {
	int item;
	struct List* next;
};
typedef struct List list;

/* Function to to push pair of vertex in edge_list */
edge* PushEdge(edge* e,int uu,int vv, int wt)
{
	edge* node = (edge*) malloc(sizeof(edge));
	node -> u = uu;
	node -> v = vv;
	node -> weight = wt;
	node -> next = NULL;
	
	if(e == NULL) return node;
	
	edge* head = e;
	
	/* adding pair in the last by not changing head */
	while(e->next!=NULL) e = e->next;
	e->next = node;
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

/* Function to relax given edge and returning true 
if we changed distance of the vertex else false */
bool RelaxEdge(edge* e)
{
	/* a -> b */
	int a = e->u;
	int b = e->v;
	int wt = e->weight;
	
	if( d[b] > ( d[a] + wt ) )
	{
		d[b] = d[a] + wt;
		Predecessor[b] = a;
		return true;
        printf("*\n");
	}
	
	/* Vertex distance is not changed */
	return false;
}

/* BelmanFord algo to find shortest distance from single source
and function will return false if there is a negative weight cycle */
bool BelmanFord(edge* e,int source,int n)
{
	/* source distance is zero */
	d[source] = 0;
	
	/* flag to check wheather we have changed distance of a at 
	least one vertex or not in one iteration over all edges */
	bool flag = false;
	
	/* N rounds for checking negative edge weight cycle */
	for(int i=1;i<=n;i++)
	{
		/* initial conditions */
		flag = false;
		edge* ptr = e;
		while(ptr != NULL)
		{
			if(RelaxEdge(ptr) == true) 
            {
                if(i==n && LastChanged==-1){
                    LastChanged = ptr->v;
                }
				
				/* we have changed distance of at least one vertex */
                flag = true;
              
            }
            ptr = ptr->next;
		}
		
		if(flag == false) return true;
	}
	return false;
}

/* Function to print negative edge weight cycle */
void PrintCyclye()
{
	/* empty stack to store cycle */
	list* stack = NULL;

	/* space to store wheather we have 
	visited vertex or not while retracing path */
    bool visited[500] = {0};

	/* vertex whose value get changed first in last round */
    int last = LastChanged;

	/* Retracing the path using pred array */
    while( visited[last] == false )
    {
        stack = Push(stack,last);
        visited[last] = true;
        last = Predecessor[last];
    }

	/* Printing negative edge weight cycle */
    while(true)
    {
		if(stack->item == last ) {
			printf("%d",stack->item);
			break;
		}
        printf("%d ",stack->item);
        stack = stack -> next;
    }
}

int main()
{	
	/* no of vertex and edges */
	int n =0, m=0;
	scanf(" %d %d",&n,&m);
	
	/* creating empty edges list and taking input for all edges */
	edge* EdgeList = NULL;
	
	for(int i=1;i<=n;i++) {
        d[i] = 500;
        Predecessor[i]=-1;
    }

	for(int i=1; i<=m; i++)
	{
		int u = 0,v = 0,wt = 0;
		scanf(" %d %d %d", &u, &v, &wt);
		EdgeList = PushEdge(EdgeList,u,v,wt);
	}
	 
    int source;
    scanf(" %d",&source);

	/* Result */
	if(BelmanFord(EdgeList,source,n))
	{
		for(int i=1;i<=n;i++)
		{
			if(d[i]!=500) printf("%d %d\n",d[i], Predecessor[i]);
			else printf("Unreachable\n");
		}
		
	} else{
        PrintCyclye();
    }
    
	return 0;
}

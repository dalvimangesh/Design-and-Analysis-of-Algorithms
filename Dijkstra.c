#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

/* Singly Linked list */
struct List {
	int item;
	int weight;
	struct List* next;
};
typedef struct List list;

/* struct to store key value in heap */
struct data {
	int vertex;
	int value;
};
typedef struct data Data;

/* Empty Priority queue */
Data Pq[500];

/* space to store vertex index in heap */
int IndexOfVertex[500];

/* space to store shortest distance from source , pred and current size of heap */
int d[500];
int Pred[500];
int LastOfPq = 0;

/*Function to swap value at two location */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Function to add given value in adjacency list of given value */
list* Attach(list* g,int value, int wt)
{
	list* node = (list*) malloc(sizeof(list));
	node -> item = value;
	node -> weight = wt;
	node -> next = NULL;
	
	if(g==NULL) return node;
	
	list* head = g;
	
	/* adding element in the last by not changing head */
	while(g->next!=NULL) g = g->next;
	g->next = node;
	return head;
}

/*Function to minheapfy the given index value at its correct position */
void MinHeapFy(int index)
{
    int right = 2 * index;
    int left = 2 * index + 1;
    while (true)
    {
		/* base condition */
        if (right > LastOfPq || left > LastOfPq) break;
		
		/* finding min of two child then replacing value in that min */
        int min = Pq[right].value > Pq[left].value ? left : right;
		
        if ( Pq[index].value > Pq[min].value )
        {
			swap( &IndexOfVertex[Pq[index].vertex], &IndexOfVertex[Pq[min].vertex] );
            swap( &Pq[index].value, &Pq[min].value );
            swap( &Pq[index].vertex, &Pq[min].vertex );
			
			/* going for min child as parent */
            index = min;
        }
        else break;
		
        right = 2 * index;
        left = 2 * index + 1;
    }
}

/* Function to get min value of the heap */
int ExtractMin()
{
	int val = Pq[1].vertex;
	
	Pq[1].value = Pq[LastOfPq].value;
	Pq[LastOfPq].value = 5000;
	
	MinHeapFy(1);
    LastOfPq--;
	
	return val;
}

/* Function to shiftUp the given index value at its correct position*/
void ShiftUp(int index)
{
	while ( Pq[index/2].value  > Pq[index].value )
    {
		swap( &IndexOfVertex[Pq[index/2].vertex], &IndexOfVertex[Pq[index].vertex] );
        swap( &Pq[index/2].value, &Pq[index].value );
        swap( &Pq[index/2].vertex, &Pq[index].vertex );
        index /= 2;
    }
}

/* Decrease Key */
void DecreaseKey(int v, int NewValue)
{
	Pq[ IndexOfVertex[v] ].value = NewValue;
	ShiftUp( IndexOfVertex[v] );
}

/* Function to check heap is empty or not */
bool IsHeapEmpty()
{
    return LastOfPq >= 1;
}

/* Function to Relax given edge */
void Relax(int u, int v, int wt)
{
	if( d[v] > ( d[u] + wt ) )
	{
		DecreaseKey(v, (d[u] + wt) );
		d[v] = d[u] + wt;
		Pred[v] = u;
        //printf("%d %d %d\n", u ,v , (d[u] + wt) );
	}
}

/* Signle shource shortest path Function */
void DijkstraS(list* g[], int source)
{
	/* source distace is zero */
	DecreaseKey(source,0);
	d[source] = 0;
	
	while( IsHeapEmpty() )
	{
		/* Extracting shortest distance vertex from the heap */
		int ele = ExtractMin();
		
		/* Relaxing all edges of current element*/
		list* ptr = g[ele];
		while( ptr != NULL )
		{
			/* (u,v) */
			Relax(ele, ptr->item, ptr->weight);
            ptr = ptr->next;
		}
	}
}

int main(){
	
	/* no of vertex */
	int n = 0;
	scanf(" %d",&n);
	
	/* creating empty graph and taking input for graph */
	list* graph[n+1];
	for(int i=1; i<=n; i++)
	{
		graph[i] = NULL;
		d[i] = 5000;
		
		/* Assuming initially all vertex all pred as -1 
		and there distance from the source is infinity */
		Pred[i] = -1;
		IndexOfVertex[i] = i;
		Pq[i].vertex = i;
		Pq[i].value = 5000;
	}
	
	/* making size of heap as n */
	LastOfPq = n;
	
	/* Input for given graph */
	for(int i=1; i<=n; i++)
	{
		int vertex = 0 ,wt = 0;
		while(true)
		{
			scanf(" %d",&vertex);
			if(vertex == -1) break;
			scanf(" %d",&wt);
			graph[i] = Attach(graph[i],vertex,wt);
		}
	}
	
	/* source */
	int source = 0;
	scanf(" %d",&source);
	
	/* calculating shortest path using Dijkstras algo */
    DijkstraS(graph,source);

	/* result */
    for(int i=1; i<=n; i++)
	{
			/* if Unreachable */
			if(d[i] == 5000 ){
				printf("Unreachable\n");
			}
			else{
				printf("%d %d\n",d[i],Pred[i]);
			}
	}

	return 0;
}

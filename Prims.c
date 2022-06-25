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
    int parent;
	int value;
};
typedef struct data Data;

/* Empty Priority queue */
Data Pq[1000];

/* space to store vertex index in heap */
int IndexOfVertex[1000];
int vis[1000];

 /* inf distance */
 const int inf = 1e9;

/*current size of heap */
int LastOfPq = 0;

/*Function to swap value at two location */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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
            swap( &Pq[index].parent, &Pq[min].parent );
			
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
    if(Pq[1].parent != 0)
        printf("%d %d %d\n",Pq[1].parent,Pq[1].vertex,Pq[1].value);

	int val = Pq[1].vertex;

    /* taking last element in the 1st position and then 
    applying Minheapfy operation on it */
    swap( &IndexOfVertex[Pq[1].vertex], &IndexOfVertex[Pq[LastOfPq].vertex] );
	Pq[1].value = Pq[LastOfPq].value;
    Pq[1].vertex = Pq[LastOfPq].vertex;
    Pq[1].parent = Pq[LastOfPq].parent;
	Pq[LastOfPq].value = inf;
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
        swap( &Pq[index/2].parent, &Pq[index].parent );
        index /= 2;
    }
}

/* Decrease Key */
void DecreaseKey(int v, int NewValue,int p)
{
	Pq[ IndexOfVertex[v] ].value = NewValue;
    Pq[ IndexOfVertex[v] ].parent = p;
	ShiftUp( IndexOfVertex[v] );
}

/* Function to check heap is empty or not */
bool IsHeapEmpty()
{
    return LastOfPq >= 1;
}


/* Finding MST */
void PrimesAlgo(list* g[], int source)
{
	/* Allowing source in MST */
	DecreaseKey(source,0,0);
	
	while( IsHeapEmpty() )
	{
		/* Extracting shortest distance vertex from the heap */
		int ele = ExtractMin();

		/* Relaxing all edges of current element */
		list* ptr = g[ele];
		while( ptr != NULL )
		{
			/* (u,v) */
            if(vis[ptr->item] == -1) {
                ptr = ptr->next;
                continue;
            }
			int WeightInHeap = Pq[IndexOfVertex[ptr->item]].value;
			int CurrentWeight = ptr->weight;

            /* if for a vertex current weight is less than its 
            weight in heap then updating its weight*/
			if( CurrentWeight < WeightInHeap )
			{
				DecreaseKey( ptr->item, CurrentWeight, ele);
			}
            ptr = ptr->next;
		}

        /* marking vertex as in MST */
        vis[ele] = -1;
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
        /* Initial condition's */
		graph[i] = NULL;
    
		/* Assuming  distance from the source is infinity */
		IndexOfVertex[i] = i;
		Pq[i].vertex = i;
        Pq[i].parent = 0;
		Pq[i].value = inf;
	}
	
	/* making n size heap */
	LastOfPq = n;
	
	/* Input for given graph */
	for(int i=1; i<=n; i++)
	{
		int vertex = 0 ,wt = 0;

        list* cur = NULL;

        /* input for adjacecy list of current vertex */
		while(true)
		{
			scanf(" %d",&vertex);
			if(vertex == -1) break;
			scanf(" %d",&wt);

            /* creating node of given values */
            list* node = (list*) malloc(sizeof(list));
	        node -> item = vertex;
	        node -> weight = wt;
	        node -> next = NULL;
            
            /* if adjacency list is empty */
            if( graph[i] == NULL ){
        
                /* this node will become head of graph[i] list */
                graph[i] = node;

                cur = node;
                continue;
            }

            /* if list is not empty then adding node at last and then 
            making cur pointing to last */
            cur->next = node;
            cur=node;

		}
	}
	
	/* source */
	int source = 0;
	scanf(" %d",&source);
	
	/* calculating shortest path using PrimesAlgo algo */
    PrimesAlgo(graph,source);

	return 0;
}

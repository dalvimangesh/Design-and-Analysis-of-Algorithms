#include<stdio.h>
#include<stdbool.h>

/* structure which stores the rank and parent for vertex*/
struct Data
{
	int rank;
	int parent;
};
typedef struct Data Data;

/* creating disjoint sets for all vertex */
void MakeSet(Data* a,int n)
{
    /* each vertex is parent of itself so rank is zero*/
	for(int i=1;i<=n;i++)
	{
		a[i].parent = i;
		a[i].rank = 0;
	}
}

/* finding parent for the input and simulsimultaneously
doing path compression in recursive way*/
int Find(Data* a,int x)
{
	if (a[x].parent == x) return x;
	return a[x].parent = Find(a,a[x].parent);
}

/* Union of two sets based on their ranks of parent
lower rank will get attach to higher one */
void Union(Data* a, int x,int y)
{	
    /* parent of x and y */
	int p1 = Find(a,x);
	int p2 = Find(a,y);
	
    /* if equals means both are in same set*/
	if(p1==p2) return;
	
    /* rank of parent of x and y */
	int r1 = a[p1].rank;
	int r2 = a[p2].rank;
	
    /* same rank condition */
	if( r1==r2 )
	{
		a[p2].parent = p1;
		a[p1].rank++;
	}
	else if(r1<r2)
	{
		a[p1].parent = p2;
	}
	else
	{
		a[p2].parent = p1;
	}
	
}

/* Function to print vertex and its parent in dsu */
void PrintDSU(Data* a,int n)
{
	for(int i=1;i<=n;i++)
		printf("%d %d\n",i,Find(a,i));
}

int main()
{
    /* No of vertex */
	int n = 0; scanf(" %d",&n);
	
    /* creating disjoint sets for all vertex */
	Data dsu[n+1];
	MakeSet(dsu,n);
	
	while(true)
	{
		int q = 0;
		scanf(" %d",&q);
		
        /* query 1 ... finding parent of x */
		if(q==1)
		{
			int x = 0; scanf(" %d",&x);
			int p = Find(dsu,x);
			printf("%d\n",p);
		}

        /* query 2 ...  union of x and y */
		if(q==2)
		{
			int x = 0,y = 0; scanf(" %d %d",&x,&y);
			Union(dsu,x,y);

            /* New parent after union */
            int new_parent = Find(dsu,y);
            printf("%d %d\n",new_parent,dsu[new_parent].rank);
		}

        /* query 3 ... printing whole dsu */
		if(q==3)
		{
			PrintDSU(dsu,n);
		}

        /* query 4 ... exit */
		if(q==4)
		{
			break;
		}
	}
	return 0;
}

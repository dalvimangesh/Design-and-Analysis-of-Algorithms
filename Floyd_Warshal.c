#include<stdio.h>

/* inf distance */
const int inf =  55555;
/* distance array , each (i,j) is shortest path from i to j*/
int d[1000][1000]; 
/* predecessor array , each (i,j) is 
predecessor of j in shortest path from i to j */
int Pred[1000][1000]; 

/* Function to pritn matrix in given format */
void PrintMatrix(int matrix[1000][1000],int n,int type)
{
    for(int i=1;i<=n;i++)
    {
		for(int j=1;j<=n-1;j++)
        {
            if(matrix[i][j] == inf )
            {
                if(type == 1) printf("%d ",inf);
                if(type == 2) printf("NIL ");
            } 
            else printf("%d ",matrix[i][j]);
		}
		if(matrix[i][n] == inf ){
            if(type == 1) printf("%d\n",inf);
            if(type == 2) printf("NIL\n");
        } 
        else printf("%d\n",matrix[i][n]);
	}
}

/* All pair shortest path using DP by allowing 1 to k 
vertex and then updating dis from i to j accordingly */
void FloydWarshall(int n)
{
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				/* if by allowing 1 to k vertex if we are getting 
				shortest path from i to j then changing its value */
				if( d[i][j] > (d[i][k] + d[k][j]) )
                {
					d[i][j] = d[i][k] + d[k][j];
					Pred[i][j] = Pred[k][j];
                }
			}
		}
		
		/* result */
        if(k==2)
        {
            printf("Pairwise Distance Matrix After Two Rounds\n");
            PrintMatrix(d,n,1);
            printf("Pairwise Predecessor Matrix After Two Rounds\n");
            PrintMatrix(Pred,n,2);
        }
	}
}

int main()
{
	/* number of vertex */
	int n = 0;
    scanf(" %d",&n);
	
	/* input for graph in matrix form */
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			
			scanf(" %d",&d[i][j]);
			
			/* if there is no edge */
            if( d[i][j] == 0 )	Pred[i][j] = inf;
            
			/* if there is an edge then parent will be predecessor */
            else if( d[i][j] < inf )	Pred[i][j] = i;
            
            else	Pred[i][j] = inf;
			
		}
	}
	
	/* Finding All pair shortest path using floyd warshall */
	FloydWarshall(n);
	
	/* final result */
    printf("Final Pairwise Distance Matrix\n");
    PrintMatrix(d,n,1);
    printf("Final Pairwise Predecessor Matrix\n");
    PrintMatrix(Pred,n,2);
	
	return 0;
}

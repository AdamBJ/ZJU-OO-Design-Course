#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

#define inf INT_MAX                       /* A large enough integer is regarded as infinity */
#define arraySize (N-1)*N/2               /* There are at most (N-1)*N/2 highways linking N cities. Sum of numbers from 1 to N is N*(N+1)/2. We sum 1 to N-1, just plug in. */
#define max(x,y) (x>y?x:y)                /* Macro definition of function max */
#define min(x,y) (x<y?x:y)                /* Macro definition of function min */
#define sub1(i,j) (2*N-i)*(i-1)/2+j-i-1   /* Find the subscript of highway which connects city_i and city_j(i < j) in array W[] */
#define sub(i,j) sub1(min(i,j),max(i,j))  /* Find the subscript of highway which connects city_i and city_j in array W[] */

int N, M;                                 /* N(<=1000): the number of cities;  M: the number of highways */
int *W;                                   /* Array of weight of each highway which represents an upper triangular matrix */
int *ans, *cost, *known;                  /* Key cities are marked in ans[]; cost[] and known[] helps to find key cities */
int maxEffort;

void UpdateCost(int j)								  /* Update cost[] after city_j is linked */
{
	int i;
	for (i = 1; i <= N; i++)
		if (!known[i])								  /* If city_i is not linked */
			cost[i] = min(cost[i], W[sub(i,j)]);
}

int FindNextCity()								      /* Find next city which costs the lest effort to link */
{                                                     /* If a minimium spanning tree has been finished, it returns 0 */
	int i, t = 0;
	for (i = 1; i <= N; i++)                          /* Scan cities which haven't been linked yet */
		if (!known[i])								  /* If city_i is not linked */
			t = cost[t]>=cost[i]?i:t;                 /* If city_i costs less than city_t, replace t by i */
	return t;
}

void FindKeyCities()								  /* Find key cities (by using greedy algorithm) and mark them in ans[] */
{                                                     /* It is guaranteed that N>=2 */
	int i, j, effort;
	maxEffort = 0;
	for (i = 1; i <= N; i++)                          /* Scan all the cities to find those we must protect the most */
	{                                                 /* If city_i is conquered, find one minimum spanning tree between the remaining ...*/
		effort = 0;                                   /*   ... cities to obtain the minimum cost to rebuild the connection */
		memset(known + 1, 0, N*sizeof(int));          /* Set all the cities to be unknown(unlinked) */
		for (j = 0; j <= N; j++) cost[j] = inf;       /* Initialize cost[] */
		known[i] = 1;                                 /* This line simulates the condition that city_i has been conquered */
		j = i==1?2:1;                                 /* Select one city to begin Prim's Algorithm */
		known[j] = 1;                                 /* Declare city_j to be known as the first node in the tree */
		UpdateCost(j);
		while (j = FindNextCity())                    /* While there exists cities haven't been linked to the tree */
		{
			if (cost[j] == inf)                       /* cost[j] == inf means there's no highway connects cities which have been ... */
			{                                         /*   ...linked and the rest */ 
				effort = inf;
				break;                                /* If there's no way to keep the rest of the cities connected, break the loop */
			}
			effort += cost[j];
			known[j] = 1;                             /* Declare city_j to be known(linked) */
			UpdateCost(j);                            /* Update cost[] */
		}
		if (effort >= maxEffort)
		{
			if (effort > maxEffort)                   /* If city_i causes more effort */
				memset(ans + 1, 0, N*sizeof(int));    /* Unmark previously marked cities */
			ans[i] = 1;                               /* Mark city_i */
			maxEffort = effort;                       /* Update maxEffort */
		}
	}
}

void DisplayAns()                                     /* Output the IDs of key cities */
{
	int i, bSpace = 0;
	if (!maxEffort)                                   /* If there is no need to repair any highway at all, output 0 */
	{
		printf("0\n");
		return;
	}
	for (i = 1; i <= N; i++)
		if (ans[i])                                   /* If city_i is marked */
		{
			if (bSpace)
				printf(" ");
			printf("%d", i);
			bSpace = 1;
		}
	printf("\n");
}

int main()
{
	int i, City1, City2, Cost, Status;                /* Assume Cost is always positive. If Cost = 0, it makes no sense */
	while (scanf("%d", &N) && N)                      /* Read N and check loop termination conditions */
	{
		scanf("%d", &M);
		W = (int*)malloc(arraySize*sizeof(int));      /* Allocate memory for arrays */
		ans = (int*)malloc((N + 1)*sizeof(int));
		cost = (int*)malloc((N + 1)*sizeof(int));
		known = (int*)malloc((N + 1)*sizeof(int));
		for (i = 0; i < arraySize; i++) W[i] = inf;   /* Initialize array W */
		for (i = 0; i < M; i++)                       /* Read the information of highways and store it to array W */
		{
			scanf("%d%d%d%d", &City1, &City2, &Cost, &Status);
			if (Status)                               /* If the highway is in use */
				W[sub(City1,City2)] = 0;
			else W[sub(City1,City2)] = Cost;          /* If the highway is destroyed */
		}
		if (N == 1)
			printf("1\n");                            /* If there is only one city, city_1 will be the only key city */
		else
		{
			FindKeyCities();						  /* Find key cities */
			DisplayAns();                             /* Display key cities */
		}
		free(W);                                      /* Release arrays */
		free(ans);
		free(cost);
		free(known);
	}
	return 0;
}
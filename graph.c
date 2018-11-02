#include <stdio.h>
#include <stdlib.h>
#define MAXV 5000

#include "bool.h"
#include "queue.h" 
#include "backtrack.h"

typedef struct {
	int y;
	int weight;
	struct edgenode *next;
} edgenode;

typedef struct {
	edgenode *edges[MAXV+1];
	int degree[MAXV+1];
	int nvertices;
	int nedges;
	bool directed;
} graph;

bool processed[MAXV];	/* which vertices have been processed */
bool discovered[MAXV];	/* which vertices have been found */
int parent[MAXV];		/* discovery relation */

initialize_graph(graph *g, bool directed)
{
	int i;
	g -> nvertices = 0;
	g -> nedges = 0;
	g -> directed = directed;
	for (i=1; i<=MAXV; i++) g->degree[i] = 0;
	for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

process_vertex(int v)
{
printf("processed vertex %d",v);
}

process_edge(int x, int y)
{
}

read_graph(graph *g, bool directed)
{
	int i;
	int m;
	int x, y;
	initialize_graph(g, directed);
	scanf("%d %d",&(g->nvertices),&m);
	for (i=1; i<=m; i++){
		scanf("%d %d",&x,&y);
		insert_edge(g,x,y,directed);
	}
}

insert_edge(graph *g, int x, int y, bool directed)
{
	edgenode *p;
	p = malloc(sizeof(edgenode));
	p -> weight = NULL;
	p -> y = y;
	p -> next = g -> edges[x];
	
	g -> edges[x] = p;

	g -> degree[x] ++;

	if (directed == FALSE)
		insert_edge(g,y,x,TRUE);
	else
		g->nedges ++;
}

initialize_search(graph *g)
{
	int i;
	for (i=1; i <= g->nvertices; i++){
		processed[i] = discovered[i] = FALSE;
		parent[i] = -1;
	}
}

bfs(graph *g, int start)
{
	queue q;
	int v;
	int y;
	edgenode *p;
	init_queue(&q);
	enqueue(&q,start);
	discovered[start] = TRUE;
	while (empty(&q) == FALSE){
		v = dequeue(&q);
		printf("%d ", v);
		processed[v] = TRUE;
		p = g->edges[v];
		while (p != NULL) {
			y = p->y;
			if ((processed[y] == FALSE)|| g -> directed)
				process_edge(v,y);
			if (discovered[y] == FALSE){
				enqueue(&q,y);
				discovered[y] = TRUE;
				parent[y] = v;
			}
			p = p->next;
		}
	}
}

bool finished = FALSE;			/* found all solutions yet? */
int max_dist;
int s[NMAX+1];

process_solution(int a[], int k, graph *g)
{
	int i;
	int b[NMAX+1];
	for (i=1; i<=k; i++) {
		 b[a[i]] = i;
	}
	int j;
	for (j=1; j<=k; j++) {
		int v = a[j];
		edgenode *curr_edges = g->edges[v];
		int len = g->degree[v];
		int v_max_dist = -1;
		while (curr_edges != NULL){
			if (abs(j - b[curr_edges->y]) > v_max_dist) {
				v_max_dist = abs(j-b[curr_edges->y]);
			} 
			curr_edges = curr_edges->next;
		}
		if (max_dist > v_max_dist) {
			max_dist = v_max_dist;
			memcpy(s,a,sizeof(s));
		}
		
	}
}

is_a_solution(int a[], int k, int n)
{
	return (k == n);
}

construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
	int i;				/* counter */
	bool in_perm[NMAX];		/* what is now in the permutation? */

	for (i=1; i<NMAX; i++) in_perm[i] = FALSE;
	for (i=1; i<k; i++) in_perm[ a[i] ] = TRUE;

	*ncandidates = 0;
	for (i=1; i<=n; i++) 
		if (in_perm[i] == FALSE) {
			c[ *ncandidates] = i;
			*ncandidates = *ncandidates + 1;
		}
}

backtrack(int a[], int k, graph *g)
{
        int c[MAXCANDIDATES];           /* candidates for next position */
        int ncandidates;                /* next position candidate count */
        int i;                          /* counter */
	int v = g->nvertices;
        if (is_a_solution(a,k,v))
                process_solution(a,k,g);
        else {
                k = k+1;
                construct_candidates(a,k,v,c,&ncandidates);
                for (i=0; i<ncandidates; i++) {
                        a[k] = c[i];
                        backtrack(a,k,g);
                        if (finished) return;   /* terminate early */
                }
        }
}

main() 
{

	graph g;
	read_graph(&g,FALSE);
	int a[NMAX+1];
	backtrack(a,0,&g);	
	
}

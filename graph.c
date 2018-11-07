#include <stdio.h>
#include <stdlib.h>
#define MAXV 5000

#include "bool.h"
#include "backtrack.h"

typedef struct {
	int x;
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
	int max_degree;
	int min_pos_bandwidth;
} graph;

bool processed[MAXV];	/* which vertices have been processed */
bool discovered[MAXV];	/* which vertices have been found */
int parent[MAXV];		/* discovery relation */

initialize_graph(graph *g, bool directed)
{
	int i;
	g -> nvertices = 0;
	g -> nedges = 0;
	g -> max_degree = 0;
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
	int j;
	int m;
	int x, y;
	initialize_graph(g, directed);
	scanf("%d",&(g->nvertices));
	scanf("%d",&m);
	for (i=1; i<=m; i++){
		scanf("%d %d",&x,&y);
		insert_edge(g,x,y,directed);
	}
	for (j = 1; j <= g->nvertices; j++){
		if (g->max_degree < g->degree[j]){
			g->max_degree = g->degree[j];
		}
	}
	g -> min_pos_bandwidth = (g -> max_degree + 1)/2;
}

insert_edge(graph *g, int x, int y, bool directed)
{
	edgenode *p;
	p = malloc(sizeof(edgenode));
	p -> weight = NULL;
	p -> x = x;
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

bool finished = FALSE;			/* found all solutions yet? */
int max_dist = 50000;
int s[NMAX+1];
int nvertices_;
int nvertices__;

process_solution(int a[], int k, graph *g)
{
	if (finished) return;
	int i;
	int b[nvertices__];
	for (i=1; i<=k; i++) b[a[i]] = i;
	int j;
	int v_max_dist = -1;
	for (j=1; j<=k; j++) {
		edgenode *curr_edges = g->edges[a[j]];	
		while (curr_edges != NULL){ 
			if (abs(j - b[curr_edges->y] > v_max_dist)) {
				v_max_dist = abs(j - b[curr_edges->y]);
				if (g->nvertices/2 <= v_max_dist || max_dist <= v_max_dist){
					goto skip;
				}
			} 
			curr_edges = curr_edges->next;
		}	
	}
	if (v_max_dist <= g->min_pos_bandwidth) {
		finished = TRUE;
	}
	if (max_dist > v_max_dist) {
		max_dist = v_max_dist;
		memcpy(s,a,sizeof(s));
	}
	skip: ;
}

is_a_solution(int a[], int k, int n)
{
	return (k == n);
}

construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
	if (finished) return;
	int i;
	bool in_perm[nvertices__];

	for (i=1; i<nvertices__; i++) in_perm[i] = FALSE;
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
        int c[nvertices_];           /* candidates for next position */
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
	int a[g.nvertices+1];
	nvertices_ = g.nvertices;
	nvertices__ = nvertices_ + 1;
	backtrack(a,0,&g);	
	printf("Minimum Bandwidth: %d\n", max_dist);
	int c;
	for (c = 1; c <= nvertices_; c++) {
		printf("%d ", s[c]);
	}	
}

#include <stdio.h>
#include <stdlib.h>
#define MAXV 5000

#include "bool.h"
#include "queue.h" 

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

connected_components(graph *g)
{
	int c;
	int i;
	initialize_search(g);
	c = 0;
	for (i=1; i<=g->nvertices; i++)
		if (discovered[i] == FALSE){
			c = c+1;
			printf("Component %d: ",c);
			bfs(g,i);
			printf("\n");
		}
}

main() 
{

	graph g;
	read_graph(&g,FALSE);
	connected_components(&g);

}

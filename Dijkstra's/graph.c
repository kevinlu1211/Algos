#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "heap.h"
#include "set.h"

/*
** Create graph with number_of_vertices vertices
*/
Graph *
graph_new(int number_of_vertices) {
    assert(number_of_vertices > 0);
    Graph *g = (Graph *)malloc(sizeof(Graph));
    assert(g);
    g->number_of_houses = NULL;
    g->number_of_school_sites = NULL;
    g->number_of_vertices = number_of_vertices;
    g->vertices = (Vertex *)malloc(sizeof(Vertex) * number_of_vertices);
    assert(g->vertices);
	
    for(int i = 0 ; i < number_of_vertices ; i++) {
        g->vertices[i].data  = NULL;
        g->vertices[i].label = i;
        g->vertices[i].edges = NULL;
        g->vertices[i].num_edges = 0;
        g->vertices[i].max_num_edges = 0;
    }
        
    return(g);
}

/*
** Add edge to g. 
*/
void  
graph_add_edge(Graph *g, Label v, Label u, Dist d) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    // printf("Number of vertices: %d\nLabel: %d", g->number_of_vertices, u);	
    assert(u >= 0 && u < g->number_of_vertices);

        // Make room if no room.
    if (g->vertices[v].num_edges == g->vertices[v].max_num_edges) {
        if (g->vertices[v].max_num_edges == 0)
            g->vertices[v].max_num_edges = 1;
        else
            g->vertices[v].max_num_edges *= 2;
        g->vertices[v].edges = (Edge *)realloc(g->vertices[v].edges, sizeof(Edge) * g->vertices[v].max_num_edges);
        assert(g->vertices[v].edges);
    }
	// Deference g then access element v of array of vertices
	//			   then access element num_edges of array of edges for accessed vertex v
	// 		       then access field u (which is the end of the edge) and set it to u
    g->vertices[v].edges[g->vertices[v].num_edges].label = u;
    
    g->vertices[v].edges[g->vertices[v].num_edges].dist = d;

    g->vertices[v].num_edges += 1;
}

// Updates the graph with information taken from stdin
Graph *graph_create() {
	int num_of_houses; int num_of_school_sites; int num_of_vertices;
	Label vertex_v	 ; Label vertex_u         ; int dist           ;
    Graph *g;
	scanf("%d", &num_of_houses);
	scanf("%d", &num_of_school_sites);
	num_of_vertices = num_of_houses + num_of_school_sites;
	g = graph_new(num_of_vertices);
	g -> number_of_houses = num_of_houses;
	g -> number_of_school_sites = num_of_school_sites;
	while (scanf("%d %d %d", &vertex_v, &vertex_u, &dist)==3) {
		graph_add_edge(g, vertex_v, vertex_u, dist);
		graph_add_edge(g, vertex_u, vertex_v, dist);
	}
	return g;
}

// Prints the graph for debugging
void graph_print(Graph *g) {
	int i, j;
	for (i = 0; i < g->number_of_vertices; i++) {
		printf("Label is: %d\n", g->vertices[i].label);
		printf("Number of Edges: %d\n", g->vertices[i].num_edges);
		
		for (j = 0; j < g->vertices[i].num_edges; j++) {
			
			printf("Edge label connected: %d, Distance: %f meters\n", 
			        g->vertices[i].edges[j].label, g->vertices[i].edges[j].dist);
		}		
	}
}


/*
Exploring the graph to see if all the nodes are connected
*/

int 
graph_default_explore(Graph *g, Label v) {
    int connected_vertices = 1;
    
    //base case
    if (g->vertices[v].data)
        return 0;

    g->vertices[v].data = (void *)1; // mark as visited

    for(int i = 0 ; i < g->vertices[v].num_edges ; i++)
        connected_vertices += graph_default_explore(g, g->vertices[v].edges[i].label);
        
    return connected_vertices;
}

// Dijkstra's algorithm to find the shortest path
Set *dijkstra(Graph *g, Label src) {
	// src is the potential school site node
	Set *s = create_set();
	Heap *h = create_heap();
	Label u; Label v; Dist dist_u_v; Dist dist_src_v; Dist dist_src_u_v; 
	Label school_site_id = src;
	
	// Initializing heap priority queue
	for (int i = 0; i < g->number_of_vertices; i++) {
		if(insert_heap(h, i, MAX_DIST)==HEAP_SUCCESS) {	
		}
		else {
			fprintf(stderr, "Failed to insert into heap");
		}
	}	
	
	// Update school_site dist to 0;
	change_key(h, school_site_id, 0);

	// While the heap is not empty
	while (h->n != 0) {
		// Remove the minimum of the heap
		u = remove_min(h);
		
		// Checking for early termination
		if (h->H[h->map[u]].dist > MAX_RADIUS) {
			return s;
		}
		
		// Enter the vertex with least distance to the set
		enter_at_foot(s, u);
		
		// Finding vertex id and distances connected to deleted vertex
		for (int j = 0; j < g->vertices[u].num_edges; j++) {
			// print_heap(h);
			v = g->vertices[u].edges[j].label;
			dist_u_v = g->vertices[u].edges[j].dist;
			dist_src_v = h->H[h->map[v]].dist; 
			dist_src_u_v = h->H[h->map[u]].dist + dist_u_v;
			if (dist_src_v > dist_src_u_v) {
				change_key(h, v, dist_src_u_v);	 
			}
		}
	}
	destroyHeap(h);
	return s;
}
/* All taken from Tutor Champake*/

typedef int Label;   // a vertex label (should be numeric to index edge lists)
typedef float Dist;	 // a distance between edges

typedef struct {
    Dist  dist;   // any data you want to store about an edge
    Label label;        // end vertex of edge
} Edge;

typedef struct {
    void   *data;        		// any data you want to store about a vertex
    Label  label;        		// this vertex's label
    Edge  *edges;        		// array of edges [0..num_edges-1]
    int   num_edges;    		// number of edges
    int   max_num_edges;		// current malloced size of edges array, num_edges <= max_num_edges
} Vertex;

typedef struct {
    int    number_of_houses;
    int    number_of_school_sites;              // any data you want to store about a graph
    int    number_of_vertices; // |V|
    Vertex *vertices;          // array of vertices [0..number_of_vertices-1]
} Graph;

// Prototype Functions
Graph *graph_new(int number_of_vertices);
void  graph_add_edge(Graph *g, Label v, Label u, Dist d);
void  graph_print(Graph *g);
Graph *graph_create();
void  graph_set_vertex_data(Graph *g, Label v, int data);
int graph_default_explore(Graph *g, Label v);
void graph_dfs(Graph *g, Label v, void (explore)(Graph *g, Label v));



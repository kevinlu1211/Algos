typedef int Label;   // a vertex label (should be numeric to index edge lists)
typedef struct node Set_node;

// The node for the set which is a linked list data structure
struct node {
	Label	  label;
	Set_node  *next;
};

// The set itself
typedef struct {
	Set_node *head;
	Set_node *foot;
	int number_of_nodes;
} Set;

// An array of sets
typedef struct {
	Set **sets;
	int number_of_sets;
} All_Sets;


// Prototype Functions
Set *create_set();
Set *create_house(Graph *g);	
All_Sets *create_all_sets(Graph *g);
void set_free(Set *list);
Set *delete_element(Set *list, Label element);
Set *dijkstra(Graph *g, Label src); 
Set *enter_at_foot(Set *s, Label label);
void print_set(Set *s);
void print_all_sets(Graph *g, All_Sets *all_sets); 
int *set_cover(All_Sets *all_sets, Set *h, int *num_of_schools);
Set* set_intersect(Set *s, Set *h);
Set* set_delete(Set *s, Set *h);
int is_in_set(Set *s, int data);
/* Written by Kevin Lu 695824 */
/* Assignment 2 */
#include "graph.h"
#include "heap.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	// Creating variables needed to create set cover
  	All_Sets *all_sets; 
  	Graph *g = graph_create();
  	Set *h; 
  	int *schools; int number_of_schools;
  	
    // Checking for graph connectivity
    if (g->number_of_vertices != graph_default_explore(g, 0)) {
    	fprintf(stderr, "Graph not connected");
    }
    else {
    	// Creating all possible sets
    	all_sets = create_all_sets(g);
    	
    	// Creating set of all houses
    	h = create_house(g);
    	
    	
    	// Finding school sites
		schools = set_cover(all_sets, h, &number_of_schools); 
		
		// Printing school site vertices
		for (int i = 0; i < number_of_schools; i++) {
			printf("%d\n", schools[i]-g->number_of_houses);
		}
		
    }
    return 0;
}
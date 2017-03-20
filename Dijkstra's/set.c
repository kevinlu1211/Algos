#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#include "set.h"
#include "heap.h"

// Creates a empty set
Set *create_set() {
    Set *s = (Set *)malloc(sizeof(Set));
    assert(s);
    s->head = s->foot = NULL;
    return s;
}

// Creates the set of all houses
Set *create_house(Graph *g) {
	Set *h = create_set();
	for (int i = 0; i < g->number_of_houses; i++) {
		enter_at_foot(h, i);
	}
	return h;
}

// Creates an array with each element being one of all the houses within 1000 meters
// from a potential school site
All_Sets *create_all_sets(Graph *g) {
	All_Sets *all_sets;
	all_sets = (All_Sets*)malloc(sizeof(All_Sets*));
	all_sets->number_of_sets = 0;
	all_sets->sets = (Set **)malloc(sizeof(Set *) * g->number_of_school_sites);
	
	int array_index = 0;
	
	// Using dijkstra's algorthim to find shortest path from potential school site 
	// where index i is the label of the potential school site
	// and then returning the set of houses that are within 1000 meters
	for (int i = g->number_of_houses; i < g->number_of_vertices; i++) {
		all_sets -> sets[array_index++] = dijkstra(g, i);
	}
	all_sets->number_of_sets = array_index;
	return all_sets;
}

// Frees a set
void set_free(Set *list) {
    Set_node *curr, *prev;
    assert(list!=NULL);
    curr = list->head;
    while (curr) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(list);
}

	// Deletes an element from a set
Set *delete_element(Set *list, Label element) {
    assert(list);

    Set_node *curr = list->head, *prev = list->head;
    while (curr != NULL && curr->label != element) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
        return list;

    if (curr == list->head) {
        if (list->foot == list->head)
            list->foot = curr->next;
        list->head = curr->next;
    } else {
        prev->next = curr->next;
        if (list->foot == curr)
            list->foot = curr->next;
    }
    free(curr);

    return(list);
}

// Appends an item onto the end of the linked list
Set *enter_at_foot(Set *s, Label label) {
	Set_node *new_node;
    new_node = (Set_node*)malloc(sizeof(new_node));
    assert(s!=NULL && new_node!=NULL);
    new_node->label = label;
    new_node->next = NULL;
    if (s->foot==NULL) {
        /* this is the first insertion into the list */
        s->head = s->foot = new_node;
    } 
    else {
        s->foot->next = new_node;
        s->foot = new_node;
    }
    return s;
}

// Prints the a set
void print_set(Set *s) {
	Set_node *temp = s->head;
	while(temp != NULL) {
		printf("Label: %d\n", temp->label);
		temp = temp->next;
	} 
	
}

// Prints all sets of houses with potential school sites
void print_all_sets(Graph *g, All_Sets *all_sets) {
	for (int i = 0; i < all_sets->number_of_sets; i++) {
		printf("Set head: %d\n", i + g->number_of_houses);
		print_set(all_sets->sets[i]);
	}
}

// Minimum Set Cover Greedy Algorithm
int *set_cover(All_Sets *all_sets, Set *h, int *num_of_schools) {
	// all_sets is a pointer to an array of sets
	// h is the set of all houses
	// num_of_schools is the number of school sites (needed to iterate through array)
	int *schools = (int *)malloc(sizeof(schools));
	assert(schools);
	int school_n = 0;
	int school_size = 1;
	int loop_count = 0;
	Set *s_intersect_h; 
	int number_of_sets = all_sets->number_of_sets;
	
	// while the set of houses is not empty
	while (h->head != NULL){
		if (loop_count == number_of_sets){
			// in the case that there are houses that can't be reached by any of the
			// school sites
			*num_of_schools = school_n;
			set_free(h);
			return schools;
		}
		
		int max_intersect = 0;
		int set_index = 0;
		
		// Iterating through all the created sets and finding set with maximum
		// number of elements that intersect with the set of houses
		for (int i = 0; i < number_of_sets; i++){
			s_intersect_h = set_intersect(all_sets->sets[i], h);
			
			// Checks if |s_intersect_h| is greater than previous ones if it is then update
			if (s_intersect_h->number_of_nodes > max_intersect){
				max_intersect = s_intersect_h->number_of_nodes;
				set_index = i;
			}
			set_free(s_intersect_h);
		}
		//remove delete elements from the set of houses that intersected with the chosen set
		h = set_delete(all_sets->sets[set_index], h);
		
		// checking to see if the schools array needs to be enlarged
		if (school_n >= school_size){
			school_size *= 2;
			schools = (int *)realloc(schools, sizeof(schools) * school_size);
		}
		// checking if there are duplicate school sites
		int in_schools = 0;
		for (int j=0; j<school_n; j++) {
			if (all_sets->sets[set_index]->head->label == schools[j]) {
				in_schools = 1;
			}
		}
		if (in_schools == 0) {
			schools[school_n++] = all_sets->sets[set_index]->head->label;
		}
		loop_count++;
	}
	// updating num_of_schools to the length of the array for iteration
	*num_of_schools = school_n; 
	set_free(h);
	return schools;
}

// Checking if an element is in the set
int
is_in_set(Set *s, int data) {
	Set_node *temp = s->head;
	while (temp != NULL) {
		if (temp->label == data) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

// Returns a set of all the intersected elements 
Set* set_intersect(Set *s, Set *h) {
	// Where s is one of the sets from a school
	//		 h is the set of all houses
	Set_node *temp = h->head;
	Set* temp_set = create_set();
	temp_set->number_of_nodes = 0;
	while(temp != NULL) {
		if(is_in_set(s, temp->label)) {
			enter_at_foot(temp_set, temp->label);
			temp_set->number_of_nodes++;
		}
		temp = temp->next;
	}	
	return temp_set;
}

// Returns the updated set of the set of all houses
Set* set_delete(Set *s, Set *h) {
	// Where s is one of the sets from a school
	//		 h is the set of all houses
	
	Set_node *temp = s->head;
	while(temp != NULL) {
		if(is_in_set(h, temp->label)) {
			delete_element(h, temp->label);
		}
		temp = temp->next;
	}	
	return h;
}


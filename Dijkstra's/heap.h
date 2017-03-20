/* All taken from Tutor Champake*/
typedef unsigned int uint;
typedef int Label;   // a vertex label (should be numeric to index edge lists)
typedef float Dist;	 // a distance between edges

typedef struct item {
    Dist  dist;		 // the key for deciding position in heap
    uint  dataIndex; // the payload index provided by the calling program
} HeapItem;

typedef struct heap {
    HeapItem *H;     // the underlying array
    uint   *map;   // map[i] is index into H of location of payload with dataIndex == i
    uint    n;     // the number of items currently in the heap
    uint    size;  // the maximum number of items allowed in the heap
} Heap;

#define HEAP_SUCCESS 1
#define HEAP_FAIL    0
#define MAX_DIST 2147483647
#define MAX_RADIUS 1000

Heap *create_heap(void);                               // returns a pointer to a new, empty heap
int insert_heap(Heap *h, uint dataIndex, Dist dist);     // inserts dataIndex into h
uint peek(Heap *h);                                 // returns the data index of the root.
uint peekKey(Heap *h);                              // returns the key of the root.
uint remove_min(Heap *h);                            // removes the root, returns the data index to it, and re-heapifies 
void change_key(Heap *h, uint dataIndex, Dist dist); // adds delta to the key of dataIndex
void destroyHeap(Heap *h);                            // free any memory you might of alloced in heap creation
void print_heap(Heap *h);

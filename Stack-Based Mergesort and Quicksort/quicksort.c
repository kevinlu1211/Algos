/*
**
*/
#include <stdio.h>
#include <stdlib.h>
#include "partition.h"
#include "stack.h"

void myQuicksort(void **A, int n, int(cmp)(void *, void*)) {
    /* This is the iterative function call for quicksort that 
     * uses a stack to mimic a recursive quicksort */
    
    Stack *s;
    s = stack_new();
    
    /* Creating the variables that are needed to create the initial stack */
    n = (long)n;
    long l = 0;
    long h = n-1;
    
    /* Pushing initial indexes onto the stack */
    stack_push(s, (void *)l);
    stack_push(s, (void *)h);
    
    while (stack_isEmpty(s)==0) {
        
        /* Popping off the indexes needed to define the subarray */
        h = (long)stack_pop(s);
        l = (long)stack_pop(s);
        n = h - l + 1;
        
        /* Taking pivot as last element in subarray */
        void *pivot = A[h];

        long p = partition(A+l, n, pivot, cmp) + l;
        
        /* If there are still values left of the index of the partition
         * then that means that there is another subarray that is needed
         * to be sorted hence put the values of the index of the subarray onto
         * the stack */
        if ((p - 1) > l) {          
            stack_push(s, (void *)l);
            stack_push(s, (void *)(p-1));
            
        }
        /* Same logic as above except for values right of the index of the 
         * partition */
        if ((p + 1) < h ) {
            stack_push(s, (void *)(p+1));
            stack_push(s, (void *)h);
        }
    }
    
    free_stack(s);
    
    return;
}


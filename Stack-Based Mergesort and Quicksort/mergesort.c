/*
**
*/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* merge function taken from: http://geeksquiz.com/merge-sort/ */
void merge(void **A, int l, int m, int h, int(cmp)(void *, void *)) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  h - m;
 
    /* create temp arrays */
    long L[n1]; 
    long R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for(i = 0; i < n1; i++)
        L[i] = (long)A[l + i];
    for(j = 0; j < n2; j++)
        R[j] = (long)A[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (cmp((void *)L[i],(void *)R[j]) <= 0)
        {
            A[k] = (void *)L[i];
            i++;
        }
        else
        {
            A[k] = (void *)R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        A[k] = (void *)L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        A[k] = (void *)R[j];
        j++;
        k++;
    }
}


void myMergesort(void **A, int n, int(cmp)(void *, void*)) {
    Stack *s;
    s = stack_new();
    long start, mid, end;
    long stack_state;
    
    /* Creating the variables that are needed check whether the subarrays are fit for merging */
    long state_split = 1;
    long state_merge = 0;
    long len = n - 1;
    
    /* Considering the case where the input is one element */
    if (n < 2) {
        return;
    }
    
    /* Pushing the information needed onto the initial stack */
    stack_push(s, (void *)state_split);
    stack_push(s, (void *)(len));
    stack_push(s, (void *)0);

    while (stack_isEmpty(s) == 0) {
        
        /* Popping the stack to get the information that is needed */
        start = (long)stack_pop(s);
        end = (long)stack_pop(s);
        stack_state = (long)stack_pop(s);
        mid = (start+end)/2;
        
        
        if(stack_state == state_split) {
            
            /* This if statement checks if the subarrays have been split to one element arrays
             * if not it mimics the recursive calls made in a recursive version of mergesort*/
            
            if((end - start) > 1) {
                /* These 3 stack push statements mimic the merge function that is called at the 
                 * end of the mergesort function (note that as it is a stack since the merge 
                 * function is last in the recursive mergesort function, it should be pushed on
                 * first in a stack due to LIFO*/
                stack_push(s, (void *)state_merge);
                stack_push(s, (void *)end);
                stack_push(s, (void *)start);
                
                /* These 3 stack push statements mimic the mergesort function that divides the
                 * array into 2 sub arrays */
                stack_push(s, (void *)state_split);
                stack_push(s, (void *)end);
                stack_push(s, (void *)(mid + 1));
                
                /* Same explaination as above */
                stack_push(s, (void *)state_split);
                stack_push(s, (void *)mid);
                stack_push(s, (void *)start);
                
                
            }
            /* This is the case where both are one element arrays and therefore should be sorted */
            else if((end - start) == 1) {
                merge(A, start, mid, end, cmp);
            }
            else {
            }
        }
        /* This is the case where we are finished merging one element arrays and are merging arrays that
         * have more than one element */
        else {
            merge(A, start, mid, end, cmp);
        }
    }
    free_stack(s);
}

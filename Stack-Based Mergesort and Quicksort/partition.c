#include "stack.h"
#include <stdio.h>
#include <string.h>

void swap (void *a, void *b, size_t size) {
    /* Due to the inputs being void pointers of unknown size (even though we
     * that is of type long) the memcpy function is used to swap the positions
     * of the index 
     */
    char temp[size];
    memcpy(temp, b,    size);
    memcpy(b,    a,    size);
    memcpy(a,    temp, size);
}

int partition(void **A, int n, void *pivot, int (cmp)(void *, void *)) {
    /* This is a standard partition function that switches the elements in
     * the array that have a lower value than the pivot with the next greatest
     * value in the array (subarray) to be sorted*/
    int i;
    int greaterIndex = -1;
    for (i = 0; i < n-1 ; i++) {
        if  ((cmp(A[i], pivot) < 0) || (cmp(A[i], pivot) == 0)) {
            greaterIndex++;
            swap(&A[greaterIndex], &A[i], sizeof(long));
        }
    }
    swap(&A[++greaterIndex], &A[n-1], sizeof(long));
    return (greaterIndex);
}

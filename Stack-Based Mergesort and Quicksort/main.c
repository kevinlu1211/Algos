/*
** COMP20007 Design of Algorithms
** Semester 1 2015
** Assignment 1 driver
**
** Andrew Turpin (aturpin@unimelb.edu.au)
** Thu 26 Feb 2015 11:04:32 AEDT
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "quicksort.h"
#include "mergesort.h"

#define MAX_NUMBER_STRING_LEN 64  /* maximum length in chars of number */

/*
** Print usage message
*/
void
usage(char *exeName) { 
    fprintf(stderr,"Usage: %s [q | m] < filename\n",exeName);
    fprintf(stderr,"       where\n");
    fprintf(stderr,"          q - Quicksort\n");
    fprintf(stderr,"          m - Mergesort\n");
    fprintf(stderr,"          filename - file name of text file of numbers, one per line\n");
}

/*
** Comparison function that interprets void * as int
*/
int
cmpLong(void *a, void *b) {
    long aa = (long)a;
    long bb = (long)b;
    return aa - bb;
}


/*
** Read input, call getKth, print time
*/
int 
main(int argc, char *argv[]) {
    
    if (argc != 2) {
        usage(argv[0]);
        return(-1);
    }
    
    
    char method = argv[1][0];

    /*
    ** Read in the numbers, and keep increasing the array size
    ** if necessary.
    */
    int maxArraySize = 64;  /* any number > 0 */
    int n  = 0;
    void **A = (void **)malloc(sizeof(void *) * maxArraySize);
    assert(A);
    char buff[MAX_NUMBER_STRING_LEN];
    
    while (fgets(buff, MAX_NUMBER_STRING_LEN, stdin) != NULL) {
        if (n >= maxArraySize) {
            maxArraySize *= 2;  /* double the size of the array */
            A = (void **)realloc(A, sizeof(void *) * maxArraySize);
            assert(A);
        }
       
        long temp;
        sscanf(buff, "%ld", &temp);
        A[n++] = (void *)temp;
    }
    
    
    if (method == 'q') {
        
        clock_t startTime = clock();
        
        myQuicksort(A, n, cmpLong);
        
        clock_t endTime = clock();
        fprintf(stderr,"Quicksort %10d elements %ldms\n", n, (endTime-startTime+500)/1000);
    } else {
        clock_t startTime = clock();
        myMergesort(A, n, cmpLong);
        clock_t endTime = clock();
        fprintf(stderr,"Mergesort %10d elements %ldms\n", n, (endTime-startTime+500)/1000);
    }
    
        // output array to check correctness
    
    for(int i = 0 ; i < n ; i++) {
        printf("%ld\n",(long)A[i]);
    }
    

    free(A);
    return 0;
}

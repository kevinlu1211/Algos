#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"stack.h"


Stack *stack_new() {
    /* This function creates the stack */
    Stack *s;
    s = (Stack*)malloc(sizeof(Stack));
    assert(s!=NULL);
    s->A = (void**)malloc(sizeof(void*) * INITIAL_ARRAY_SIZE);
    assert(s->A!=NULL);
    s->size = INITIAL_ARRAY_SIZE;
    
    /* Setting top to -1 because if it started at 0 it would be an hassle as 
     * it wouldn't be the same as the index value of stack array */
    s->top = -1;
    return s;
}

void   stack_push(Stack *s, void *item) {
    // push item onto stack s
    
    if (s->size == s->top+1) {
        s->size *= 2;
        s->A = (void **)realloc(s->A, sizeof(void *) * s->size);
        assert(s->A!=NULL);
    }
    s->A[++s->top] = item;
    return;
}
void  *stack_pop(Stack *s) {
    // pop item from stack s
    return s->A[s->top--];
}   
int    stack_isEmpty(Stack *s) {
    // return 1 if stack s is empty, else 0
    if (s->top <= -1) {
        return 1;
    }
    else {
        return 0; 
    }
    return 0;
}    
void   free_stack(Stack *s) {
    free(s->A);
    free(s);
    s = NULL;
}
void   stack_print(Stack *s, void(printfn)(void *)) {
    // prints whole stack
    int i;
    for (i=0; i<s->top; i++) {
        printfn(s->A[i]);
    }
    return;
}


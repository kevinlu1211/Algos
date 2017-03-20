/*
** Stack implementation interface
**
** Andrew Turpin
** Tue 24 Feb 2015 19:13:11 AEDT
*/
#define INITIAL_ARRAY_SIZE 1

typedef struct {
    void **A;   // the allocated array of void * pointers, [0..size-1]
    int size;   // the size of A
    int top;    // the index of the current top of the stack
} Stack;

Stack *stack_new();                      // create a new, empty stack
void   stack_push(Stack *s, void *item); // push item onto stack s
void  *stack_pop(Stack *s);              // pop item from stack s
int    stack_isEmpty(Stack *s);          // return 1 if stack s is empty, else 0
void   stack_print(Stack *s, void(printFn)(void *)); // print whole stack
void   free_stack(Stack *s);

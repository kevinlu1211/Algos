/*
** Header for COMP20007 Assignment 1
**
** Andrew Turpin
** Thu 26 Feb 2015 11:08:14 AEDT
*/
void myMergesort(void **A, int n, int(cmp)(void *, void*));
void merge(void **A, int l, int m, int h, int(cmp)(void *, void *));

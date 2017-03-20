#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *f = fopen("1000k.txt", "w");
    int i;
    int random;
    for (i = 0; i < 1000000; i++) {
        
        fprintf(f, rand());
    }
    fclose(f);
    return 0;
}
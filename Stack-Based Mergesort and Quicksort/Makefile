# Makefile 
# Kevin Lu
# March 2015

OBJ     = main.o stack.o partition.o quicksort.o mergesort.o
CC      = g++
EXE     = sort
CFLAGS  = -Wall

assn1:   $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE) 

main.o: partition.h quicksort.h mergesort.h Makefile
partition.o: partition.h 
quicksort.o: quicksort.h stack.h partition.h
mergesort.o: mergesort.h stack.h
stack.o: stack.h 

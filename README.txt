In the Algorithms folder:

The Dijkstra’s folder implements a greedy set approach to find all houses within 1000 meters of a school node. The set uses a heap priority queue as the data structure for the distance between nodes for efficiency.

1st input:
Number of houses

2nd input:
Number of school sites

3rd input onwards:
Vertex 1 Vertex 2 distance between (all integers)

Output: 
A greedy approach to finding school sites so that all houses are within 1000 meters

There is a test.txt file that has sample inputs for the algorithm although it may take ~20 seconds to run as the graph is quite large with around 2000 school sites meaning that 2000 sets will be created for the greedy implementation of set cover

The program has already been complied so on the command line:

./dijkstra < test.txt 

should run assuming you are using a Linux shell

=====================================================================================

The Stack-Based Mergesort and Quicksort quite self explanatory I have already complied it for you and can be on the command line via: 

For quick sort:
./sort q < 1m.txt > output.txt 

For merge sort
./sort m < 1m.txt > output.txt 


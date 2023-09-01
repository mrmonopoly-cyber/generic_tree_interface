warning= -Wall -Wextra
optimization= -O0

.PHONY: all

all: test_bst test_bst.o tree_operations.o bst.o 

test_bst : test_bst.o bst.o tree_operations.o 
	gcc $(optimization) $(warning) -g test_bst.o bst.o tree_operations.o -o test_bst

test_bst.o : test_bst.c bst.h 
	gcc $(optimization) $(warning) -g -c test_bst.c

bst.o : bst.h tree_operations.h bst.c
	gcc $(optimization) $(warning) -g -c bst.c  

tree_operations.o : tree_operations.h tree_operations.c
	gcc $(optimization) $(warning) -g -c tree_operations.c 

clean:
	rm test_bst test_bst.o bst.o tree_operations.o 

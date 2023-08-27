warning= -Wall -Wextra
optimization= -O2

.PHONY: all

all: test_btree test_btree.o tree_operations.o btree.o 

test_btree : test_btree.o btree.o tree_operations.o 
	gcc $(optimization) $(warning) -g test_btree.o btree.o tree_operations.o -o test_btree

test_btree.o : test_btree.c btree.h 
	gcc -c $(optimization) $(warning) -c test_btree.c

btree.o : btree.h tree_operations.h btree.c
	gcc $(optimization) $(warning) -c btree.c  

tree_operations.o : tree_operations.h tree_operations.c
	gcc $(optimization) $(warning) -c tree_operations.c 

clean:
	rm test_btree test_btree.o btree.o tree_operations.o 

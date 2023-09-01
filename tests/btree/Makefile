warning= -Wall -Wextra
optimization= -O0

.PHONY: all

all: test_btree test_btree.o tree_operations.o btree.o 

test_btree : test_btree.o btree.o tree_operations.o 
	gcc $(optimization) $(warning) -g test_btree.o btree.o tree_operations.o -o test_btree

test_btree.o : test_btree.c btree.h 
	gcc $(optimization) $(warning) -g -c test_btree.c

btree.o : btree.h tree_operations.h btree.c
	gcc $(optimization) $(warning) -g -c btree.c  

tree_operations.o : tree_operations.h tree_operations.c
	gcc $(optimization) $(warning) -g -c tree_operations.c 

clean:
	rm test_btree test_btree.o btree.o tree_operations.o 

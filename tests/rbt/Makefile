warning= -Wall -Wextra
optimization= -O2

.PHONY: all

all: test_rbt test_rbt.o tree_operations.o rbt.o 

test_rbt : test_rbt.o rbt.o tree_operations.o 
	gcc $(optimization) $(warning) -g test_rbt.o rbt.o tree_operations.o -o test_rbt

test_rbt.o : test_rbt.c rbt.h 
	gcc -c $(optimization) $(warning) -c test_rbt.c

rbt.o : rbt.h tree_operations.h rbt.c
	gcc $(optimization) $(warning) -c rbt.c  

tree_operations.o : tree_operations.h tree_operations.c
	gcc $(optimization) $(warning) -c tree_operations.c 

clean:
	rm test_rbt test_rbt.o rbt.o tree_operations.o 

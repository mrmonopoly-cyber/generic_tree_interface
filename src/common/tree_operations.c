#include <stdlib.h>

#include "tree_operations.h"
//private

//functions
static void swap_keys(void **node1,void **node2)
{
  char *c1 = *(char **) node1;
  char *c2 = *(char **) node2;
  char *tc = c1;
  *node1 = c2;
  *node2 = tc;
}

static void in_order_visit_bin(void *root)
{
  
}
//public
struct tree_operations *create_environment(int (*compare_key) (void *,void*),
                                    void (*free_data) (void *),
                                    void (*print_key) (void *))
{
  struct tree_operations *ops=malloc(sizeof(*ops));
  ops->compare_key=compare_key;
  ops->free_data=free_data;
  ops->swap_keys=swap_keys;
  ops->print_key=print_key;
  return ops;
}

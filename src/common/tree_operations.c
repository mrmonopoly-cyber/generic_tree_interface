#include <stdlib.h>

#include "tree_operations.h"
//private

struct common_node {
  struct commond_node *children;
  void *key;
};
//functions
static void swap_keys(void ** key1,void **key2)
{
  void *temp=*key1;
  key1=key2;
  key2=&temp;
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

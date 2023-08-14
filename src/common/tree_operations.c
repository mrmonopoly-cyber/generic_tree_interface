


#include "tree_operations.h"

struct tree_operations {
  int (*compare_key) (void *,void*);
  void (*free_data) (void *);
};


tree_operations *create_environment(int (*compare_key) (void *,void*),
                                    void (*free_data) (void *))
{
  tree_operations *ops=malloc(sizeof(*ops));
  ops->compare_key=compare_key;
  ops->free_data=free_data;
}


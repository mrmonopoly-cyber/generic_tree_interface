#include <stdlib.h>

#include "btree.h"

//private

//data structure 
struct btree{
  void *key;
  struct btree **children;
  struct tree_operations *operations;
};

//functions

//public
int BTREE_insert(btree **root,void *key,tree_operations *ops)
{
  return 0;
}

int BTREE_delete(btree **root,void *key)
{
  return 0;
}

void BTREE_free(btree *root)
{
  return ;
}

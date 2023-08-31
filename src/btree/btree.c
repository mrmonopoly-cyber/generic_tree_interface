#include <stdlib.h>

#include "btree.h"

//private

//data structure 

enum NODE_TYPE{LEAF,MIDDLE};

struct btree{
  void *keys;
  struct btree **children;
  struct tree_operations *operations;
};

//functions

//public
int BTREE_insert(btree **root,void *key,tree_operations *ops)
{
  return 0;

invalid_pointer:
  return -1;
}

btree *BTREE_search(btree *root,void *key)
{
 return NULL;
}

int BTREE_delete(btree **root,void *key)
{
  return 0;
}

void BTREE_free(btree *root)
{
  return ;
}

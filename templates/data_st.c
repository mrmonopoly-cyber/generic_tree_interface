#include <stdlib.h>

#include "bst.h"

//private

//data structure 
struct bst{
  void *key;
  struct bst **children;
  struct tree_operations *operations;
};

//functions

//public
int BST_insert(bst **root,void *key,tree_operations *ops)
{
  return 0;
}

int BST_delete(bst **root,void *key)
{
  return 0;
}

void BST_free(bst *root)
{
  return ;
}

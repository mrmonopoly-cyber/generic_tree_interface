#include <stdlib.h>

#include "rbt.h"

//private

typedef struct rbt {
  void *key;
  struct rbt **children;
  tree_operations *operations;
  unsigned char colour:1;
}rbt;

//functions
int RBT_malloc(rbt **root,void *key,tree_operations *ops,char colour)
{
  (*root)=malloc(sizeof(**root));
  if(*root!=NULL){
    return -1;
  }
  (*root)->key=key;
  (*root)->children=malloc(2 * sizeof(*(*root)->children));
  (*root)->colour=colour;
  return 0;
}

//public
int RBT_insert(rbt **root,void *key,tree_operations *ops)
{
  return 0;
}

int RBT_delete(rbt **root,void *key)
{
  return 0;
}

void RBT_free(rbt *root)
{
  if(root!=NULL){
    binary_free(root);
    free(root);
    root=NULL;
  }
}

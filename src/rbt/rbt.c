#include <stdlib.h>

#include "rbt.h"

//private

enum COLOUR{BLACK,RED };

typedef struct rbt {
  void *key;
  struct rbt **children;
  tree_operations *operations;
  enum COLOUR colour;
}rbt;

//functions
static int RBT_malloc(rbt **root,void *key,tree_operations *ops,enum COLOUR colour)
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
  if(root==NULL){
    goto NULL_pointer;
  }
  if(*root==NULL){
    return RBT_malloc(root,key,ops,BLACK);
  }
  return 0;
  
  //exceptions
  NULL_pointer:
    return -2;

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

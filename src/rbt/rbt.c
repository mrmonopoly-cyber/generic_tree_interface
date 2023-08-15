
#include "rbt.h"

//private

typedef struct rbt {
  void *key;
  struct rbt *children;
  tree_operations *operations;
  char colour:1;
}rbt;

//public
int RBT_insert(rbt **root,void *key,tree_operations *ops)
{

}

int RBT_delete(rbt **root,void *key)
{

}

void RBT_free(rbt *root)
{

}

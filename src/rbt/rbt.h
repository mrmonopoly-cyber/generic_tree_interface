#ifndef _RBT_
#define _RBT_

#include "tree_operations.h"

typedef struct rbt rbt;


int RBT_insert(rbt **root,void *key,tree_operations *ops);
#define RBT_search(R,K) binary_search(R,K)
int RBT_delete(rbt **root,void *key);
void RBT_free(rbt *root);

#endif // !_RBT_

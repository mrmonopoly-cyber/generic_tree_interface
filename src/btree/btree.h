#ifndef _BTREE_TREE_
#define _BTREE_TREE_
#include "tree_operations.h"

typedef struct btree btree;

int BTREE_insert(btree **root,void *key,tree_operations *ops);
#define BTREE_search(R,K) binary_search(R,K)
int BTREE_delete(btree **root,void *key);
void BTREE_free(btree *root);
#define BTREE_pre_order_visit(R) binary_pre_order_visit(R)
#define BTREE_in_order_visit(R) binary_in_order_visit(R)
#define BTREE_post_order_visit(R) binary_post_order_visit(R)

#define BTREE_environment(FK,OTHER) create_environment(FK,OTHER)

#endif // !_BTREE_TREE_

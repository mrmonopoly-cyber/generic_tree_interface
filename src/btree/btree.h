#ifndef _BTREE_TREE_
#define _BTREE_TREE_
#include "tree_operations.h"

typedef struct btree btree;

int BTREE_insert(btree **root,void *key,tree_operations *ops);
btree *BTREE_search(btree *root,void *key);
int BTREE_delete(btree **root,void *key);
void BTREE_free(btree *root);

#define BTREE_environment(CK,FK,PK,NC) create_environment(CK,FK,PK,NC)

#endif // !_BTREE_TREE_

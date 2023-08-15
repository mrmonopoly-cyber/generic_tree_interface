#ifndef _BST_TREE_
#define _BST_TREE_
#include "tree_operations.h"

typedef struct bst bst;

int BST_insert(bst **root,void *key,tree_operations *ops);
int BST_delete(bst **root,void *key);
void BST_free(bst *root);

#endif // !_BST_TREE_

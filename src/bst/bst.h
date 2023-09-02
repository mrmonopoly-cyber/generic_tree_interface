#ifndef _BST_TREE_
#define _BST_TREE_
#include "tree_operations.h"

typedef struct bst bst;

int BST_insert(bst **root,void *key,tree_operations *ops);
#define BST_search(R,K) binary_search(R,K)
int BST_delete(bst **root,void *key);
void BST_free(bst *root);
#define BST_pre_order_visit(R) binary_pre_order_visit(R)
#define BST_in_order_visit(R) binary_in_order_visit(R)
#define BST_post_order_visit(R) binary_post_order_visit(R)

#define BST_environment(CK,PK,FK,OTHER) create_environment(CK,PK,FK,OTHER)

#endif // !_BST_TREE_

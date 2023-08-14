#ifndef _BST_TREE_
#define _BST_TREE_


typedef struct bst bst;

int BST_insert(bst **root,void *key);
int BST_delete(bst **root,void *key);
bst *BST_search(bst **root,void *key);

void BST_free(bst **root);
#endif // !_BST_TREE_

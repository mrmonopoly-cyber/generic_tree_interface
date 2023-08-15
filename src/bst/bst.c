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
int BST_malloc(bst **root,void *key,tree_operations *ops)
{
  *root=malloc(sizeof(**root));
  if(*root == NULL){
    return -1;
  }
  (*root)->key=key;
  (*root)->children=malloc(2*sizeof(*(*root)->children));
  (*root)->operations=ops;
  return 0;
}

//public
int BST_insert(bst **root,void *key,tree_operations *ops)
{
  if(bst==NULL){
    return -2;
  }
  if(*root==NULL){
    return BST_malloc(root,key,ops);
  }

  int is_greater = (*root)->operations->compare_key((*root)->key,key);
  bst *new_node=NULL;
  if(is_greater >= 0){
    return BST_insert(&(*root)->children[1],key,ops);
  }
  return BST_insert(&(*root)->children[0],key,ops);

  return -1;
}

int BST_delete(bst **root,void *key)
{
  //removing an element not in the tree
  if(*root == NULL){
    return -1;
  }
  bst *node = *root;
  //searching node
  int is_greater = node->operations->compare_key(node->key,key);
  if(is_greater > 0){
    return BST_delete(&node->children[1],key);
  }else if(is_greater <0){
    return BST_delete(&node->children[0],key);
  }
  //found it
  
  //leaf node
  if(node->children[0]==NULL && node->children[1]==NULL){
    BST_free(*root);
    *root=NULL;
    return 0;
  }

  //2 children node
  if(node->children[0]!=NULL && node->children[1]!=NULL){
    bst *successor_parent = node;
    bst *greater_child = node->children[1];
    bst *successor = greater_child;
    while (successor->children[0]!=NULL) {
      successor_parent=successor;
      successor=successor->children[0];
    }
    swap_keys(&node->key,&successor->key);
    if(greater_child == successor){
      node->children[1]=successor->children[1];
      successor->children[1]=NULL;
      BST_free(successor);
      return 0;
    }
    BST_free(successor);
    successor_parent->children[0]=NULL;
    return 0;
  }

  //1 child node
  bst *child =node->children[0];
  if(node->children[0]==NULL){
    child=node->children[1];
  }
  swap_keys(&node->key,&child->key);
  node->children[0]=child->children[0];
  node->children[1]=child->children[1];
  child->children[0]=NULL;
  child->children[1]=NULL;
  BST_free(child);
  //error 
  return 0;
}

void BST_free(bst *root)
{
  if(root!=NULL){
    binary_free(root);
    free(root);
    root=NULL;
  }
}

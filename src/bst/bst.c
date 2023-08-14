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

static bst *BST_malloc(void *key,tree_operations *ops)
{
  bst *new_node = malloc(sizeof(*new_node));
  new_node->key=key;
  new_node->children=malloc(sizeof(*new_node->children));
  new_node->operations=ops;
  return new_node;
}

//public
int BST_insert(bst **root,void *key,tree_operations *ops)
{
  if(*root==NULL){
    *root=BST_malloc(key,ops);
    return 0;
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
  bst *node = *root;
  //searching node
  int is_greater = node->operations->compare_key(node->key,key);
  if(is_greater > 0){
    return BST_delete(&node->children[1],key);
  }else if(is_greater <0){
    return BST_delete(&node->children[0],key);
  }
  //find it
  
  //leaf node
  if(node->children[0]==NULL && node->children[1]==NULL){
    BST_free(node);
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
    node->operations->swap_keys(&node->key,&successor->key);
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
  node->operations->swap_keys(&node->key,&child->key);
  node->children[0]=child->children[0];
  node->children[1]=child->children[1];
  child->children[0]=NULL;
  child->children[1]=NULL;
  BST_free(child);
  //error 
  return 0;
}

bst *BST_search(bst **root,void *key)
{
  if(*root!=NULL){
    bst *temp = (*root);
    int is_greater = temp->operations->compare_key(temp->key,key);

    switch (is_greater) {
      case 0:
        return temp;
        break;
      case 1:
        return BST_search(&temp->children[0],key);
        break;
      case -1:
        return BST_search(&temp->children[1],key);
        break;
    }
  }
  return NULL;
}

void BST_free(bst *root)
{
  if(root!=NULL){
    BST_free(root->children[0]);
    BST_free(root->children[1]);

    if(root->key!=NULL && root->operations->free_data!=NULL){
      root->operations->free_data(root->key);
      root->key=NULL;
    }
    free(root);
    root=NULL;
  }
}


void BST_in_order_visit(bst *root)
{
  if(root!=NULL){
    BST_in_order_visit(root->children[0]);
    void *key=root->key;
    root->operations->print_key(key);
    BST_in_order_visit(root->children[1]);
  }
}
//debug

#include <stdio.h>
int compare_key(void *data1,void *data2)
{
  int int_data1 = *(int *) data1;
  int int_data2 = *(int *) data2;
  if(int_data1==int_data2){
    return 0;
  }
  if(int_data1>int_data2){
    return -1;
  }
  return 1;
}

void print_key(void *key)
{
  int dig = *(int *)key;
  printf("%d\n",dig);
}

int main(int argc, char *argv[])
{
  tree_operations *env;
  bst *root=NULL;

  env = create_environment(compare_key,NULL,print_key);
  int key1 = 1;
  int key2 = 2;
  int key4 = 4;

  printf("empty tree\n");
  BST_in_order_visit(root);
  printf("with one insertion\n");
  BST_insert(&root,(void *) &key1,env);
  BST_in_order_visit(root);

  printf("with two insertion\n");
  BST_insert(&root,(void *) &key2,env);
  BST_in_order_visit(root);

  printf("with one instertion and one deletion insertion\n");
  BST_delete(&root,(void *)&key2);
  BST_in_order_visit(root);

  printf("reinsertion after deliting\n");
  BST_insert(&root,(void *) &key4,env);
  BST_in_order_visit(root);

  
  return EXIT_SUCCESS;
}

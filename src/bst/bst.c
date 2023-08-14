#include <stdlib.h>

#include "../common/tree_operations.h"
#include "bst.h"

//private

//data structure 
struct bst{
  void *key;
  bst childs[2];
  bst *parent;
  struct tree_operations *operations;
};

//functions

bst *BST_malloc(void *key,bst *parent)
{
  bst *new_node = malloc(sizeof(*new_node));
  new_node->key=key;
  if(parent!=NULL){
    new_node->parent=parent;
  }
  new_node->childs[0]=NULL;
  new_node->childs[1]=NULL;
  return new_node;
}

void BST_unlink(bst *parent,bst *to_delete)
{
  if(parente->childs[0] != NULL && parente->childs[0] == to_delete){
    parente->childs[0]=NULL;
  }else {
    parente->childs[1]=NULL;
  }
}
//public
int BST_insert(bst **root,void *key)
{
  if(*root==NULL){
    *root=BST_malloc(key,NULL);
    return 0;
  }

  int is_greater = (*root)->operations->compare_key((*root)->key,key);
  bst *new_node=NULL;
  if(is_greater >= 0){
    if((*root)->childs[0] == NULL){
      (*root)->childs[0]=BST_malloc(key,(*root));
    }
    return BST_insert(&(*root)->childs[0],key);
  }
  if((*root)->childs[1] == NULL){
    (*root)->childs[1]=BST_malloc(key,(*root));
  }
  return BST_insert(&(*root)->childs[1],key);

  return -1;
}

int BST_delete(bst **root,void *key)
{
  bst *to_delete = BST_search(root,key);
  bst *to_delete_parent = to_delete->parent;
  bst *candidate;
  
  //leaf node
  if(to_delete->childs[0]==NULL && to_delete->childs[1] == NULL){
    BST_unlink(to_delete_parent,to_delete);
    BST_free(to_delete);
    return 0;
  }
  
  //middle node
  candidate = (*root)->operations->min((*root)->childs[1]);
  if(candidate==NULL){
    candidate = (*root)->operations->max((*root)->childs[0]);
  }
  if(candidate !=NULL){
    (*root)->operations->swap_keys(to_delete,candidate);
    BST_unlink(candidate->parent,candidate);
    BST_free(candidate);
    return 0;
  }
  // double NULL case, need rotation
  candidate = (*root)->operations->min((*root));
  if(candidate==NULL){
    candidate = (*root)->operations->max((*root));
  }
  (*root)->operations->swap_keys(candidate->parent,candidate);
  bst *candidate_parent_childs = candidate->parente->childs;
  if(candidate_parent_childs[0]!=NULL && candidate_parent_childs[0]==candidate){
    candidate_parent_childs[1]=candidate;
    candidate_parent_childs[0]=NULL;
  }else {
    candidate_parent_childs[0]=candidate;
    candidate_parent_childs[1]=NULL;
  }
  BST_delete(&to_delete,key);
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
        return BST_search(&temp->childs[0],key);
        break;
      case -1:
        return BST_search(&temp->childs[1],key);
        break;
    }
  }
  return NULL;
}

void BST_free(bst **root)
{
  if(root!=NULL){
    BST_free(root->childs[0]);
    BST_free(root->childs[1]);

    if(root->key!=NULL && root->operations->free_data!=NULL){
      root->operations->free_data(root->key);
      root->key=NULL;
    }
    free(root);
    root=NULL;
  }
}


//debug
int compare_key(void *data1,void *data2)
{
  int int_data1 = *(int *) data1;
  int int_data2 = *(int *) data2;
  if(int_data1==int_data2){
    return 0;
  }
  if(int_data1<int_data2){
    return -1;
  }
  return 1;
}



int main(int argc, char *argv[])
{
  tree_operations *env;
  env = create_environment(compare_key,NULL);
  int key1 = 1;
  int key2 = 2;
  
  
  return EXIT_SUCCESS;
}

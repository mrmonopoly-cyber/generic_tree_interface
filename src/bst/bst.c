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


//public
int BST_insert(bst **root,void *key)
{
  if(*root==NULL){
    (*root)=malloc(sizeof(**root));
    (*root)->key=key;
    (*root)->parent = NULL;
  }

  int is_greater = (*root)->operations->compare_key((*root)->key,key);

  if(is_greater >= 0){
    return BST_insert(&(*root)->childs[0],key);
  }
  return BST_insert(&(*root)->childs[1],key);

  return -1;
}

int BST_delete(bst **root,void *key)
{
  bst *to_delete = BST_search(root,key);
  bst *to_delete_parent;
  bst *to_delete_child_0;
  bst *to_delete_child_1;
  if(to_delete==NULL){
    return -1;
  }
  
  to_delete_parent = to_delete->parent;
  to_delete_child_0 = to_delete->childs[0];
  to_delete_child_1 = to_delete->childs[1];

  if(to_delete_child_0==NULL && to_delete_child_1 == NULL){
    BST_free(&to_delete);
  }

  
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
  if(*root!=NULL){
    bst *temp = (*root);
    BST_free(&temp->childs[0]);
    BST_free(&temp->childs[1]);

    if(temp->key!=NULL && temp->operations->free_data!=NULL){
      temp->operations->free_data(temp->key);
      temp->key=NULL;
    }
    free(temp);
    *root=NULL;
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

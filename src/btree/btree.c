#include <stdlib.h>

#include "btree.h"

//private

//data structure 

enum NODE_TYPE{LEAF,MIDDLE};

struct btree{
  void *keys;
  struct btree **children;
  struct tree_operations *operations;
  long key_num; //min t-1 max 2t-1
};

//functions
static int BTREE_malloc(btree **root,void *key,tree_operations *operations)
{
  void **keys = malloc(operations->number_of_children*sizeof(*keys));
  if(keys==NULL){
    return -1;
  }
  *root=malloc(sizeof(**root));
  if(*root==NULL){
    goto failed_malloc;
  }

  (*root)->key_num
  (*root)->keys=(void *)keys;
  (*root)->children=malloc(sizeof(operations->number_of_children*sizeof(*(*root)->children)));
  if((*root)->children){
    goto failed_malloc;
  }
  (*root)->operations=operations;
  (*root)->key_num=0;
  return 0;

failed_malloc:
  return -1;
}
//public
int BTREE_insert(btree **root,void *key,tree_operations *ops)
{
  if(root==NULL){
    goto invalid_pointer;
  }
  //new tree case 
  if(*root==NULL){
    return BTREE_malloc(root,key,ops);
  }

  btree *root_conv = *root;
  long number_of_children =root_conv->operations->number_of_children;
  //split node if it is full
  root_conv->key_num==((2*number_of_children)-1){
    
  }

  //finding where to insert
  key_array = (void **)(*root)->keys;
  for (i=0;i<(*root)->key_num;++i) {
    is_greater = (*root)->operations->compare_key(key,key_array[i]);
    if(is_greater<0){
      return BTREE_insert(&(*root)->children[i],key);
    }else if(is_greater>0 && i==((*root)->key_num-1)){
      return BTREE_insert(&(*root)->children[i+1],key);
    }
  }

  return 0;

invalid_pointer:
  return -1;
}

btree *BTREE_search(btree *root,void *key)
{
  void **key_array; 
  int i,is_greater=0;

  if(root!=NULL){
    key_array = (void **)root->keys;
    for (i=0;i<root->key_num;++i) {
      is_greater = root->operations->compare_key(key,key_array[i]);
      if(is_greater<0){
        return BTREE_search(root->children[i],key);
      }else if(is_greater>0 && i==(root->key_num-1)){
        return BTREE_search(root->children[i+1],key);
      }
      if(is_greater==0){
        return key_array[i];
      }
    }
  }
  return NULL;
}

int BTREE_delete(btree **root,void *key)
{
  return 0;
}

void BTREE_free(btree *root)
{
  return ;
}

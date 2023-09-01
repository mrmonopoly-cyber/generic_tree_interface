#include <stdlib.h>
#include <stdio.h>

#include "btree.h"

//private

//data structure 
struct btree{
  void *key;
  struct btree **children;
  struct tree_operations *operations;
  enum NODE_TYPE* children_type;
  long key_num; //min t-1 max 2t-1
};

//functions
static int BTREE_malloc(btree **root,void *key,tree_operations *operations)
{
  if(root==NULL){
    goto invalid_pointer;
  }

  void **keys = malloc( ((2*operations->t)-1) * sizeof(*keys));
  keys[0]=key;
  *root=malloc(sizeof(**root));
  if(*root==NULL){
    goto failed_malloc;
  }

  (*root)->key_num=1;
  (*root)->keys=(void *)keys;
  (*root)->operations=operations;
  (*root)->children=malloc((2*operations->t) * sizeof(*(*root)->children));
  if((*root)->children==NULL){
    goto failed_malloc;
  }
  (*root)->children_type=NULL;
  return 0;

invalid_pointer:
  printf("invalid pointer malloc\n");
  return -1;
failed_malloc:
  printf("failed malloc in BTREE malloc\n");
  return -2;
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
  long t =root_conv->operations->t;
  long index_last_key = ((2*t)-1)-1;
  long index_middle_key = (t-1);
  void **key_array=(void **)root_conv->keys;
  int i,j,is_greater;

  //split node if it is full
  //root of tree is full
  if(root_conv->key_num==((2*t)-1)){
    if(BTREE_malloc(root,key_array[index_middle_key],ops)){
      goto failed_malloc;
    }
    key_array[index_middle_key]=NULL;
  }

  //middle node of tree is full

  //finding where to insert
  key_array = (void **)(*root)->keys;

  if(root_conv->children_type!=NULL){ 
    for (i=0;i<root_conv->key_num;++i) {
      is_greater = (*root)->operations->compare_key(key,key_array[i]);
      btree *minor_child = (*root)->children[i];
      btree *greater_child = (*root)->children[i+1];
      if(is_greater<0){
        return BTREE_insert(&minor_child,key,ops);
      }else if(is_greater>=0 && i==((*root)->key_num-1)){
        return BTREE_insert(&greater_child,key,ops);
      }
    }
    goto invalid_case;
  }else { //inserting in leaf
    for (i=0;i<root_conv->key_num;++i) {
      is_greater = (*root)->operations->compare_key(key,key_array[i]);
      if(is_greater>=0){
        for (j=(root_conv->key_num)-1;j>=i;--j) {
          key_array[j+1]=key_array[j];
        }
        break;
      }
    }
    key_array[i]=key;
    root_conv->key_num+=1;
  }
  

  return 0;

invalid_pointer:
  return -1;
failed_malloc:
  return -2;
invalid_case:
  return -3;
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

void BTREE_pre_order_visit(btree *root)
{
  if(root!=NULL){
    void **key_array=(void **)root->keys;
    for (int i=0;i<root->key_num;++i) {
      if(root->children_type!=NULL){
        BTREE_pre_order_visit(root->children[i]);
      }
      root->operations->print_key(key_array[i]);
      printf("\n");
    }
  }
  return ;
}

void BTREE_in_order_visit(btree *root)
{
  return;
}


void BTREE_post_order_visit(btree *root)
{
  return ;
}

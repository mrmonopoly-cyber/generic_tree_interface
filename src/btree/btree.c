#include <stdlib.h>
#include <stdio.h>

#include "btree.h"

//private

//data structure 
enum NODE_TYPE{LEAF,MIDDLE,NOTHING};

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
  (*root)->children_type=malloc((2*operations->t) * sizeof(*(*root)->children_type));
  for (int i=0;i<2*operations->t;++i) {
    (*root)->children_type[i]=NOTHING;
  }
  if((*root)->children==NULL){
    goto failed_malloc;
  }
  return 0;

invalid_pointer:
  fprintf(stderr,"invalid pointer malloc\n");
  return -1;
failed_malloc:
  fprintf(stderr,"failed malloc in BTREE malloc\n");
  return -2;
}

static void insert_key_in_node(btree *root,void *key)
{
  void **key_array = (void **) root->keys;
  int i,j,is_greater;

  for (i=0;i<root->key_num;++i) {
  is_greater = root->operations->compare_key(key_array[i],key);
    if(is_greater<=0){
      for (j=(root->key_num)-1;j>=i;--j) {
        key_array[j+1]=key_array[j];
      }
      break;
    }
  }
  key_array[i]=key;
  root->key_num+=1;
}

static int split_node(btree **new_node,btree *old_node)
{
  tree_operations *operations = old_node->operations;
  long t =operations->t;
  long index_middle_key = old_node->key_num/2;
  void **key_array=(void **)old_node->keys;
  int i,first_greater;
  btree *greater_child;
  void **new_array_key;
  void *old_middle_key= key_array[index_middle_key];
  void *old_grater_than_middle_key= key_array[index_middle_key+1];
  
  if(*new_node==NULL){
    if(BTREE_malloc(new_node,old_middle_key,operations)){
      goto failed_malloc;
    }

    key_array[index_middle_key]=NULL;
    (*new_node)->children[0]=old_node;
    greater_child=(*new_node)->children[index_middle_key+1];
  }else {
  }

  if(BTREE_malloc(&greater_child,old_grater_than_middle_key,operations)){
    goto failed_malloc;
  }
  
  new_array_key = (void **)greater_child->keys;
  first_greater = index_middle_key+2;
  for (i=first_greater;i<(2*t)-1;++i) {
    new_array_key[i - first_greater] = key_array[i];
    key_array[i]=0x0;
  }

  return 0;
  
failed_malloc:
  fprintf(stderr, "failed_malloc in split_node\n");
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
  btree *minor_child;
  btree *greater_child;
  long t =root_conv->operations->t;
  void **key_array=(void **)root_conv->keys;
  int i,is_greater;

  //split node if it is full
  //root of tree is full
  if(root_conv->key_num==((2*t)-1)){
    *root=NULL;   
    split_node(root,root_conv);
    root_conv=(*root);
  }
  


  //finding where to insert
  key_array = (void **)(*root)->keys;

  if(root_conv->children_type[0]!=NOTHING){ 
    for (i=0;i<root_conv->key_num;++i) {
      is_greater = (*root)->operations->compare_key(key_array[i],key);
      minor_child = (*root)->children[i];
      greater_child = (*root)->children[i+1];

      if(is_greater<0){
        if(minor_child->key_num==(2*t)-1){
          split_node(root,minor_child);
        }
        return BTREE_insert(&minor_child,key,ops);
      }else if(is_greater>=0 && i==((*root)->key_num-1)){
        if(greater_child->key_num==(2*t)-1){
          split_node(root,greater_child);
        }
        return BTREE_insert(&greater_child,key,ops);
      }
    }
    goto invalid_case;
  }else { //inserting in leaf
    insert_key_in_node(root_conv,key);
  }
  

  return 0;

invalid_pointer:
  fprintf(stderr, "invalid_pointer in BTREE_insert\n");
  return -1;
invalid_case:
  fprintf(stderr, "invalid_case in BTREE_insert\n");
  return -2;
}

btree *BTREE_search(btree *root,void *key)
{
  void **key_array; 
  int i,is_greater=0;

  if(root!=NULL){
    key_array = (void **)root->keys;
    for (i=0;i<root->key_num;++i) {
      is_greater = root->operations->compare_key(key_array[i],key);
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
  void **key_array;
  int i;
  
  if(root!=NULL){
    key_array=(void **)root->keys;
    for(i=0;i<root->key_num;++i){
      root->operations->free_data(key_array[i]);
    }
    free(root->keys);
    for (i=0;i<root->key_num+1;++i) {
      if(root->children[i]!=NULL){
        free(root->children[i]);
      }
    }
    if (root->children_type!=NULL) {
      free(root->children_type);
    }
  }
  return ;
}

void BTREE_pre_order_visit(btree *root)
{
  int i=0;
  if(root!=NULL){
    void **key_array=(void **)root->keys;
    printf("node start with length %ld\n",root->key_num);
    for (i=0;i<root->key_num;++i) {
      root->operations->print_key(key_array[i]);
      printf("\n");
    }
    printf("node end\n");
    for (i=0;i<=root->key_num;++i) {
      if(root->children_type[i]!=NOTHING){
        BTREE_pre_order_visit(root->children[i]);
      }
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

#include <stdlib.h>
#include <stdio.h>

#include "btree.h"

//private

//data structure 
enum NODE_TYPE{LEAF,MIDDLE};

struct btree{
  void *keys;
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
  
  void **keys;
  long t = *(long *)operations->other;

  keys = malloc( ((2*t)-1) * sizeof(*keys));
  keys[0]=key;
  *root=malloc(sizeof(**root));
  if(*root==NULL){
    goto failed_malloc;
  }

  (*root)->key_num=1;
  (*root)->keys=(void *)keys;
  (*root)->operations=operations;
  (*root)->children=malloc(2*t * sizeof(*(*root)->children));
  (*root)->children_type=malloc(2*t * sizeof(*(*root)->children_type));
  for (int i=0;i<2*t;++i) {
    (*root)->children_type[i]=LEAF;
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

static void insert_key_in_node(btree **root,void *key)
{
  long *key_array = (void *) (*root)->keys;
  btree **children = (*root)->children;
  int i,j,is_greater;

  for (i=0;i<(*root)->key_num;++i) {
  is_greater = (*root)->operations->compare_key(&key_array[i],key);
    if(is_greater<=0){
      for (j=((*root)->key_num)-1;j>=i;--j) {
        key_array[j+1]=key_array[j];
        children[j+1]=children[j];
      }
      break;
    }
  }
  key_array[i]=(long)key;
  (*root)->key_num+=1;
}

static int split_node(btree **new_node,btree *old_node)
{
  tree_operations *operations = old_node->operations;
  long t =*(long *)operations->other;
  long index_middle_key = old_node->key_num/2;
  long *key_array=(long *)old_node->keys;
  int i,first_greater;
  btree *greater_child;
  long old_middle_key= key_array[index_middle_key];
  long old_grater_than_middle_key= key_array[index_middle_key+1];
  
  if(*new_node==NULL){
    if(BTREE_malloc(new_node,(void *)old_middle_key,operations)){
      goto failed_malloc;
    }
    key_array[index_middle_key]=0x0;
    (*new_node)->children[0]=old_node;


    if(BTREE_malloc(&(*new_node)->children[1],(void *)old_grater_than_middle_key,operations)){
      goto failed_malloc;
    }
    greater_child=(*new_node)->children[1];
    (*new_node)->children_type[0]=MIDDLE;
    (*new_node)->children_type[1]=MIDDLE;

  }else {
    insert_key_in_node(new_node,(void *)old_middle_key);
    key_array[index_middle_key]=0x0;
    for (i=0;i<(*new_node)->key_num;++i) {
      if(((void **)(*new_node)->keys)[i]==(void *)old_middle_key){
        (*new_node)->children[i]=old_node;
      }
    }
    if(BTREE_malloc(&(*new_node)->children[i+1],(void *)old_grater_than_middle_key,operations)){
      goto failed_malloc;
    }
    (*new_node)->children_type[i]=MIDDLE;
    (*new_node)->children_type[i+1]=MIDDLE;
    greater_child=(*new_node)->children[i+1];
  } 

  old_node->key_num-=2;

  first_greater = index_middle_key+2;
  for (i=first_greater;i<(2*t)-1;++i) {
    insert_key_in_node(&greater_child,(void *)key_array[i]);
    key_array[i]=0x0;
    old_node->key_num-=1;
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
  long t =*(long *)root_conv->operations->other;
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

  for (i=0;i<root_conv->key_num;++i) {
    is_greater = root_conv->operations->compare_key(&key_array[i],key);
    minor_child = (*root)->children[i];
    greater_child = (*root)->children[i+1];

    if(is_greater<0){
      if(minor_child->key_num==(2*t)-1 && (*root)->children_type[i]!=LEAF){
        split_node(root,minor_child);
      }
      return BTREE_insert(&minor_child,key,ops);
    } 
  }
  if(is_greater>=0 && (*root)->children_type[i]!=LEAF){
    if(greater_child->key_num==(2*t)-1){
      split_node(root,greater_child);
    }
    return BTREE_insert(&greater_child,key,ops);
  }

  //insert in current node (LEAF)
  insert_key_in_node(root,key);
  return 0;
  

invalid_pointer:
  fprintf(stderr, "invalid_pointer in BTREE_insert\n");
  return -1;
}

btree *BTREE_search(btree *root,void *key)
{
  long *key_array; 
  int i,is_greater=0;

  if(root!=NULL){
    key_array = (long *)root->keys;
    for (i=0;i<root->key_num;++i) {
      is_greater = root->operations->compare_key(&key_array[i],key);
      if(is_greater<0){
        return BTREE_search(root->children[i],key);
      }else if(is_greater>0 && i==(root->key_num-1)){
        return BTREE_search(root->children[i+1],key);
      }
      if(is_greater==0){
        return root;
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
  long *key_array;
  if(root!=NULL){
    key_array=(long *)root->keys;
    printf("node start with length %ld\n",root->key_num);
    for (i=0;i<root->key_num;++i) {
      root->operations->print_key((void *)key_array[i]);
      printf("\n");
    }
    for (i=0;i<=root->key_num;++i) {
      if(root->children_type[i]!=LEAF){
        BTREE_pre_order_visit(root->children[i]);
      }
    }
  }
}

void BTREE_in_order_visit(btree *root)
{
  int i=0;
  long *key_array;
  if(root!=NULL){
    key_array=(long *)root->keys;
    for (i=0;i<root->key_num;++i) {
      if(root->children_type[i]!=LEAF){
        BTREE_in_order_visit(root->children[i]);
      }
      root->operations->print_key((void *)key_array[i]);
      printf("\n");
    }
    if(root->children_type[i]!=LEAF){
      BTREE_in_order_visit(root->children[i]);
    }

  }
}


void BTREE_post_order_visit(btree *root)
{
  int i=0;
  long *key_array;
  if(root!=NULL){
    key_array=(long *)root->keys;
    for (i=0;i<root->key_num;++i) {
      root->operations->print_key((void *)key_array[i]);
      printf("\n");
      if(root->children_type[i]!=LEAF){
        BTREE_in_order_visit(root->children[i]);
      }
    }
    if(root->children_type[i]!=LEAF){
      BTREE_in_order_visit(root->children[i]);
    }

  }
}

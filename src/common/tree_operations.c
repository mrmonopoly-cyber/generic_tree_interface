#include <stdlib.h>

#include "tree_operations.h"
//private

//functions


void swap_child(common_tree **node1,common_tree **node2)
{
  common_tree *temp = *node1;
  *node1=*node2;
  *node2=temp;
}

//public
struct tree_operations *create_environment(int (*compare_key) (void *,void*),
                                    void (*free_data) (void *),
                                    void (*print_key) (void *))
{
  struct tree_operations *ops=malloc(sizeof(*ops));
  ops->compare_key=compare_key;
  ops->free_data=free_data;
  ops->print_key=print_key;
  return ops;
}

void binary_pre_order_visit(void *root)
{
  common_tree *t=(common_tree *)root;
  if(t!=NULL){
    void *key=t->key;
    t->operations->print_key(key);
    binary_pre_order_visit((void *)t->children[0]);
    binary_pre_order_visit((void *)t->children[1]);
  }
}

void binary_in_order_visit(void *root)
{
  common_tree *t=(common_tree *)root;
  if(t!=NULL){
    binary_in_order_visit((void *)t->children[0]);
    void *key=t->key;
    t->operations->print_key(key);
    binary_in_order_visit((void *)t->children[1]);
  }
}

void binary_post_order_visit(void *root)
{
  common_tree *t=(common_tree *)root;
  if(t!=NULL){
    void *key=t->key;
    binary_pre_order_visit((void *)t->children[0]);
    binary_pre_order_visit((void *)t->children[1]);
    t->operations->print_key(key);
  }
}

int binary_rotation(void **root, enum ROTATION_DIRECTION direction)
{
  common_tree **conv_root = (common_tree **) root;
  common_tree **to_swap = &(*conv_root)->children[0];
  if(direction==RIGHT){
    to_swap = &(*conv_root)->children[1];
  }
  swap_keys((void **)conv_root,(void **)to_swap);
  swap_child(&(*to_swap)->children[0],&(*to_swap)->children[1]);
  switch (direction) {
    case LEFT:
      swap_child(&(*to_swap)->children[1],&(*conv_root)->children[1]);
      break;
    case RIGHT:
      swap_child(&(*to_swap)->children[0],&(*conv_root)->children[0]);
      break;
    default:
      goto invalid_direction;
  }
  swap_child(&(*conv_root)->children[0],&(*conv_root)->children[1]);
  
  return 0;

invalid_direction:
  return -1;
}

void *binary_search(void *root,void *key)
{
  common_tree *temp = (common_tree *)root;
  if(temp!=NULL){
    int is_greater = temp->operations->compare_key(temp->key,key);

    switch (is_greater) {
      case 0:
        return temp;
        break;
      case 1:
        return binary_search(&temp->children[0],key);
        break;
      case -1:
        return binary_search(&temp->children[1],key);
        break;
    }
  }
  return NULL;
}

void binary_free(void *root)
{
  if(root!=NULL){
    common_tree *temp = (common_tree *)root;
    binary_free(temp->children[0]);
    binary_free(temp->children[1]);

    if(temp->key!=NULL && temp->operations->free_data!=NULL){
      temp->operations->free_data(temp->key);
      temp->key=NULL;
    }
  }
}

void swap_keys(void **node1,void **node2)
{
  char *c1 = *(char **) node1;
  char *c2 = *(char **) node2;
  char *tc = c1;
  *node1 = c2;
  *node2 = tc;
}

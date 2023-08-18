#include <stdlib.h>

#include "tree_operations.h"
//private

//functions

void swap_child(common_tree **node1,int child1, common_tree **node2,int child2)
{
  common_tree *temp = (*node1)->children[child1];

  (*node1)->children[child1]=(*node2)->children[child2];
  (*node2)->children[child2]=temp;
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
  common_tree *conv_root = *(common_tree **) root;
  common_tree *to_swap = conv_root->children[0];
  common_tree *temp;
  int which_child=1;

  if(direction==RIGHT){
    to_swap = (conv_root)->children[1];
    which_child=0;
  }

  swap_keys((void *)conv_root,(void *)to_swap);

  // swap_child(conv_root,0,conv_root,1);
  temp=(conv_root)->children[0];
  conv_root->children[0]=conv_root->children[1];
  conv_root->children[1]=temp;
  temp=NULL;
  
  // swap_child(conv_root,0,to_swap,0);
  // swap_child(conv_root,0,to_swap,0);
  temp=conv_root->children[which_child];
  conv_root->children[which_child]=to_swap->children[which_child];
  to_swap->children[which_child]=temp;
  temp=NULL;
  
  // swap_child(to_swap,0,to_swap,1);
  temp=to_swap->children[0];
  to_swap->children[0]=to_swap->children[1];
  to_swap->children[1]=temp;
  temp=NULL;

  // switch (direction) {
  //   case LEFT:
  //     // swap_child(conv_root,1,to_swap,1);
  //     break;
  //   case RIGHT:
  //     // swap_child(conv_root,0,to_swap,0);
  //     temp=(*conv_root)->children[0];
  //     (*conv_root)->children[0]=(*to_swap)->children[0];
  //     (*to_swap)->children[0]=temp;
  //
  //     break;
  //   default:
  //     goto invalid_direction;
  // }
  // swap_child(to_swap,0,to_swap,1);
  
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
  common_tree *node1c = *(common_tree **) node1;
  common_tree *node2c = *(common_tree **) node2;
  void *temp =  (node1c)->key;
  (node1c)->key=(node2c)->key;
  (node2c)->key=temp;
}

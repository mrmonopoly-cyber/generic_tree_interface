#include <stdlib.h>

#include "tree_operations.h"
//private

//functions

void swap_child(common_tree **node1,int child1, common_tree **node2,int child2)
{
  common_tree *child1_p=(*node1)->children[child1];
  common_tree *child2_p=(*node2)->children[child2];
  common_tree *temp=child1_p;

  (*node1)->children[child1]=child2_p;
  (*node2)->children[child2]=temp;
}

//public
struct tree_operations *create_environment(int (*compare_key) (void *,void*),
                                    void (*free_data) (void *),
                                    void (*print_key) (void *),
                                    int number_of_children)
{
  struct tree_operations *ops=malloc(sizeof(*ops));
  ops->compare_key=compare_key;
  ops->free_data=free_data;
  ops->print_key=print_key;
  ops->number_of_children=number_of_children;
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
    binary_post_order_visit((void *)t->children[0]);
    binary_post_order_visit((void *)t->children[1]);
    t->operations->print_key(key);
  }
}

int binary_rotation(void *root, enum ROTATION_DIRECTION direction)
{
  int which_child=1;
  common_tree *conv_root = *(common_tree **) root;
  common_tree *to_swap;

  if(direction==RIGHT){
    which_child=0;
  }

  to_swap = (conv_root)->children[which_child];
  swap_keys(root,&to_swap);
  swap_child(&conv_root,0,&conv_root,1);
  swap_child(&conv_root,which_child,&to_swap,which_child);
  swap_child(&to_swap,0,&to_swap,1);
 
  return 0;
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

void swap_keys(void *node1,void *node2)
{
  common_tree *node1c = *(common_tree **) node1;
  common_tree *node2c = *(common_tree **) node2;
  void *temp =  (node1c)->key;
  (node1c)->key=(node2c)->key;
  (node2c)->key=temp;
}

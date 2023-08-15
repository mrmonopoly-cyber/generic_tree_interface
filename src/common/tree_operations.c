#include <stdlib.h>

#include "tree_operations.h"
//private

typedef struct common_tree {
  void *key;
  struct common_tree **children;
  tree_operations *operations;
}common_tree;

//functions
static void swap_keys(void **node1,void **node2)
{
  char *c1 = *(char **) node1;
  char *c2 = *(char **) node2;
  char *tc = c1;
  *node1 = c2;
  *node2 = tc;
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

//public
struct tree_operations *create_environment(int (*compare_key) (void *,void*),
                                    void (*free_data) (void *),
                                    void (*print_key) (void *))
{
  struct tree_operations *ops=malloc(sizeof(*ops));
  ops->compare_key=compare_key;
  ops->free_data=free_data;
  ops->swap_keys=swap_keys;
  ops->print_key=print_key;
  return ops;
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

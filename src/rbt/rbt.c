#include <stdlib.h>

#include "rbt.h"

//private

enum COLOUR{BLACK,RED };

struct rbt {
  void *key;
  struct rbt **children;
  tree_operations *operations;
  struct rbt *parent;
  enum COLOUR colour;
};

//functions
static int RBT_malloc(rbt **root,void *key,tree_operations *ops,rbt *parent,enum COLOUR colour)
{
  (*root)=malloc(sizeof(**root));
  if(*root==NULL){
    return -1;
  }
  (*root)->key=key;
  (*root)->children=malloc(2 * sizeof(*(*root)->children));
  (*root)->children[0]=NULL;
  (*root)->children[1]=NULL;
  (*root)->colour=colour;
  (*root)->operations=ops;
  (*root)->parent=parent;
  return 0;
}

static void reset_parent_after_rotation(rbt *parent,rbt *child,enum ROTATION_DIRECTION dir)
{
  int which_child=0;
  if(dir==LEFT){
    which_child=1;
  }
  if(parent->children[which_child]!=NULL){
    parent->children[which_child]->parent=parent;
  }
  if(child->children[which_child]!=NULL){
    child->children[which_child]->parent=child;
  }
}

static int double_rotation(rbt *grandparent,rbt *parent,int index_pr_ch,rbt *child,
                           enum ROTATION_DIRECTION first_rotation,enum ROTATION_DIRECTION second_rotation)
{
  if(parent->children[index_pr_ch]!=NULL && parent->children[index_pr_ch]==child){
    if(binary_rotation(&parent,first_rotation)){
      goto failed_rotation;
    }
    reset_parent_after_rotation(parent,child,first_rotation);
  }
  if(binary_rotation(&grandparent,second_rotation)){
    goto failed_rotation;
  }
  reset_parent_after_rotation(grandparent,parent,second_rotation);
  return 0;
failed_rotation:
  return -1;
}
static int colour_correction(rbt *child){
  rbt *parent= child->parent;
  rbt *grandparent;
  rbt *uncle;

  //parent of child is NULL (root case)
  if(parent==NULL){
    child->colour=BLACK;
    return 0;
  }
  //child red and parent black
  if( parent->colour==BLACK ){
    return 0;
  }
  //child is red , parent is red.
  grandparent = parent->parent;
  uncle = grandparent->children[0];
  if(uncle == parent){
    uncle = grandparent->children[1];
  }
  //child red,parent red,uncle red
  if(uncle!=NULL && uncle->colour==RED){
    parent->colour=BLACK;
    uncle->colour=BLACK;
    grandparent->colour=RED;
    return colour_correction(grandparent);
  }
  //child red, parent red, uncle black

  //case LR LL 
  if(grandparent->children[0]!=NULL && grandparent->children[0]==parent){
    return double_rotation(grandparent,parent,1,child,LEFT,RIGHT);
  }

  // //case RL RR
  if(grandparent->children[1]!=NULL && grandparent->children[1]==parent){
    return double_rotation(grandparent,parent,0,child,RIGHT,LEFT);
  }

  //errors
  return -2;
}

//public
int RBT_insert_full(rbt **root,void *key,rbt *parent,tree_operations *ops)
{
  if(root==NULL){
    goto NULL_pointer;
  }
  //searching 
  if(*root!=NULL){
    int is_greater = (*root)->operations->compare_key((*root)->key,key);
    if(is_greater >= 0){
      return RBT_insert_full(&(*root)->children[1],key,(*root),ops);
    }else {
      return RBT_insert_full(&(*root)->children[0],key,(*root),ops);
    
    }
  }
  //inserting
  if(RBT_malloc(root,key,ops,parent,RED)){
    goto failed_malloc;
  }
 
  //parent colour red and current node colour red
  return colour_correction(*root);
  
  //exceptions
failed_malloc:
    return -1;
NULL_pointer:
    return -2;

}

int RBT_delete(rbt **root,void *key)
{
  return 0;
}

void RBT_free(rbt *root)
{
  if(root!=NULL){
    binary_free(root);
    free(root);
    root=NULL;
  }
}

int valid_rbt(rbt *root)
{
  int right,left=0;

  if(root==NULL){
    return 1;
  }
  if(root->colour==BLACK){
    right = 1 + valid_rbt(root->children[1]);
    left = 1 + valid_rbt(root->children[0]);
  }else {
    right = valid_rbt(root->children[1]);
    left = valid_rbt(root->children[0]);
  } 
  if(right!=left){
    return 0;
  }
  return right;

}

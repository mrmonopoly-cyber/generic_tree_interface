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
  (*root)->colour=colour;
  (*root)->operations=ops;
  (*root)->parent=parent;
  return 0;
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
  if(uncle == child){
    uncle = grandparent->children[1];
  }
  //child red,parent red,uncle red
  if(uncle->colour==RED){
    parent->colour==BLACK;
    uncle->colour==BLACK;
    parent->parent->colour=RED;
    return colour_correction(grandparent);
  }
  //child red, parent red, uncle black
  //left left case (LL)
  return binary_rotation((void **)&grandparent,RIGHT);
  //left right case (LR)
  if(binary_rotation((void **)&parent,LEFT)){
    goto failed_rotation;
  }
  return binary_rotation((void **)&grandparent,RIGHT);
  //right right case (RR)
  return binary_rotation((void **)&grandparent,LEFT);
  //right left case (RL)
  if(binary_rotation((void **)&parent,RIGHT)){
    goto failed_rotation;
  }
  return binary_rotation((void **)&grandparent,LEFT);

   
  return 0;
failed_rotation:
  return -1;
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

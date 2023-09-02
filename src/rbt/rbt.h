#ifndef _RBT_
#define _RBT_

#include "tree_operations.h"

typedef struct rbt rbt;

#define RBT_environment(CK,PK,FK,OTHER) create_environment(CK,PK,FK,OTHER)

int RBT_insert_full(rbt **root,void *key,rbt *parent,tree_operations *ops);
#define RBT_insert(root,key,ops) RBT_insert_full(root,key,NULL,ops);
#define RBT_search(R,K) binary_search(R,K)
int RBT_delete(rbt **root,void *key);
void RBT_free(rbt *root);
void RBT_pre_order_visit(rbt *root);
#define RBT_in_order_visit(R) binary_in_order_visit(R)
#define RBT_post_order_visit(R) binary_post_order_visit(R)
#define RBT_pre_order_visit(R) binary_pre_order_visit(R)

#ifdef DEBUG
#undef RBT_pre_order_visit
void debug_RBT_pre_order_visit(rbt *root);
#define RBT_pre_order_visit(R) debug_RBT_pre_order_visit(R)
void set_colour(rbt *root,int colour);
rbt *get_right_child(rbt *root);
rbt *get_left_child(rbt *root);
int valid_rbt(rbt *root);
int correct_parents(rbt *root);
#endif // DEBUG
       
#endif // !_RBT_

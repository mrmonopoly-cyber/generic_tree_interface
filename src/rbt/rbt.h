#ifndef _RBT_
#define _RBT_

#include "tree_operations.h"

typedef struct rbt rbt;

#define RBT_environment(CK,FD,PK) create_environment(CK,FD,PK)

int RBT_insert_full(rbt **root,void *key,rbt *parent,tree_operations *ops);
#define RBT_insert(root,key,ops) RBT_insert_full(root,key,NULL,ops);
#define RBT_search(R,K) binary_search(R,K)
int RBT_delete(rbt **root,void *key);
void RBT_free(rbt *root);
#define RBT_pre_order_visit(R) binary_pre_order_visit(R)
#define RBT_in_order_visit(R) binary_in_order_visit(R)
#define RBT_post_order_visit(R) binary_post_order_visit(R)

int valid_rbt(rbt *root);

#endif // !_RBT_

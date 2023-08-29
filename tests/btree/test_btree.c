#include <stdio.h>

#include "btree.h"

int main(void)
{
  tree_operations *env;
  btree *root=NULL;
  int dati[] = {2,3,4,5,6,7};
  int num_el = sizeof(dati) / sizeof(dati[0]);
  int rm[] = {};
  int rm_len = sizeof(rm) / sizeof(rm[0]);
  int t = 3;

  env = BTREE_environment(NULL,t);
  
  //insert
  for (int i=0;i<num_el;++i) {
    BTREE_insert(&root,(void *) &dati[i],env);
  }
  printf("dopo tutti gli inserimenti\n");
  printf("pre_order visit\n");
  BTREE_pre_order_visit(root);
  printf("in_order visit\n");
  BTREE_in_order_visit(root);

  //delete
  for (int j=0;j<rm_len;++j) {
    BTREE_delete(&root,(void *)&rm[j]);
    printf("eliminato %d\n",rm[j]);
  }
  printf("dopo tutte le eliminazioni\n");
  printf("pre_order visit\n");
  BTREE_pre_order_visit(root);
  printf("in_order visit\n");
  BTREE_in_order_visit(root);
  
  BTREE_free(root);
  root=NULL;
  BTREE_pre_order_visit(root);
  return 0;
}

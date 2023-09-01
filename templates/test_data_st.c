#include <stdio.h>

#include "bst.h"

int main(void)
{
  tree_operations *env;
  bst *root=NULL;
  int dati[] = {};
  int num_el = sizeof(dati) / sizeof(dati[0]);
  int rm[] = {};
  int rm_len = sizeof(rm) / sizeof(rm[0]);
  env = BST_environment(NULL,NULL);
  
  //insert
  for (int i=0;i<num_el;++i) {
    BST_insert(&root,(void *) &dati[i],env);
  }
  printf("dopo tutti gli inserimenti\n");
  printf("pre_order visit\n");
  BST_pre_order_visit(root);
  printf("in_order visit\n");
  BST_in_order_visit(root);

  //delete
  for (int j=0;j<rm_len;++j) {
    BST_delete(&root,(void *)&rm[j]);
    printf("eliminato %d\n",rm[j]);
  }
  printf("dopo tutte le eliminazioni\n");
  printf("pre_order visit\n");
  BST_pre_order_visit(root);
  printf("in_order visit\n");
  BST_in_order_visit(root);
  
  BST_free(root);
  root=NULL;
  BST_pre_order_visit(root);
  return 0;
}

#include <stdio.h>

#include "bst.h"

<<<<<<< HEAD
int main(void)
=======
int compare_key(void *root_key,void *key)
{
  int int_root_key = *(int *) root_key;
  int int_key = *(int *) key;
  if(int_root_key==int_key){
    return 0;
  }
  if(int_key>int_root_key){
    return 1;
  }
  return -1;
}

void print_key(void *key)
{
  int dig = *(int *)key;
  printf("%d\n",dig);
}

int main(int argc, char *argv[])
>>>>>>> 9da5086 (bugfix in BTREE_insert partial implementation, refactored compare_key function in template, tested partial implementation BTREE_insert)
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

#include <stdio.h>

#include "bst.h"

int compare_key(void *node_key,void *key)
{
  int node_key_int = *(int *)node_key;
  int key_conv = *(int *)key;
  if(key_conv<node_key_int){
    return -1;
  }else if (key_conv>node_key_int) {
    return 1;
  }
  return 0;
}

void print_key(void * key)
{
  printf("%d",*(int *)key);
}

int main(void)
{
  tree_operations *env;
  bst *root=NULL;
  int dati[] = {};
  int num_el = sizeof(dati) / sizeof(dati[0]);
  int rm[] = {};
  int rm_len = sizeof(rm) / sizeof(rm[0]);
  env = BST_environment(compare_key,print_key,NULL,NULL);
  
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

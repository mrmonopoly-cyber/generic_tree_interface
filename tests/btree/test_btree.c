#include <stdio.h>

#include "btree.h"

int compare_key(void *data1,void *data2)
{
  int int_data1 = *(int *) data1;
  int int_data2 = *(int *) data2;
  if(int_data1==int_data2){
    return 0;
  }
  if(int_data1>int_data2){
    return -1;
  }
  return 1;
}

void print_key(void *key)
{
  int dig = *(int *)key;
  printf("%d\n",dig);
}

int main(int argc, char *argv[])
{
  tree_operations *env;
  btree *root=NULL;
  int dati[] = {};
  int num_el = sizeof(dati) / sizeof(dati[0]);
  int rm[] = {};
  int rm_len = sizeof(rm) / sizeof(rm[0]);
  env = BTREE_environment(compare_key,NULL,print_key);
  
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

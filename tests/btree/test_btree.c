#include <stdio.h>

#include "btree.h"

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
  btree *root=NULL;
  int dati[] = {10,20,30,40,50,60,70,80,90,100,22,25,30,2,0,1,21,110,120,75};
  int num_el = sizeof(dati) / sizeof(dati[0]);
  int rm[] = {};
  int rm_len = sizeof(rm) / sizeof(rm[0]);
  long t = 2;

  env = BTREE_environment(compare_key,print_key,NULL,&t);
  
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

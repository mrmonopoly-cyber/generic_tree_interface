#include <stdio.h>

#include "rbt.h"


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
  printf("%d\t",dig);
}

int main(int argc, char *argv[])
{
  tree_operations *env;
  rbt *root=NULL;
  int dati[] = {30,20,40,37,35,19,35};
  int num_el = sizeof(dati) / sizeof(dati[0]);
  int rm[] = {20,40,19};
  int rm_len = sizeof(rm) / sizeof(rm[0]);
  env = RBT_environment(compare_key,NULL,print_key);
 
  //insert
  for (int i=0;i<num_el;++i) {
    RBT_insert(&root,(void *) &dati[i],env);
  }
  printf("dopo tutti gli inserimenti\n");
  printf("pre_order visit\n");
  RBT_pre_order_visit(root);
  printf("in_order visit\n");
  RBT_in_order_visit(root);
  printf("\n");
  if(valid_rbt(root)){
    printf("this is an rbt\n");
  }
  if(correct_parents(root)){
    printf("correct parents\n");
  }
  //delete
  for (int j=0;j<rm_len;++j) {
    RBT_delete(&root,(void *)&rm[j]);
  }
  printf("dopo tutte le eliminazioni\n");
  printf("pre_order visit\n");
  RBT_pre_order_visit(root);
  printf("in_order visit\n");
  RBT_in_order_visit(root);
  printf("\n");
  if(valid_rbt(root)){
    printf("this is an rbt\n");
  }

  if(correct_parents(root)){
    printf("correct parents\n");
  }

  
  RBT_free(root);
  root=NULL;
  RBT_pre_order_visit(root);
  return 0;
}

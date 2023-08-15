#ifndef _TREE_OPERATIONS_
#define _TREE_OPERARIONS_


typedef struct tree_operations tree_operations;
struct tree_operations {
  int (*compare_key) (void *,void*);
  void (*free_data) (void *);
  void (*print_key) (void *);
};

typedef struct common_tree {
  void *key;
  struct common_tree **children;
  tree_operations *operations;
}common_tree;


tree_operations *create_environment(int (*compare_key) (void *,void*),
                                    void (*free_data) (void *),
                                    void (*print_key) (void *));

void binary_in_order_visit(void *root);
void binary_pre_order_visit(void *root);
void *binary_search(void *root,void *key);
void binary_free(void *root);

void swap_keys(void **node1,void **node2);

#endif // _TREE_OPERATIONS_

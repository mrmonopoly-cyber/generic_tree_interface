#ifndef _TREE_OPERATIONS_
#define _TREE_OPERATIONS_

enum ROTATION_DIRECTION { LEFT = 0, RIGHT = 1 };

typedef struct tree_operations tree_operations;
struct tree_operations {
  int (*compare_key)(void *, void *);
  void (*free_data)(void *);
  void (*print_key)(void *);
  void *other;
  unsigned int ref_number;
};

typedef struct common_tree {
  void *key;
  struct common_tree **children;
  tree_operations *operations;
} common_tree;

struct tree_operations *create_environment(int (*compare_key)(void *, void *),
                                           void (*print_key)(void *),
                                           void (*free_data)(void *),
                                           void *other);

void binary_pre_order_visit(void *root);
void binary_in_order_visit(void *root);
void binary_post_order_visit(void *root);

int binary_rotation(void *root, enum ROTATION_DIRECTION direction);

void *binary_search(void *root, void *key);
void binary_free(void *root);

void swap_keys(void *node1, void *node2);

#endif // _TREE_OPERATIONS_

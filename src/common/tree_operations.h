#ifdef _TREE_OPERATIONS_

typedef struct tree_operations;

tree_operations *create_environment(int (*compare_key) (void *,void*),
                                    void (*free_data) (void *));

#endif // _TREE_OPERATIONS_

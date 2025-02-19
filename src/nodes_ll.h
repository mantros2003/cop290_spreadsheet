#ifndef NODES_LL_H_
#define NODES_LL_H_

struct cell;

/*
 * Struct for linked list of cell pointers
 * These pointers are edges in the dependency graph
 */
struct nodes_ll {
  struct cell *cell_ptr;
  struct nodes_ll *next;
};

struct nodes_ll *mk_ll();

void free_ll(struct nodes_ll**);

int num_nodes(struct nodes_ll*);

void print_ll(struct nodes_ll*);

void rm_node_ll(struct nodes_ll**, struct cell*);

void add_node_end(struct nodes_ll**, struct nodes_ll**);

struct nodes_ll *copy_ll(struct nodes_ll*);

#endif // NODES_LL_H_

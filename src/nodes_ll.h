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

void rm_node_ll(struct nodes_ll**, struct cell**);

void print_ll(struct nodes_ll*);

struct nodes_ll *mk_ll();

#endif // NODES_LL_H_

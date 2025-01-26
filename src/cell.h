#ifndef CELL_H_
#define CELL_H_

#define DATA int

struct nodes_ll;

/*
 * Struct to store a cell; contains data, edges of dependency graph, and operator
 * Operator defines the cell's relation with its children
 */
struct cell {
  DATA data;
  char oper;
  struct nodes_ll *in_edges;
  struct nodes_ll *out_edges;
};

void print_cell(struct cell *c);

void rm_in_edges(struct cell **c);

void add_dep(struct cell **from, struct cell **to, char oper);

#endif // CELL_H_

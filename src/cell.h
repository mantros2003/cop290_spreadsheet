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
  _Bool error;
  struct nodes_ll *in_edges;
  struct nodes_ll *out_edges;
};

struct cell *mk_cell();

void print_cell(struct cell *c);

#endif // CELL_H_

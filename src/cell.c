#include "cell.h"
#include "nodes_ll.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Returns a new dynamically allocated struct cell with all values initialized to NULL
 */
struct cell *mk_cell() {
  struct cell *cell = malloc(sizeof(struct cell));
  cell->data = 0;
  cell->oper = ' ';
  cell->error = 0;
  cell->in_edges = NULL;
  cell->out_edges = NULL;

  return cell;
}

/*
 * Prints all the fields in cell
 */
void print_cell(struct cell *c) {
  printf("data = %d oper = %c in_edges = %s out_edges = %s\n",
         c->data, c->oper, (c->in_edges == NULL) ? "no": "yes", (c->out_edges == NULL) ? "no": "yes");
}

/*
int main() {
  struct cell *c1 = malloc(sizeof(struct cell));
  c1->data = 120, c1->oper = ' ', c1->in_edges = NULL, c1->out_edges = NULL;
  struct cell *c2 = malloc(sizeof(struct cell));
  c2->data = 12, c2->oper = ' ', c2->in_edges = NULL, c2->out_edges = NULL;
  struct cell *c3 = malloc(sizeof(struct cell));
  c3->data = 1, c3->oper = ' ', c3->in_edges = NULL, c3->out_edges = NULL;

  add_dep(&c2, &c1, '+');
  add_dep(&c3, &c1, '+');
  print_cell(c1);
  print_cell(c2);
  print_cell(c3);

  rm_in_edges(&c1);

  print_cell(c1);
  print_cell(c2);
  print_cell(c3);
  printf("%p", (void*) &c1);
  return 0;
}
*/

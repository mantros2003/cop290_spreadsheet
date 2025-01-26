#include "cell.h"
#include "nodes_ll.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Prints all the fields in cell
 */
void print_cell(struct cell *c) {
  printf("data = %d oper = %c in_edges = %s out_edges = %s\n",
         c->data, c->oper, (c->in_edges == NULL) ? "no": "yes", (c->out_edges == NULL) ? "no": "yes");
}

/*
 * Function to remove all in_edges from cell
 */
void rm_in_edges(struct cell **c) {
  printf("w");
  printf("x");
  struct nodes_ll *prev_node = NULL;
  struct nodes_ll *curr_node = (*c)->in_edges;
  while (curr_node != NULL) {
    printf("a");
    rm_node_ll(&((curr_node->cell_ptr)->out_edges), c);
    printf("b");
    prev_node = curr_node;
    curr_node = curr_node->next;
    free(prev_node);
  }

  (*c)->in_edges = NULL;
}

/*
 * Adds a new nodes_ll in from->out_edges and to->in_edges
 * Establishes link between cells from and to
 * from haas a link to cell to
 * to has a link to cell from
 * Changes to's operator to the operator provided in function
 */
void add_dep(struct cell **from, struct cell **to, char oper) {
  // nodes_ll to be added to the front of from's nodes_ll
  // The node will have a pointer to the cell to
  struct nodes_ll *from_dep = mk_ll();
  from_dep->cell_ptr = *to;

  struct nodes_ll *from_head = (*from)->out_edges;
  (*from)->out_edges = from_dep;
  from_dep->next = from_head;
  
  struct nodes_ll *to_dep = mk_ll();
  to_dep->cell_ptr = *from;

  struct nodes_ll *to_head = (*to)->in_edges;
  (*to)->in_edges = to_dep;
  to_dep->next = to_head;

  (*to)->oper = oper;
}

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

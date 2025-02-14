#include "nodes_ll.h"
#include "cell.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Returns a new nodes_ll instance with all pointers NULL
 */
struct nodes_ll *mk_ll() {
  struct nodes_ll *ll_head = malloc(sizeof(struct nodes_ll));
  ll_head->cell_ptr = NULL;
  ll_head->next = NULL;
  return ll_head;
}

int num_nodes(struct nodes_ll *head) {
  int sz = 0;
  while (head != NULL) {
    ++sz;
    head = head->next;
  }

  return sz;
}

/*
 * Prints all the pointers in the linked list
 */
void print_ll(struct nodes_ll *head) {
  while (head != NULL)  {
    printf("%p ", (void*) head->cell_ptr);
    head = head->next;
  }

  printf("\n");
}

/*
 * Removes the node which contains the pointer to cell target
 */
void rm_node_ll(struct nodes_ll **head_node, struct cell *target) {
  struct nodes_ll *prev = NULL;
  struct nodes_ll *curr = *head_node;

  while (curr != NULL) {
    if (target == curr->cell_ptr) {
      if (prev == NULL) {
        *head_node = curr->next;
      } else {
        prev->next = curr->next;
        free(curr);
      }

      break;
    }

    prev = curr;
    curr = curr->next;
  }
}

/*
 * Function to remove all in_edges from cell
 */
void rm_in_edges(struct cell *c) {
  struct nodes_ll *prev_node = NULL;
  struct nodes_ll *curr_node = c->in_edges;

  while (curr_node != NULL) {
    // Removing the out edge from the cell reffered to in this cell
    rm_node_ll(&((curr_node->cell_ptr)->out_edges), c);

    // Traversing the linked list and freeing the nodes
    prev_node = curr_node;
    curr_node = curr_node->next;
    free(prev_node);
  }

  c->oper = ' ';
  c->in_edges = NULL;
}

/*
 * Adds a new nodes_ll in from->out_edges and to->in_edges
 * Establishes link between cells from and to
 * from haas a link to cell to
 * to has a link to cell from
 * Changes to's operator to the operator provided in function
 */
void add_dep(struct cell *from, struct cell *to, char oper) {
  // nodes_ll to be added to the front of from's nodes_ll
  // The node will have a pointer to the cell to
  struct nodes_ll *from_dep = mk_ll();
  from_dep->cell_ptr = to;

  struct nodes_ll *from_head = from->out_edges;
  from->out_edges = from_dep;
  from_dep->next = from_head;
  
  struct nodes_ll *to_dep = mk_ll();
  to_dep->cell_ptr = from;

  struct nodes_ll *to_head = to->in_edges;
  to->in_edges = to_dep;
  to_dep->next = to_head;

  to->oper = oper;
}

/*
int main() {
  struct cell *c1 = malloc(sizeof(struct cell));
  c1->data = 123;
  c1->in_edges = NULL;
  c1->out_edges = NULL;
  struct cell *c2 = malloc(sizeof(struct cell));
  c2->data = 12;
  c2->in_edges = NULL;
  c2->out_edges = NULL;
  struct cell *c3 = malloc(sizeof(struct cell));
  c3->data = 1;
  c3->in_edges = NULL;
  c3->out_edges = NULL;

  struct nodes_ll *n1 = mk_ll();
  struct nodes_ll *n2 = mk_ll();
  struct nodes_ll *n3 = mk_ll();
  n1->cell_ptr = c1;
  n2->cell_ptr = c2;
  n3->cell_ptr = c3;
  n1->next = n2;
  n2->next = n3;
  n3->next = NULL;

  print_ll(n1);
  print_ll(n2);
  print_ll(n3);

  rm_node_ll(&n1, &c2);

  print_ll(n1);

  free(c1);
  free(c2);
  free(c3);
  free(n1);
  free(n2);
  free(n3);
}

*/

#include "nodes_ll.h"
#include "cell.h"
#include <stdio.h>
#include <stdlib.h>

void rm_node_ll(struct nodes_ll **head_node, struct cell **target) {
  struct nodes_ll *prev = NULL;
  struct nodes_ll *curr = *head_node;

  while (curr != NULL) {
    if (*target == curr->cell_ptr) {
      if (prev == NULL) {
        *head_node = curr->next;
      } else {
        prev->next = curr->next;
      }

      break;
    }

    prev = curr;
    curr = curr->next;
  }
}

struct nodes_ll *mk_ll() {
  struct nodes_ll *ll_head = malloc(sizeof(struct nodes_ll));
  ll_head->cell_ptr = NULL;
  ll_head->next = NULL;
  return ll_head;
}

void print_ll(struct nodes_ll *head) {
  while (head != NULL)  {
    printf("%p ", (void*) head->cell_ptr);
    head = head->next;
  }

  printf("\n");
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

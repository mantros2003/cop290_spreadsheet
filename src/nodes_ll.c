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

void free_ll(struct nodes_ll **head) {
  struct nodes_ll *curr = *head;
  struct nodes_ll *temp = *head;

  while (curr != NULL) {
    temp = curr->next;
    free(curr);
    curr = temp;
  }

  *head = NULL;
}

/*
 * Adds new_node to the end of linked list whose head is head
 */
void add_node_end(struct nodes_ll **head, struct nodes_ll **new_node) {
  struct nodes_ll* curr = *head;

  while (curr != NULL && curr->next != NULL) curr = curr->next;

  if (curr == NULL) *head = *new_node;
  else curr->next = *new_node;
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
      if (prev == NULL) *head_node = curr->next;        // Node to be rwmoved is head, so setting head to be curr's next
      else prev->next = curr->next;                     // Setting prev's next to be curr's next
      
      curr->next = NULL;

      free(curr);
      
      break;      
    }
   
    prev = curr;
    curr = curr->next;
  }
}

/**
 * Function returns a new linked list with all cell pointers in the same order
 */
struct nodes_ll *copy_ll(struct nodes_ll *node) {
  if (node == NULL) return NULL;

  struct nodes_ll *head = mk_ll(), *curr = head;

  while (node != NULL) {
    curr->cell_ptr = node->cell_ptr;

    if (node->next != NULL) curr->next = mk_ll();
    node = node->next;
    curr = curr->next;
  }

  return head;
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

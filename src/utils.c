#include "hashset.h"
#include "nodes_ll.h"
#include "cell.h"
#include <stdio.h>

/*
 * Travels the graph depth first assuming the graph to be undirected
 * Travels both the out edged and the in edges to construct the complete connected component
 */
struct nodes_ll *dfs_ud(struct cell *cell, hashset *visited, struct nodes_ll *component) {
  struct nodes_ll *new_node = mk_ll();
  new_node->cell_ptr = cell;
  new_node->next = component;
  
  insert_hset(visited, (long) cell, cell);

  struct nodes_ll *node = cell->in_edges;
  while (node != NULL) {
    if (!in_hset(visited, (long) node->cell_ptr, node->cell_ptr)) {
      new_node = dfs_ud(node->cell_ptr, visited, new_node);
    }

    node = node->next;
  }

  node = cell->out_edges;
  while (node != NULL) {
    if (!in_hset(visited, (long) node->cell_ptr, node->cell_ptr)) {
      new_node = dfs_ud(node->cell_ptr, visited, new_node);
    }

    node = node->next;
  }

  return new_node;
}

/*
 * Returns the connected component that cell is part of
 */
struct nodes_ll *connected_component(struct cell *cell) {
  hashset *visited = mk_hashset(NULL, HASHTABLE_SIZE);
  struct nodes_ll *component = dfs_ud(cell, visited, NULL);
  free_hset(visited);
  return component;
}

/*
 * Travels the graph depth first and travels only through out edges
 */
_Bool traverse(struct cell* curr_cell, hashset* visited_global, hashset* visited_local) {
  _Bool result = 0;

  struct nodes_ll *node = curr_cell->out_edges;
  while (node != NULL) {
    printf("checking %p...\n", node->cell_ptr);
    if (in_hset(visited_local, (long) node->cell_ptr, node->cell_ptr)) return 1;
    else if (!in_hset(visited_global, (long) node->cell_ptr, node->cell_ptr)) {
      printf("visiting %p...\n", node->cell_ptr);
      insert_hset(visited_global, (long) node->cell_ptr, node->cell_ptr);
      insert_hset(visited_local, (long) node->cell_ptr, node->cell_ptr);
      result |= traverse(node->cell_ptr, visited_global, visited_local);
      if (result) return result;
    }

    node = node->next;
  }

  return result;
}

/**
 * Checks if the connected component component has a cycle
 */
_Bool contains_cycle(struct nodes_ll *component) {
  hashset *visited_global = mk_hashset(NULL, HASHTABLE_SIZE);

  struct nodes_ll *curr = component;
  while (curr != NULL) {
    hashset *visited_local = mk_hashset(NULL, HASHTABLE_SIZE);
    printf("current node: %p...\n", curr->cell_ptr);
    if (!in_hset(visited_global, (long) curr->cell_ptr, curr->cell_ptr)) {
      printf("starting traversal from %p...\n", curr->cell_ptr);
      insert_hset(visited_global, (long) curr->cell_ptr, curr->cell_ptr);
      insert_hset(visited_local, (long) curr->cell_ptr, curr->cell_ptr);
      if (traverse(curr->cell_ptr, visited_global, visited_local)) {
        free_hset(visited_local);
        free_hset(visited_global);
        return 1;
      }
    }

    curr = curr->next;
    free_hset(visited_local);
  }

  free_hset(visited_global);

  return 0;
}

int main() {
  struct cell *cells[5];
  for (int i = 0; i < 5; i++) {
    cells[i] = mk_cell();
    printf("made cell %d at %p\n", i, cells[i]);
  }

  add_dep(cells[1], cells[2], '+');
  add_dep(cells[2], cells[3], '+');
  add_dep(cells[3], cells[4], '+');
  add_dep(cells[4], cells[0], '+');
  add_dep(cells[0], cells[1], '+');

  struct nodes_ll *node = connected_component(cells[1]);
  printf("%d nodes, contains cycle: %s ", num_nodes(node), contains_cycle(node) ? "yes" : "no");
  print_ll(node);

  node = connected_component(cells[3]);
  printf("%d nodes, contains cycle: %s ", num_nodes(node), contains_cycle(node) ? "yes" : "no");
  print_ll(node);

  for (int i = 0; i < 5; i++) free(cells[i]);

  return 0;
}

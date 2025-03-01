#include "utils.h"
#include "hashset.h"
#include "nodes_ll.h"
#include "cell.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Custom input function that takes input till '\n'
 */
void get_ip(char* buff, int sz) {
	char c;
	--sz;

	while ((c = getchar()) != '\n' && c != EOF && sz--) {
		*buff++ = c;
	}

	*buff = '\0';
}

/*
 * Adds a new nodes_ll in from->out_edges and to->in_edges
 * Establishes link between cells from and to
 * from has a link to cell to
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

/**
 * Adds dependency, and additionaly checks if the cells are initialized or not
 */
void add_dependency(database *db, int from_cell, int to_cell, char oper) {
  struct cell *from = get_cell(db, from_cell / 1000, from_cell % 1000);
  struct cell *to = get_cell(db, to_cell / 1000, to_cell % 1000);

  if (from == NULL) {
    set(db, from_cell % 1000, from_cell / 1000, 0);
    from = get_cell(db, from_cell / 1000, from_cell % 1000);
  }
  if (to == NULL) {
    set(db, to_cell % 1000, to_cell / 1000, 0);
    to = get_cell(db, to_cell / 1000, to_cell % 1000);
  }

  add_dep(from, to, oper);
}

/**
 * Adds dependency to a range of cells range_start: range_end
 */
void add_dep_range(database *db, int target, int range_start, int range_end, char oper) {
  int col_start = range_start / 1000, row_start = range_start % 1000;
  int col_end = range_end / 1000, row_end = range_end % 1000;

  for (int row = row_start; row <= row_end; row++) {
    for (int col = col_start; col <= col_end; col++) {
      add_dependency(db, 1000 * col + row, target, oper);
    }
  }
}

/*
 * Add dependencies from a linked list
 */
void add_dep_ll(struct nodes_ll *ll, struct cell *to) {
  to->in_edges = ll;

  while (ll != NULL) {
    struct cell *from = ll->cell_ptr;

    struct nodes_ll *from_dep = mk_ll();
    from_dep->cell_ptr = to;
    from_dep->next = from->out_edges;
    from->out_edges = from_dep;

    ll = ll->next;
  }
}

/*
 * Function to remove all in_edges from cell
 */
void rm_all_dep(struct cell *c) {
if(c == NULL){
	return ;
}
  struct nodes_ll *prev_node = NULL;
  struct nodes_ll *curr_node = c->in_edges;

  //printf("Removing deps %p\n", curr_node);
  while (curr_node != NULL) {
    if (curr_node->cell_ptr == NULL) {
    	prev_node = curr_node;
	    curr_node = curr_node->next;
	    prev_node->next = NULL;
	    free(prev_node);
	 continue;
    }
    // Removing the out edge from the cell reffered to in this cell
    //printf("cell_ptr:%\n",curr_node->cell_ptr);
    
    //printf("Before: ");
    //printf("inedges: ");
    //print_ll(curr_node->cell_ptr->in_edges);
    //printf("outedges: ");
    //print_ll(curr_node->cell_ptr->out_edges);
    
    rm_node_ll(&((curr_node->cell_ptr)->out_edges), c);
  
    //printf("After: ");
    //printf("inedges: ");
    //print_ll(curr_node->cell_ptr->in_edges);
    //printf("outedges: ");
    //print_ll(curr_node->cell_ptr->out_edges);

    // Traversing the linked list and freeing the nodes
    prev_node = curr_node;
    curr_node = curr_node->next;
    prev_node->next = NULL;
    free(prev_node);
  }

  c->oper = ' ';
  c->in_edges = NULL;
}


void rm_all_dep2(struct cell *c) {
if(c == NULL){
	return ;
}
  struct nodes_ll *prev_node = NULL;
  struct nodes_ll *curr_node = c->out_edges;

  //printf("Removing deps %p\n", curr_node);
  while (curr_node != NULL) {
    if (curr_node->cell_ptr == NULL) {
    	prev_node = curr_node;
	    curr_node = curr_node->next;
	    prev_node->next = NULL;
	    free(prev_node);
	 continue;
    }
    // Removing the out edge from the cell reffered to in this cell
    //printf("cell_ptr:%\n",curr_node->cell_ptr);
    
    //printf("Before: ");
    //printf("inedges: ");
    //print_ll(curr_node->cell_ptr->in_edges);
    //printf("outedges: ");
    //print_ll(curr_node->cell_ptr->out_edges);
    
    rm_node_ll(&((curr_node->cell_ptr)->in_edges), c);
  
    //printf("After: ");
    //printf("inedges: ");
    //print_ll(curr_node->cell_ptr->in_edges);
    //printf("outedges: ");
    //print_ll(curr_node->cell_ptr->out_edges);

    // Traversing the linked list and freeing the nodes
    prev_node = curr_node;
    curr_node = curr_node->next;
    prev_node->next = NULL;
    free(prev_node);
  }

  c->oper = ' ';
  c->in_edges = NULL;
}

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
 * Travels the graph depth first, but only considers the out edges
 */
struct nodes_ll *dfs_d(struct cell *cell, hashset *visited, struct nodes_ll *component) {
  insert_hset(visited, (long) cell, cell);

  struct nodes_ll *node = cell->out_edges;
  while (node != NULL) {
    if (!in_hset(visited, (long) node->cell_ptr, node->cell_ptr)) {
      component = dfs_d(node->cell_ptr, visited, component);
    }

    node = node->next;
  }
  
  struct nodes_ll *new_node = mk_ll();
  new_node->cell_ptr = cell;
  new_node->next = NULL;

  if (component == NULL) return new_node;

  add_node_end(&component, &new_node);

  return component;
}

/*
 * Returns the connected component that cell is part of
 */
struct nodes_ll *connected_component(struct cell *cell) {
  hashset *visited = mk_hashset(NULL, HASHTABLE_SIZE);
  struct nodes_ll *component = dfs_ud(cell, visited, NULL);
  free_hset(&visited);
  return component;
}

/*
 * Travels the graph depth first and travels only through out edges
 */
_Bool traverse(struct cell* curr_cell, hashset* visited, hashset* visiting) {
  _Bool result = 0;

  insert_hset(visited, (long) curr_cell, curr_cell);
  insert_hset(visiting, (long) curr_cell, curr_cell);

  struct nodes_ll *node = curr_cell->out_edges;
  while (node != NULL) {
    if (in_hset(visiting, (long) node->cell_ptr, node->cell_ptr)) return 1;
    else if (!in_hset(visited, (long) node->cell_ptr, node->cell_ptr)) {
      result |= traverse(node->cell_ptr, visited, visiting);
      if (result) return result;
    }

    node = node->next;
  }

  rm_hset(visiting, (long) curr_cell, curr_cell);

  return result;
}

/*
 * Checks if the connected component component has a cycle
 */
_Bool contains_cycle(struct nodes_ll *component) {
  hashset *visited = mk_hashset(NULL, HASHTABLE_SIZE);

  struct nodes_ll *curr = component;
  while (curr != NULL) {
    hashset *visiting = mk_hashset(NULL, HASHTABLE_SIZE);
    if (!in_hset(visited, (long) curr->cell_ptr, curr->cell_ptr)) {
      insert_hset(visited, (long) curr->cell_ptr, curr->cell_ptr);
      insert_hset(visiting, (long) curr->cell_ptr, curr->cell_ptr);
      if (traverse(curr->cell_ptr, visited, visiting)) {
        free_hset(&visited);
        free_hset(&visiting);
        return 1;
      }
    }

    curr = curr->next;
    free_hset(&visiting);
  }

  free_hset(&visited);

  return 0;
}

/*
 * Returns the topological ordering of the component of the graph
 */
struct nodes_ll *topo_sort(struct cell *c) {
  struct nodes_ll *topo_order = NULL;
  hashset *visited = mk_hashset(NULL, HASHTABLE_SIZE);

  // Gets a reverse topological sort ordering from the cell c
  // Then reverses the order
  struct nodes_ll *rev_topo = dfs_d(c, visited, NULL);
  struct nodes_ll *curr = rev_topo;
  
  // Reversing the ordering
  while (curr != NULL) {
    struct nodes_ll *new_node = mk_ll();
    new_node->cell_ptr = curr->cell_ptr;
    new_node->next = topo_order;
    topo_order = new_node;

    curr = curr->next;
  }

  free_ll(&rev_topo);
  free_hset(&visited);

  return topo_order;
}

/*
 * From database's num_rows and num_cols, determines if the cell is in range
 */
_Bool cell_in_range(database *db, int cell) {
  return !((cell / 1000 >= db->num_cols) || (cell % 1000 >= db->num_rows));
}

/*
 * Frees the isolated cells in a linked list
 */
void free_isolated_cells(struct nodes_ll *dep) {
  while (dep != NULL) {
    if (dep->cell_ptr != NULL && dep->cell_ptr->oper == -1) {
    	free_ll(&(dep->cell_ptr->out_edges));
    	free(dep->cell_ptr);
    	dep->cell_ptr = NULL;
    }
    dep = dep->next;
  }
}

// int main() {
//   struct cell *cells[5];
//   for (int i = 0; i < 5; i++) {
//     cells[i] = mk_cell();
//     printf("made cell %d at %p\n", i, cells[i]);
//   }

//   add_dep(cells[0], cells[1], '+');
//   add_dep(cells[0], cells[2], '+');
//   add_dep(cells[1], cells[2], '+');
//   add_dep(cells[1], cells[4], '+');
//   add_dep(cells[2], cells[3], '+');
//   add_dep(cells[2], cells[4], '+');
//   add_dep(cells[3], cells[4], '+');

//   struct nodes_ll *node = connected_component(cells[1]);
//   printf("%d nodes, contains cycle: %s ", num_nodes(node), contains_cycle(node) ? "yes" : "no");
//   print_ll(node);

//   node = topo_sort(cells[0]);
//   print_ll(node);

//   return 0;
// }

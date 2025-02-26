#include "cell.h"
#include "utils.h"      // Make utils.h
#include "database.h"
#include "nodes_ll.h"
#include "_parser.h"
#include "evaluator.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

/*
 * Reevaluates cell c based on its oper
 * Calls appropriate function for functions
 */
void evaluate(struct cell *c) {
  if (c->oper == 1)
    ;

  if (c->oper == 2) {
    if (c->in_edges->cell_ptr->error) c->error = 1;
    else {
      c->data = c->in_edges->cell_ptr->data;
      c->error = 0;
    }
  }
  if (c->oper >= 3 && c->oper <= 6) {
    struct cell *left, *right;
    right = c->in_edges->cell_ptr;
    left = c->in_edges->next->cell_ptr;

    if (right->error || left->error) {
      c->error = 1;
      return;
    }
    
    if (c->oper == 3) {
      c->data = left->data + right->data;
      c->error = 0;
    }
    if (c->oper == 4) {
      c->data = left->data - right->data;
      c->error = 0;
    }
    if (c->oper == 5) {
      c->data = left->data * right->data;
      c->error = 0;
    }
    if (c->oper == 6) {
      if (right->data == 0) c->error = 1;
      else {
        c->data = left->data / right->data;
        c->error = 0;
      }
    }
  }

  if (c->oper == 7) min_fn(c);

  if (c->oper == 8) max_fn(c);

  if (c->oper == 9) avg_fn(c);

  if (c->oper == 10) sum_fn(c);

  if (c->oper == 11) stdev_fn(c);

  if (c->oper == 12) sleep_fn(c);
}

/*
 * Implements the sleep functionality; takes a cell
 * First cell is target; Second cell when argument of sleep is a cell
 * Else second cell is a NULL pointer if the argument of sleep is an int
 */
void sleep_fn(struct cell *target) {
  if (target->in_edges == NULL) {
    if (target->data >= 0) sleep(target->data);
    target->error = 0;
    return;
  }

  if (target->in_edges->cell_ptr->error) target->error = 1;
  else if (target->in_edges->cell_ptr->data >= 0) {
    sleep(target->in_edges->cell_ptr->data);
    target->error = 0;
  }
  else target->error = 0;
}

/**
 * Calculates the maximum of the range cell target depends on
 */
void max_fn(struct cell* target) {
  int _max = INT_MIN;

  struct nodes_ll *node = target->in_edges;
  while (node != NULL) {
    if (node->cell_ptr->error) {
      target->error = 1;
      return;
    }

    _max = (node->cell_ptr->data > _max) ? node->cell_ptr->data : _max;
    node = node->next;
  }

  target->data = _max;
  target->error = 0;
}

/**
 * Calculates the minimum of the range cell target depends on
 */
void min_fn(struct cell* target) {
  int _min = INT_MAX;

  struct nodes_ll *node = target->in_edges;
  while (node != NULL) {
    if (node->cell_ptr->error) {
      target->error = 1;
      return;
    }

    _min = (node->cell_ptr->data < _min) ? node->cell_ptr->data : _min;
    node = node->next;
  }

  target->data = _min;
  target->error = 0;
}

/**
 * Calculates the sum of cells dependent on cell target
 */
void sum_fn(struct cell* target) {
  int _sum = 0;

  struct nodes_ll *node = target->in_edges;
  while (node != NULL) {
    if (node->cell_ptr->error) {
      target->error = 1;
      return;
    }

    _sum += node->cell_ptr->data;
    node = node->next;
  }

  target->data = _sum;
  target->error = 0;
}

/**
 * Calculates the average of cells dependent on cell taregt
 */
void avg_fn(struct cell* target) {
  int _avg = 0, cnt = 0;

  struct nodes_ll *node = target->in_edges;
  while (node != NULL) {
    if (node->cell_ptr->error) {
      target->error = 1;
      return;
    }

    _avg += node->cell_ptr->data;
    ++cnt;
    node = node->next;
  }

  target->data = _avg / cnt;
  target->error = 0;
}

/**
 * Calculates the STDEV of the cells dependent on cell target
 */
void stdev_fn(struct cell* target) {
  int _avg;

  avg_fn(target);

  _avg = target->data;
  double _var = 0.0;
  int cnt = 0;

  struct nodes_ll *node = target->in_edges;
  while (node != NULL) {
    if (node->cell_ptr->error) {
      target->error = 1;
      return;
    }
    
    _var += (node->cell_ptr->data - _avg) * (node->cell_ptr->data - _avg);
    node = node->next;
    ++cnt;
  }
  _var /= (double) cnt;

  target->data = (int) round(sqrt(_var));
  target->error = 0;
}

/*
 * Takes input from parsera and acts on it
 */
int evaluator(response r, database *db, int *topleft, _Bool *running, _Bool *display_state) {
  print_resp(r);
  if (r.status) return r.status;

  // Checking functions that don't have a target
  if (r.func == 17) {
    *running = 0;
    *display_state = 0;

    return -1;
  }

  if (r.func == 18) {
    *display_state = 0;
    return 0;
  }

  if (r.func == 19) {
    *display_state = 1;
    return 0;
  }

  int col = *topleft / 1000, row = *topleft % 1000;
  if (r.func == 13) row = (row - 10 < 0) ? 0 : row - 10;
  if (r.func == 14) col = (col + 20 > db->num_cols) ? db->num_cols - 10 : col + 10;
  if (r.func == 15) col = (row - 10 < 0) ? 0 : row - 10;
  if (r.func == 16) row = (row + 20 > db->num_rows) ? db->num_rows - 10 : row + 10;

  *topleft = 1000 * col + row;

  if (r.func >= 13 && r.func <= 16) return 0;

  // Now all functions have a target
  if (!cell_in_range(db, r.target - 1001)) return 2;   // Check the error code

  // scroll_to function
  if (r.func == 20) {
    *topleft = r.target - 1001;
    return 0;
  }

  if (get_cell(db, r.target / 1000 - 1, r.target % 1000 - 1) == NULL) set(db, r.target % 1000 - 1, r.target / 1000 - 1, 0);
  struct cell *target = get_cell(db, r.target / 1000 - 1, r.target % 1000 - 1);

  // Can refactor such that all topological ordering is done commonly
  if (r.func == 1) {
    rm_all_dep(target);
    set(db, r.target % 1000 - 1, r.target / 1000 - 1, r.arg1);
    target->oper = r.func;
    target->error = 0;

    struct nodes_ll *topo_order = topo_sort(target);
    struct nodes_ll *curr = topo_order;

    while (curr != NULL) {
      evaluate(curr->cell_ptr);
      curr = curr->next;
    }

    free_ll(&topo_order);

    return 0;
  }

  if (r.func == 2) {
    if (!cell_in_range(db, r.arg1 - 1001)) return 2;     // Error code

    struct nodes_ll *copy_dep = copy_ll(target->in_edges);                                // Take a copy of old dependencies
    char oper_old = target->oper;
    rm_all_dep(target);                                                                   // Remove dependencies from target
    add_dependency(db, r.arg1 - 1001, r.target - 1001, r.func);

    struct nodes_ll *node = connected_component(get_cell(db, r.target / 1000 - 1, r.target % 1000 - 1));
    _Bool has_cycle = contains_cycle(node);

    if (has_cycle) {
      rm_all_dep(target);
      add_dep_ll(copy_dep, target);
      target->oper = oper_old;

      free_ll(&copy_dep);
      free_ll(&node);

      return 3;                     // Error code
    }

    free_ll(&copy_dep);
    free_ll(&node);

    struct nodes_ll *topo_order = topo_sort(target);
    struct nodes_ll *curr = topo_order;

    while (curr != NULL) {
      evaluate(curr->cell_ptr);
      curr = curr->next;
    }

    free_ll(&topo_order);
    return 0;
  }

  if (((r.arg_type & 2) && !cell_in_range(db, r.arg1)) || ((r.arg_type & 1) && !cell_in_range(db, r.arg1))) return 2;   // Error code

  struct nodes_ll *copy_dep = copy_ll(target->in_edges);
  char old_oper = target->oper;
  rm_all_dep(target);

  if (r.func >= 3 && r.func <= 6) {
    if ((r.arg_type & 2) == 0 && (r.arg_type & 1) == 0) {
      if (r.func == 3) target->data = r.arg1 + r.arg2;
      if (r.func == 4) target->data = r.arg1 - r.arg2;
      if (r.func == 5) target->data = r.arg1 * r.arg2;
      if (r.func == 6) {
        if (r.arg2 == 0) target->error = 1;
        else target->data = r.arg1 / r.arg2;
      }

      free_isolated_cells(copy_dep);
      free_ll(&copy_dep);
      return 0;
    }
    if (r.arg_type & 2) add_dependency(db, r.arg1 - 1001, r.target - 1001, r.func);
    else {
      struct cell* c = mk_isolated_cell();
      c->data = r.arg1;
      add_dep(c, target, r.func);
    }

    if (r.arg_type & 1) add_dependency(db, r.arg2 - 1001, r.target - 1001, r.func);
    else {
      struct cell* c = mk_isolated_cell();
      c->data = r.arg2;
      add_dep(c, target, r.func);
    }
  }

  if (r.func >= 7 && r.func <= 11) {
    add_dep_range(db, r.target - 1001, r.arg1 - 1001, r.arg2 - 1001, r.func);
  }

  if (r.func == 12) {
    if (r.arg_type & 2) {
      add_dependency(db, r.target - 1001, r.arg1 - 1001, r.func);
    }
    else {
      target->data = r.arg1;
      target->oper = r.func;
    }
  }

  struct nodes_ll *dep_graph = connected_component(target);
  _Bool has_cycle = contains_cycle(dep_graph);

  if (has_cycle) {
    free_isolated_cells(target->in_edges);
    rm_all_dep(target);
    add_dep_ll(copy_dep, target);
    target->oper = old_oper;

    free_ll(&dep_graph);
    free_ll(&copy_dep);

    return 3;                   // Error code
  }

  free_isolated_cells(copy_dep);
  free_ll(&dep_graph);
  free_ll(&copy_dep);

  struct nodes_ll *topo_order = topo_sort(target);
  struct nodes_ll *curr = topo_order;

  while (curr != NULL) {
    evaluate(curr->cell_ptr);
    curr = curr->next;
  }

  free_ll(&topo_order);

  return 0;
}

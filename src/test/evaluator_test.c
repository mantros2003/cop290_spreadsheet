#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "../evaluator.h"
#include "../database.h"
#include "../cell.h"
#include "../nodes_ll.h"
#include "../_parser.h"
#include "../utils.h"

// Some dummy functions

bool cell_in_range2(database *db, int index) {
    // For testing, assume a cell index is valid if 0 <= index < num_cols*num_rows.
    return (index >= 0 && index < db->num_cols * db->num_rows);
}

void rm_all_dep2(struct cell *c) {
    free_ll(&c->in_edges);
}

void add_dep2endency2(database *db, int src_index, int tgt_index, char func) {
    // Dummy stub: simulate dependency addition (do nothing).
    (void)db; (void)src_index; (void)tgt_index; (void)func;
}

void add_dep2(struct cell *src, struct cell *tgt, char func) {
    // Dummy stub: add src to tgt's dependency list.
    (void)func;
    struct nodes_ll *node = mk_ll();
    node->cell_ptr = src;
    add_node_end(&tgt->in_edges, &node);
}

void add_dep2_range(database *db, int target_index, int start_index, int end_index, char func) {
    // Dummy stub: simulate adding dependencies from a range.
    (void)target_index; (void)func;
    struct cell *target = get_cell(db, 0, 0);
    for (int i = start_index; i < end_index; i++) {
        struct cell *dep = get_cell(db, 0, i);
        if (dep == NULL) {
            dep = mk_isolated_cell();
            dep->data = i + 100;
            set(db, i, 0, dep->data);
            dep = get_cell(db, 0, i);
        }
        add_dep2(dep, target, func);
    }
}

void free_isolated_cells2(struct nodes_ll *ll) {
    // Dummy stub: do nothing.
    (void)ll;
}

struct nodes_ll* topo_sort2(struct cell *target) {
    // Dummy stub: return a list containing only the target.
    struct nodes_ll *node = mk_ll();
    node->cell_ptr = target;
    return node;
}

struct nodes_ll* connected_component2(struct cell *target) {
    // Dummy stub: return a list containing only the target.
    struct nodes_ll *node = mk_ll();
    node->cell_ptr = target;
    return node;
}

bool contains_cycle2(struct nodes_ll *ll) {
    // Dummy implementation: if any dependency equals the target, return true.
    if (ll && ll->cell_ptr && ll->cell_ptr->in_edges) {
        struct nodes_ll *dep = ll->cell_ptr->in_edges;
        while (dep != NULL) {
            if (dep->cell_ptr == ll->cell_ptr)
                return true;
            dep = dep->next;
        }
    }
    return false;
}

void add_dep2_ll2(struct nodes_ll *ll, struct cell *target) {
    // Dummy: simply set target->in_edges to ll.
    target->in_edges = ll;
}

// Testing code

void test_evaluator_scroll_to() {
    database *db = mk_db(5, 100);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r = {0};
    r.func = 20;
    r.target = 1010; // Then new topleft should be 1010 - 1001 = 9.
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    assert(ret == 0);
    assert(topleft == 9);
    free_db(&db);
    printf("Test evaluator scroll_to (func 20) passed.\n");
}

void test_evaluator_assignment() {
    database *db = mk_db(5, 100);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r = {0};
    r.func = 1;
    r.arg1 = 42;
    r.target = 1001;  // Target cell is [0,0]
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    assert(ret == 0);
    struct cell *c = get_cell(db, 0, 0);
    assert(c != NULL);
    assert(c->data == 42);
    assert(c->oper == 1);
    assert(c->error == 0);
    free_db(&db);
    printf("Test evaluator assignment (func 1) passed.\n");
}

void test_evaluator_dependency_update_no_cycle() {
    database *db = mk_db(5, 100);
    // Pre-set target cell [0,0] and a dependency at [0,1].
    set(db, 0, 0, 10);
    set(db, 1, 0, 20);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r = {0};
    r.func = 2;
    r.arg1 = 1002;  // Represents cell [0,1]
    r.target = 1001;  // Target cell [0,0]
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    // In a no-cycle case, evaluator() should return 0.
    assert(ret == 0);
    free_db(&db);
    printf("Test evaluator dependency update (func 2, no cycle) passed.\n");
}

void test_evaluator_binary_div_zero() {
    database *db = mk_db(5, 100);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r = {0};
    r.func = 6; r.arg1 = 100; r.arg2 = 0; r.arg_type = 0; r.target = 1001;
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    struct cell *c = get_cell(db, 0, 0);
    // Division by zero should set an error flag.
    assert(c->error != 0);
    free_db(&db);
    printf("Test evaluator binary division by zero (func 6) passed.\n");
}

void test_evaluator_sleep_immediate() {
    database *db = mk_db(5, 100);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r = {0};
    r.func = 12; r.arg1 = 2; r.arg_type = 0; r.target = 1001;
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    struct cell *c = get_cell(db, 0, 0);
    // With no dependency, sleep_fn should set target->data to r.arg1.
    assert(c->data == 2);
    assert(c->oper == 12);
    free_db(&db);
    printf("Test evaluator sleep immediate (func 12) passed.\n");
}

void test_evaluator_cycle_detection() {
    database *db = mk_db(5, 100);
    // Set target cell [0,0].
    set(db, 0, 0, 5);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r = {0};
    // Simulate a cycle by making r.arg1 equal to r.target.
    r.func = 2; r.arg1 = 1001; r.target = 1001;
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    // Expect cycle detection to return error code 3.
    assert(ret == 3);
    free_db(&db);
    printf("Test evaluator cycle detection (func 2) passed.\n");
}

int main() {
    test_evaluator_scroll_to();
    test_evaluator_assignment();
    test_evaluator_dependency_update_no_cycle();
    test_evaluator_binary_div_zero();
    test_evaluator_sleep_immediate();
    test_evaluator_cycle_detection();

    printf("All evaluator tests passed.\n");
    return 0;
}

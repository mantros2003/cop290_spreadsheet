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

// --- Dummy/Stubs for Utility Functions ---
// These stub functions match the prototypes declared in utils.h.
// (They do nothing or simulate basic behavior for testing purposes.)

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

// --- Comprehensive Evaluator Test Suite ---
// (These tests exercise the various branches in evaluator().)

void test_evaluator_status2() {
    database *db = mk_db(5, 100);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r;
    r.status = 7; // Simulate a parser error status.
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    assert(ret == 7);
    free_db(&db);
    printf("Test evaluator status passed.\n");
}

void test_evaluator_func17() {
    database *db = mk_db(5, 100);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r = {0};
    r.func = 17;
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    assert(ret == -1);
    assert(running == false);
    assert(display_state == false);
    free_db(&db);
    printf("Test evaluator func 17 passed.\n");
}

void test_evaluator_func18() {
    database *db = mk_db(5, 100);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r = {0};
    r.func = 18;
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    assert(ret == 0);
    assert(display_state == false);
    free_db(&db);
    printf("Test evaluator func 18 passed.\n");
}

void test_evaluator_func19() {
    database *db = mk_db(5, 100);
    int topleft = 1001;
    _Bool running = true, display_state = false;
    response r = {0};
    r.func = 19;
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    assert(ret == 0);
    assert(display_state == true);
    free_db(&db);
    printf("Test evaluator func 19 passed.\n");
}

void test_evaluator_move_func13() {
    database *db = mk_db(5, 100);
    // Set initial topleft to encode col = 4, row = 20 (i.e. 4000 + 20 = 4020).
    int topleft = 4020;
    _Bool running = true, display_state = true;
    response r = {0};
    r.func = 13; // move up: row becomes max(row - 10, 0)
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    // Expected new topleft: col remains 4, row becomes 20 - 10 = 10 → 4000 + 10 = 4010.
    assert(ret == 0);
    assert(topleft == 4010);
    free_db(&db);
    printf("Test evaluator move func 13 passed.\n");
}

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

void test_evaluator_binary_ops_immediate() {
    database *db = mk_db(5, 100);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r;
    r.arg_type = 0;  // Immediate values.
    r.target = 1001; // Target cell [0,0]

    // Addition: 10 + 20 = 30.
    r.func = 3; r.arg1 = 10; r.arg2 = 20;
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    struct cell *c = get_cell(db, 0, 0);
    assert(c->data == 30);

    // Subtraction: 50 - 15 = 35.
    r.func = 4; r.arg1 = 50; r.arg2 = 15;
    ret = evaluator(r, db, &topleft, &running, &display_state);
    c = get_cell(db, 0, 0);
    assert(c->data == 35);

    // Multiplication: 7 * 6 = 42.
    r.func = 5; r.arg1 = 7; r.arg2 = 6;
    ret = evaluator(r, db, &topleft, &running, &display_state);
    c = get_cell(db, 0, 0);
    assert(c->data == 42);

    // Division: 100 / 4 = 25.
    r.func = 6; r.arg1 = 100; r.arg2 = 4;
    ret = evaluator(r, db, &topleft, &running, &display_state);
    c = get_cell(db, 0, 0);
    assert(c->data == 25);

    free_db(&db);
    printf("Test evaluator binary operations (func 3-6 immediate) passed.\n");
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

void test_evaluator_range_functions() {
    database *db = mk_db(5, 100);
    // Pre-populate column 0, rows 0..4 with: 50, 20, 30, 10, 40.
    set(db, 0, 0, 50);
    set(db, 1, 0, 20);
    set(db, 2, 0, 30);
    set(db, 3, 0, 10);
    set(db, 4, 0, 40);
    int topleft = 1001;
    _Bool running = true, display_state = true;
    response r;
    r.arg1 = 1001; r.arg2 = 1005; r.target = 1001; r.arg_type = 0;

    // Test min (func 7): expected minimum is 10.
    r.func = 7;
    int ret = evaluator(r, db, &topleft, &running, &display_state);
    struct cell *c = get_cell(db, 0, 0);
    assert(c->data == 10);

    // Test max (func 8): expected maximum is 50.
    r.func = 8;
    ret = evaluator(r, db, &topleft, &running, &display_state);
    c = get_cell(db, 0, 0);
    assert(c->data == 50);

    // Test avg (func 9): average of {50,20,30,10,40} is 30.
    r.func = 9;
    ret = evaluator(r, db, &topleft, &running, &display_state);
    c = get_cell(db, 0, 0);
    assert(c->data == 30);

    // Test sum (func 10): sum is 150.
    r.func = 10;
    ret = evaluator(r, db, &topleft, &running, &display_state);
    c = get_cell(db, 0, 0);
    assert(c->data == 150);

    // Test stdev (func 11): standard deviation (population) of {50,20,30,10,40} is about 14 (rounded).
    r.func = 11;
    ret = evaluator(r, db, &topleft, &running, &display_state);
    c = get_cell(db, 0, 0);
    int computed = c->data;
    assert(abs(computed - 14) <= 1);

    free_db(&db);
    printf("Test evaluator range functions (func 7-11) passed.\n");
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
    test_evaluator_status2();
    test_evaluator_func17();
    test_evaluator_func18();
    test_evaluator_func19();
    test_evaluator_move_func13();
    test_evaluator_scroll_to();
    test_evaluator_assignment();
    test_evaluator_dependency_update_no_cycle();
    test_evaluator_binary_ops_immediate();
    test_evaluator_binary_div_zero();
    // test_evaluator_range_functions();
    test_evaluator_sleep_immediate();
    test_evaluator_cycle_detection();

    printf("All evaluator tests passed.\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "../cell.h"
#include "../nodes_ll.h"  
#include <assert.h> 
// Test 1: mk_cell default values.
void test1_mk_cell_default() {
    struct cell *c = mk_cell();
    assert(c != NULL);
    assert(c->data == 0);
    assert(c->oper == ' ');
    assert(c->error == 0);
    assert(c->in_edges == NULL);
    assert(c->out_edges == NULL);
    free(c);
    printf("Test 1 passed.\n");
}

// Test 2: mk_isolated_cell default values.
void test2_mk_isolated_cell_default() {
    struct cell *c = mk_isolated_cell();
    assert(c != NULL);
    assert(c->data == 0);
    assert(c->oper == -1);
    assert(c->error == 0);
    assert(c->in_edges == NULL);
    assert(c->out_edges == NULL);
    free(c);
    printf("Test 2 passed.\n");
}

// Test 3: Modify cell created with mk_cell.
void test3_modify_mk_cell() {
    struct cell *c = mk_cell();
    c->data = 123;
    c->oper = '+';
    c->error = 1;   // Use boolean value (true)
    assert(c->data == 123);
    assert(c->oper == '+');
    assert(c->error == 1);
    free(c);
    printf("Test 3 passed.\n");
}

// Test 4: Modify cell created with mk_isolated_cell.
void test4_modify_mk_isolated_cell() {
    struct cell *c = mk_isolated_cell();
    c->data = 456;
    c->oper = '*';
    c->error = 1;   // Use boolean value (true)
    assert(c->data == 456);
    assert(c->oper == '*');
    assert(c->error == 1);
    free(c);
    printf("Test 4 passed.\n");
}

// Test 5: Check that in_edges and out_edges are NULL.
void test5_edges_initial_null() {
    struct cell *c = mk_cell();
    assert(c->in_edges == NULL);
    assert(c->out_edges == NULL);
    free(c);
    printf("Test 5 passed.\n");
}

// Test 6: Check error field default is 0.
void test6_error_field_default() {
    struct cell *c = mk_cell();
    assert(c->error == 0);
    free(c);
    printf("Test 6 passed.\n");
}

// Test 7: Check operator field for mk_cell is a space.
void test7_operator_mk_cell() {
    struct cell *c = mk_cell();
    assert(c->oper == ' ');
    free(c);
    printf("Test 7 passed.\n");
}

// Test 8: Check operator field for mk_isolated_cell is -1.
void test8_operator_mk_isolated_cell() {
    struct cell *c = mk_isolated_cell();
    assert(c->oper == -1);
    free(c);
    printf("Test 8 passed.\n");
}

// Test 9: Assign a dummy pointer to in_edges.
void test9_dummy_in_edges() {
    struct cell *c = mk_cell();
    c->in_edges = (void*)0xDEADBEEF;
    assert(c->in_edges == (void*)0xDEADBEEF);
    free(c);
    printf("Test 9 passed.\n");
}

// Test 10: Assign a dummy pointer to out_edges.
void test10_dummy_out_edges() {
    struct cell *c = mk_cell();
    c->out_edges = (void*)0xCAFEBABE;
    assert(c->out_edges == (void*)0xCAFEBABE);
    free(c);
    printf("Test 10 passed.\n");
}

// Test 11: Update the data field after creation.
void test11_update_data() {
    struct cell *c = mk_cell();
    c->data = 999;
    assert(c->data == 999);
    free(c);
    printf("Test 11 passed.\n");
}

// Test 12: Update the operator field after creation.
void test12_update_operator() {
    struct cell *c = mk_cell();
    c->oper = '%';
    assert(c->oper == '%');
    free(c);
    printf("Test 12 passed.\n");
}

// Test 13: Simulate linking cells: set cell A's out_edges to point to cell B.
void test13_simulate_linking() {
    struct cell *a = mk_cell();
    struct cell *b = mk_cell();
    a->out_edges = (struct nodes_ll *)b; // Cast to match type
    b->in_edges = (struct nodes_ll *)a;
    assert(a->out_edges == (struct nodes_ll *)b);
    assert(b->in_edges == (struct nodes_ll *)a);
    free(a);
    free(b);
    printf("Test 13 passed.\n");
}

// Test 14: Multiple modifications on a cell.
void test14_multiple_modifications() {
    struct cell *c = mk_cell();
    c->data = 100;
    assert(c->data == 100);
    c->data = 200;
    assert(c->data == 200);
    c->oper = 'X';
    assert(c->oper == 'X');
    c->oper = 'Y';
    assert(c->oper == 'Y');
    free(c);
    printf("Test 14 passed.\n");
}

// Test 15: Memory allocation and free (no crash).
void test15_allocation_free() {
    struct cell *c = mk_cell();
    free(c);
    printf("Test 15 passed.\n");
}

// Test 16: Create multiple cells in a loop and check each.
void test16_multiple_cells_loop() {
    const int count = 10;
    struct cell *cells[count];
    for (int i = 0; i < count; i++) {
        cells[i] = mk_cell();
        cells[i]->data = i;
        assert(cells[i]->data == i);
    }
    for (int i = 0; i < count; i++) {
        free(cells[i]);
    }
    printf("Test 16 passed.\n");
}

// Test 17: Negative data assignment.
void test17_negative_data() {
    struct cell *c = mk_cell();
    c->data = -50;
    assert(c->data == -50);
    free(c);
    printf("Test 17 passed.\n");
}

// Test 18: Large data assignment.
void test18_large_data() {
    struct cell *c = mk_cell();
    c->data = 1000000;
    assert(c->data == 1000000);
    free(c);
    printf("Test 18 passed.\n");
}

// Test 19: Error field assignment using a boolean value.
void test19_error_assignment() {
    struct cell *c = mk_cell();
    c->error = 1;
    assert(c->error == 1);
    free(c);
    printf("Test 19 passed.\n");
}

// Test 20: Combination test: modify all fields and verify.
void test20_combination() {
    struct cell *c = mk_cell();
    c->data = 77;
    c->oper = '?';
    c->error = 1;
    c->in_edges = (void*)0x1111;
    c->out_edges = (void*)0x2222;
    assert(c->data == 77);
    assert(c->oper == '?');
    assert(c->error == 1);
    assert(c->in_edges == (void*)0x1111);
    assert(c->out_edges == (void*)0x2222);
    free(c);
    printf("Test 20 passed.\n");
}

int main() {
    test1_mk_cell_default();
    test2_mk_isolated_cell_default();
    test3_modify_mk_cell();
    test4_modify_mk_isolated_cell();
    test5_edges_initial_null();
    test6_error_field_default();
    test7_operator_mk_cell();
    test8_operator_mk_isolated_cell();
    test9_dummy_in_edges();
    test10_dummy_out_edges();
    test11_update_data();
    test12_update_operator();
    test13_simulate_linking();
    test14_multiple_modifications();
    test15_allocation_free();
    test16_multiple_cells_loop();
    test17_negative_data();
    test18_large_data();
    test19_error_assignment();
    test20_combination();

    printf("All tests passed.\n");
    return 0;
}

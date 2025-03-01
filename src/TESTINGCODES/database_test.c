#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../database.h"
#include "../column.h"
#include "../cell.h"

// Test 1: Verify that mk_db() correctly allocates a database with given dimensions.
void test1_mk_db() {
    int num_cols = 3, num_rows = 100;
    database *db = mk_db(num_cols, num_rows);
    assert(db != NULL);
    assert(db->num_cols == num_cols);
    assert(db->num_rows == num_rows);
    // All column pointers should be NULL initially.
    for (int i = 0; i < num_cols; i++) {
        assert(db->cols[i] == NULL);
    }
    free_db(&db);
    assert(db == NULL);
    printf("Test 1 (mk_db) passed.\n");
}

// Test 2: Set and then get a single cell's data.
void test2_set_get_single() {
    int num_cols = 3, num_rows = 100;
    database *db = mk_db(num_cols, num_rows);
    int row = 10, col = 1;
    DATA value = 555;
    set(db, row, col, value);
    DATA retrieved = get(db, row, col);
    assert(retrieved == value);
    free_db(&db);
    printf("Test 2 (set/get single cell) passed.\n");
}

// Test 3: Retrieve the cell pointer using get_cell() and verify its data.
void test3_get_cell() {
    int num_cols = 3, num_rows = 100;
    database *db = mk_db(num_cols, num_rows);
    int row = 20, col = 2;
    DATA value = 777;
    set(db, row, col, value);
    struct cell *c = get_cell(db, col, row);
    assert(c != NULL);
    assert(c->data == value);
    free_db(&db);
    printf("Test 3 (get_cell) passed.\n");
}

// Test 4: Check the error flag using has_error(). Modify the cell's error field and verify.
void test4_has_error() {
    int num_cols = 3, num_rows = 100;
    database *db = mk_db(num_cols, num_rows);
    int row = 15, col = 0;
    set(db, row, col, 888);
    struct cell *c = get_cell(db, col, row);
    assert(c != NULL);
    // By default, error should be 0 (false).
    assert(has_error(db, row, col) == 0);
    // Now manually set error and check.
    c->error = 1;
    assert(has_error(db, row, col) == 1);
    free_db(&db);
    printf("Test 4 (has_error) passed.\n");
}

// Test 5: Set data in multiple cells across different columns and rows.
void test5_multiple_set() {
    int num_cols = 4, num_rows = 1000;
    database *db = mk_db(num_cols, num_rows);
    for (int col = 0; col < num_cols; col++) {
        for (int row = 0; row < 50; row += 10) {
            DATA value = row * col + 100;
            set(db, row, col, value);
            assert(get(db, row, col) == value);
        }
    }
    free_db(&db);
    printf("Test 5 (multiple set/get) passed.\n");
}

// Test 6: Verify that unset cells return the default value 0.
void test6_unset_cells() {
    int num_cols = 3, num_rows = 100;
    database *db = mk_db(num_cols, num_rows);
    for (int col = 0; col < num_cols; col++) {
        for (int row = 0; row < 20; row++) {
            // No data set; should return default value 0.
            assert(get(db, row, col) == 0);
        }
    }
    free_db(&db);
    printf("Test 6 (unset cells return 0) passed.\n");
}

// Test 7: Test setting data at a row index that lies beyond the first segment.
// Assumes SEGMENT_LENGTH is defined and used by set_data()/get_data().
void test7_segment_boundary() {
    int num_cols = 2, num_rows = 1000;
    database *db = mk_db(num_cols, num_rows);
    // Choose a row index in a later segment.
    int row = SEGMENT_LENGTH + 5;
    int col = 1;
    DATA value = 999;
    set(db, row, col, value);
    assert(get(db, row, col) == value);
    free_db(&db);
    printf("Test 7 (segment boundary) passed.\n");
}

int main() {
    test1_mk_db();
    test2_set_get_single();
    test3_get_cell();
    test4_has_error();
    test5_multiple_set();
    test6_unset_cells();
    test7_segment_boundary();
    printf("All database tests passed.\n");
    return 0;
}

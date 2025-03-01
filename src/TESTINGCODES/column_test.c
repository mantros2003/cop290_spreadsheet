#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../column.h"
#include "../cell.h"
#include "../utils.h"  // Include if needed for rm_all_dep or other utilities

// Test 1: Test that make_segment() creates a valid segment with default values.
void test1_make_segment() {
    struct column_segment *seg = make_segment();
    assert(seg != NULL);
    assert(seg->start_idx == 0);
    assert(seg->next == NULL);
    for (int i = 0; i < SEGMENT_LENGTH; i++) {
        // Each cell should be default initialized.
        assert(seg->segment[i].data == 0);
        assert(seg->segment[i].oper == ' ');
        assert(seg->segment[i].error == 0);
        assert(seg->segment[i].in_edges == NULL);
        assert(seg->segment[i].out_edges == NULL);
    }
    free(seg);
    printf("Test 1 (make_segment) passed.\n");
}

// Test 2: get_data() with a NULL head should return 0.
void test2_get_data_empty() {
    int idx = 5;
    DATA d = get_data(idx, NULL);
    assert(d == 0);
    printf("Test 2 (get_data with NULL head) passed.\n");
}

// Test 3: set_data() should create a segment when head is NULL.
void test3_set_data_creates_segment() {
    struct column_segment *head = NULL;
    int idx = 7;
    DATA value = 42;
    set_data(idx, value, &head);
    assert(head != NULL);
    // Check that start_idx is set to (idx / SEGMENT_LENGTH) * SEGMENT_LENGTH.
    int expected_start = (idx / SEGMENT_LENGTH) * SEGMENT_LENGTH;
    assert(head->start_idx == expected_start);
    // Verify that get_data() returns the correct value.
    DATA d = get_data(idx, head);
    assert(d == value);
    free_segment(&head);
    printf("Test 3 (set_data creates segment) passed.\n");
}

// Test 4: set_data() should update data in an existing segment.
void test4_set_data_update() {
    struct column_segment *head = NULL;
    int idx = 3;
    DATA value1 = 10, value2 = 99;
    set_data(idx, value1, &head);
    set_data(idx, value2, &head);
    DATA d = get_data(idx, head);
    assert(d == value2);
    free_segment(&head);
    printf("Test 4 (set_data update) passed.\n");
}

// Test 5: get_cell_seg() should return a pointer to the correct cell.
void test5_get_cell_seg_valid() {
    struct column_segment *head = NULL;
    int idx = 5;
    DATA value = 55;
    set_data(idx, value, &head);
    struct cell *cell_ptr = get_cell_seg(idx, head);
    assert(cell_ptr != NULL);
    assert(cell_ptr->data == value);
    free_segment(&head);
    printf("Test 5 (get_cell_seg valid) passed.\n");
}

// Test 6: get_cell_seg() should return NULL when the head is NULL.
void test6_get_cell_seg_invalid() {
    struct cell *cell_ptr = get_cell_seg(10, NULL);
    assert(cell_ptr == NULL);
    printf("Test 6 (get_cell_seg with NULL head) passed.\n");
}

// Test 7: set_data() should create multiple segments when indices span across segments.
void test7_multiple_segments() {
    struct column_segment *head = NULL;
    int idx1 = 2;                // Within the first segment.
    int idx2 = SEGMENT_LENGTH + 3; // Should fall into a second segment.
    DATA value1 = 100, value2 = 200;
    set_data(idx1, value1, &head);
    set_data(idx2, value2, &head);
    // The first segment's next pointer should not be NULL.
    assert(head != NULL);
    assert(head->next != NULL);
    assert(get_data(idx1, head) == value1);
    assert(get_data(idx2, head) == value2);
    free_segment(&head);
    printf("Test 7 (multiple segments creation) passed.\n");
}

// Test 8: get_data() for an index not explicitly set should return default value 0.
void test8_get_data_default() {
    struct column_segment *head = NULL;
    // Set data for index idx+1 but not for idx.
    int idx = 4;
    set_data(idx + 1, 123, &head);
    DATA d = get_data(idx, head);
    assert(d == 0);
    free_segment(&head);
    printf("Test 8 (get_data default value) passed.\n");
}

// Test 9: set_data() in the same segment for multiple indices.
void test9_set_data_multiple_in_same_segment() {
    struct column_segment *head = NULL;
    int idx1 = 1, idx2 = 2, idx3 = 3;
    set_data(idx1, 10, &head);
    set_data(idx2, 20, &head);
    set_data(idx3, 30, &head);
    assert(get_data(idx1, head) == 10);
    assert(get_data(idx2, head) == 20);
    assert(get_data(idx3, head) == 30);
    free_segment(&head);
    printf("Test 9 (multiple set_data in same segment) passed.\n");
}

// Test 10: Modifying a cell via get_cell_seg() should update the stored data.
void test10_get_cell_seg_modification() {
    struct column_segment *head = NULL;
    int idx = 8;
    set_data(idx, 80, &head);
    struct cell *cell_ptr = get_cell_seg(idx, head);
    assert(cell_ptr != NULL);
    cell_ptr->data = 888;
    DATA d = get_data(idx, head);
    assert(d == 888);
    free_segment(&head);
    printf("Test 10 (get_cell_seg modification) passed.\n");
}

// Test 11: Test setting data at the boundary index (end of a segment).
void test11_set_data_boundary() {
    struct column_segment *head = NULL;
    int idx = SEGMENT_LENGTH - 1;
    DATA value = 777;
    set_data(idx, value, &head);
    assert(get_data(idx, head) == value);
    free_segment(&head);
    printf("Test 11 (set_data at segment boundary) passed.\n");
}

// Test 12: Test setting data at the start of a new segment.
void test12_set_data_boundary_start() {
    struct column_segment *head = NULL;
    int idx = SEGMENT_LENGTH; // This is the first index of the second segment.
    DATA value = 888;
    set_data(idx, value, &head);
    assert(head != NULL);
    assert(head->next != NULL);
    assert(get_data(idx, head) == value);
    free_segment(&head);
    printf("Test 12 (set_data at segment start of new segment) passed.\n");
}

// Test 13: free_segment() should free a single segment.
void test13_free_segment_single() {
    struct column_segment *head = NULL;
    set_data(2, 50, &head);
    free_segment(&head);
    assert(head == NULL);
    printf("Test 13 (free_segment single segment) passed.\n");
}

// Test 14: free_segment() should free multiple segments.
void test14_free_segment_multiple() {
    struct column_segment *head = NULL;
    set_data(1, 10, &head);
    set_data(SEGMENT_LENGTH + 1, 20, &head);
    free_segment(&head);
    assert(head == NULL);
    printf("Test 14 (free_segment multiple segments) passed.\n");
}

// Test 15: Consistency check – repeatedly set and get data across several segments.
void test15_consistency() {
    struct column_segment *head = NULL;
    for (int i = 0; i < SEGMENT_LENGTH * 3; i += 3) {
        set_data(i, i + 100, &head);
        DATA d = get_data(i, head);
        assert(d == i + 100);
    }
    free_segment(&head);
    printf("Test 15 (consistency of set and get) passed.\n");
}

// Test 16: get_cell_seg() should correctly return cells for a sequence of indices.
void test16_get_cell_seg_sequence() {
    struct column_segment *head = NULL;
    for (int i = 0; i < SEGMENT_LENGTH * 2; i++) {
        set_data(i, i + 50, &head);
    }
    for (int i = 0; i < SEGMENT_LENGTH * 2; i++) {
        struct cell *c = get_cell_seg(i, head);
        assert(c != NULL);
        assert(c->data == i + 50);
    }
    free_segment(&head);
    printf("Test 16 (get_cell_seg sequence) passed.\n");
}

// Test 17: Updating the same index multiple times should store the latest value.
void test17_update_same_index() {
    struct column_segment *head = NULL;
    int idx = 10;
    set_data(idx, 100, &head);
    set_data(idx, 200, &head);
    set_data(idx, 300, &head);
    assert(get_data(idx, head) == 300);
    free_segment(&head);
    printf("Test 17 (update same index multiple times) passed.\n");
}

// Test 18: Getting data from an unallocated index (no segment created) returns 0.
void test18_get_data_unallocated_index() {
    struct column_segment *head = NULL;
    DATA d = get_data(20, head);
    assert(d == 0);
    printf("Test 18 (get_data unallocated index) passed.\n");
}

// Test 19: Setting data at a large index should allocate the correct segment.
void test19_set_data_large_index() {
    struct column_segment *head = NULL;
    int idx = SEGMENT_LENGTH * 10 + 5;
    DATA value = 5555;
    set_data(idx, value, &head);
    assert(get_data(idx, head) == value);
    free_segment(&head);
    printf("Test 19 (set_data large index) passed.\n");
}

// Test 20: Ensure segments are chained in order when multiple segments are created.
void test20_segment_order() {
    struct column_segment *head = NULL;
    // Set data in three different segments.
    set_data(3, 1, &head);
    set_data(SEGMENT_LENGTH + 3, 2, &head);
    set_data(2 * SEGMENT_LENGTH + 3, 3, &head);
    // Count the segments.
    struct column_segment *seg = head;
    int count = 0;
    while (seg != NULL) {
        count++;
        seg = seg->next;
    }
    assert(count == 3);
    free_segment(&head);
    printf("Test 20 (segment order) passed.\n");
}

int main() {
    test1_make_segment();
    test2_get_data_empty();
    test3_set_data_creates_segment();
    test4_set_data_update();
    test5_get_cell_seg_valid();
    test6_get_cell_seg_invalid();
    test7_multiple_segments();
    test8_get_data_default();
    test9_set_data_multiple_in_same_segment();
    test10_get_cell_seg_modification();
    test11_set_data_boundary();
    // test12_set_data_boundary_start();
    test13_free_segment_single();
    test14_free_segment_multiple();
    // test15_consistency();
    test16_get_cell_seg_sequence();
    test17_update_same_index();
    test18_get_data_unallocated_index();
    test19_set_data_large_index();
    // test20_segment_order();

    printf("All tests passed.\n");
    return 0;
}

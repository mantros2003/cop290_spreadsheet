#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../nodes_ll.h"
#include "../cell.h"

// Test 1: Verify that mk_ll() creates a valid empty list.
void test1_mk_ll() {
    struct nodes_ll *ll = mk_ll();
    assert(ll != NULL);
    assert(ll->cell_ptr == NULL);
    assert(ll->next == NULL);
    free_ll(&ll);
    assert(ll == NULL);
    printf("Test 1 (mk_ll) passed.\n");
}

// Test 2: Test add_node_end() on an initially empty list.
void test2_add_node_end_empty() {
    struct nodes_ll *ll = NULL;
    // Create a new node with a dummy cell.
    struct nodes_ll *node = mk_ll();
    struct cell *dummy_cell = mk_cell();
    dummy_cell->data = 101;
    node->cell_ptr = dummy_cell;

    add_node_end(&ll, &node);
    // The list should now have one node.
    assert(ll != NULL);
    assert(num_nodes(ll) == 1);
    assert(ll->cell_ptr == dummy_cell);
    free_ll(&ll);
    free(dummy_cell);
    printf("Test 2 (add_node_end on empty list) passed.\n");
}

// Test 3: Test add_node_end() by adding multiple nodes.
void test3_add_node_end_multiple() {
    struct nodes_ll *ll = NULL;
    const int count = 5;
    struct cell *cells[count];
    
    for (int i = 0; i < count; i++) {
        cells[i] = mk_cell();
        cells[i]->data = i * 10;  // Unique value for each cell.
        struct nodes_ll *node = mk_ll();
        node->cell_ptr = cells[i];
        add_node_end(&ll, &node);
    }
    assert(num_nodes(ll) == count);

    // Verify that the order of nodes matches the insertion order.
    struct nodes_ll *curr = ll;
    for (int i = 0; i < count; i++) {
        assert(curr != NULL);
        assert(curr->cell_ptr->data == i * 10);
        curr = curr->next;
    }
    
    free_ll(&ll);
    for (int i = 0; i < count; i++) {
        free(cells[i]);
    }
    printf("Test 3 (add_node_end multiple nodes) passed.\n");
}

// Test 4: Test rm_node_ll() by removing a node from the middle of the list.
void test4_rm_node_ll() {
    struct nodes_ll *ll = NULL;
    // Create three dummy cells.
    struct cell *cell1 = mk_cell(); cell1->data = 1;
    struct cell *cell2 = mk_cell(); cell2->data = 2;
    struct cell *cell3 = mk_cell(); cell3->data = 3;
    
    // Create and add three nodes.
    struct nodes_ll *node1 = mk_ll();
    node1->cell_ptr = cell1;
    add_node_end(&ll, &node1);
    
    struct nodes_ll *node2 = mk_ll();
    node2->cell_ptr = cell2;
    add_node_end(&ll, &node2);
    
    struct nodes_ll *node3 = mk_ll();
    node3->cell_ptr = cell3;
    add_node_end(&ll, &node3);
    
    // Verify that there are three nodes.
    assert(num_nodes(ll) == 3);
    
    // Remove the node that holds cell2.
    rm_node_ll(&ll, cell2);
    // After removal, the list should have two nodes.
    assert(num_nodes(ll) == 2);
    
    // Ensure that no node in the list points to cell2.
    struct nodes_ll *curr = ll;
    while (curr != NULL) {
        assert(curr->cell_ptr != cell2);
        curr = curr->next;
    }
    
    free_ll(&ll);
    free(cell1);
    free(cell2);
    free(cell3);
    printf("Test 4 (rm_node_ll) passed.\n");
}

// Test 5: Test copy_ll() by copying a list and verifying the copy.
void test5_copy_ll() {
    struct nodes_ll *ll = NULL;
    const int count = 3;
    struct cell *cells[count];
    
    // Create a list of nodes.
    for (int i = 0; i < count; i++) {
        cells[i] = mk_cell();
        cells[i]->data = i + 100;  // Unique value.
        struct nodes_ll *node = mk_ll();
        node->cell_ptr = cells[i];
        add_node_end(&ll, &node);
    }
    
    // Copy the linked list.
    struct nodes_ll *copy = copy_ll(ll);
    // Verify that both lists have the same number of nodes.
    assert(num_nodes(ll) == num_nodes(copy));
    
    // Verify that each corresponding node in the copy has the same cell pointer.
    struct nodes_ll *orig_curr = ll;
    struct nodes_ll *copy_curr = copy;
    while (orig_curr != NULL && copy_curr != NULL) {
        assert(orig_curr->cell_ptr == copy_curr->cell_ptr);
        orig_curr = orig_curr->next;
        copy_curr = copy_curr->next;
    }
    
    free_ll(&ll);
    free_ll(&copy);
    for (int i = 0; i < count; i++) {
        free(cells[i]);
    }
    printf("Test 5 (copy_ll) passed.\n");
}

int main() {
    test1_mk_ll();
    test2_add_node_end_empty();
    test3_add_node_end_multiple();
    test4_rm_node_ll();
    test5_copy_ll();
    printf("All nodes_ll tests passed.\n");
    return 0;
}

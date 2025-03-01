#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../hashset.h"
#include "../cell.h"  // Assumes this header provides the definition of struct cell and mk_cell()

int main(void) {
    // Test default_hash: for key 25 and table size 10, expect 25 % 10 = 5.
    int table_sz = 10;
    int hash_val = default_hash(25, table_sz);
    assert(hash_val == 25 % table_sz);
    
    // Create a hashset with default hash function (NULL passed, so default_hash is used)
    hashset *set = mk_hashset(NULL, table_sz);
    assert(set != NULL);
    assert(set->table_sz == table_sz);
    for (int i = 0; i < table_sz; i++) {
        assert(set->table[i] == NULL);
    }
    
    // Create dummy cell objects.
    struct cell *c1 = mk_cell();
    struct cell *c2 = mk_cell();
    struct cell *c3 = mk_cell();
    
    // Test insertion: Insert c1 with key 5.
    _Bool inserted = insert_hset(set, 5, c1);
    assert(inserted == 1);
    assert(in_hset(set, 5, c1) == 1);
    
    // Inserting c1 again with the same key should fail.
    inserted = insert_hset(set, 5, c1);
    assert(inserted == 0);
    
    // Test collisions: keys 5, 15, 25 should all hash to the same bucket if table_sz = 10.
    inserted = insert_hset(set, 15, c2);
    assert(inserted == 1);
    assert(in_hset(set, 15, c2) == 1);
    
    inserted = insert_hset(set, 25, c3);
    assert(inserted == 1);
    assert(in_hset(set, 25, c3) == 1);
    
    // Verify that the bucket (index computed from key 5) now contains a chain.
    int idx = default_hash(5, table_sz);
    assert(set->table[idx] != NULL);
    
    // Test removal: Remove c2 using key 15.
    _Bool removed = rm_hset(set, 15, c2);
    assert(removed == 1);
    assert(in_hset(set, 15, c2) == 0);
    
    // Removing c2 again should return 0.
    removed = rm_hset(set, 15, c2);
    assert(removed == 0);
    
    // Remove c1 and c3.
    removed = rm_hset(set, 5, c1);
    assert(removed == 1);
    assert(in_hset(set, 5, c1) == 0);
    
    removed = rm_hset(set, 25, c3);
    assert(removed == 1);
    assert(in_hset(set, 25, c3) == 0);
    
    // At this point, the bucket should be empty.
    assert(set->table[idx] == NULL);
    
    // Free the hashset.
    free_hset(&set);
    
    // Free the dummy cell objects (hashset functions do not free cells).
    free(c1);
    free(c2);
    free(c3);
    
    printf("All hashset tests passed.\n");
    return 0;
}

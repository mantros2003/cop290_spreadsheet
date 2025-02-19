#include "hashset.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Default  hash function that computes table modulo table size.
 */
int default_hash(long key, int table_sz) {
  return key % table_sz;
}

/*
 * Makes a hashset with table_sz size and sets its hashing function to hash_fn or default_hash if hash_fn is NULL
 * Collsion is handled using chaining
 */
hashset *mk_hashset(int (*hash_fn)(long, int), int table_sz) {
  hashset *set = malloc(sizeof(hashset));

  if (set == NULL) return NULL;

  set->table_sz = table_sz;
  set->hash_fn = hash_fn ? hash_fn : default_hash;
  set->table = malloc(table_sz * sizeof(hashnode*));

  for (int i = 0; i < set->table_sz; i++) {
    set->table[i] = NULL;
  }

  return set;
}

/*
 * Checks if cell val's pointer is already in hashset
 */
_Bool in_hset(hashset *set, long key, struct cell *val) {
  int idx = set->hash_fn(key, (long) set->table_sz);

  hashnode *head = set->table[idx];
  while (head != NULL) {
    if (head->val == val) return 1;

    head = head->next;
  }

  return 0;
}

/*
 * Inserts val's pointer to the hashset
 * Returns 0 if its already in it, else returns 1
 */
_Bool insert_hset(hashset *set, long key, struct cell *val) {
  if (in_hset(set, key, val)) return 0;

  hashnode* new_node = malloc(sizeof(hashnode));
  new_node->val = val;

  int idx = set->hash_fn(key, (long) set->table_sz);

  new_node->next = set->table[idx];
  set->table[idx] = new_node;

  return 1;
}

/*
 * Removes val's pointer from the hashset and also frees the malloc
 * If not in hashset, returns 0 else 1
 */
_Bool rm_hset(hashset *set, long key, struct cell *val) {
  if (!in_hset(set, key, val)) return 0;

  int idx = set->hash_fn(key, (long) set->table_sz);

  hashnode *curr = set->table[idx];
  hashnode *prev = NULL;

  while (curr != NULL) {
    if (curr->val == val) break;

    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL) return 1;

  if (prev == NULL) set->table[idx] = curr->next;
  else prev->next = curr->next;

  free(curr);

  return 1;
}

/*
 * Frees the linked list pointed by hashnode
 */
void free_hnode(hashnode **node){
  hashnode *curr = *node, *temp = NULL;

  while (curr != NULL) {
    temp = curr->next;
    free(curr);
    curr = temp;
  }

  *node = NULL;
}

/*
 * Frees the memory allocated for each hashnode linked list, then frees set->table, then the hashset
 */
void free_hset(hashset** set) {
  for (int i = 0; i < (*set)->table_sz; i++) {
    if ((*set)->table[i] != NULL) {
      free_hnode(&((*set)->table[i]));
    }
  }

  free(*set);
}

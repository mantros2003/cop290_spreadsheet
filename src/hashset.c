#include "hashset.h"
#include <stdio.h>
#include <stdlib.h>

int default_hash(long int key, int table_sz) {
  return key % table_sz;
}

hashset *mk_hashset(int (*hash_fn)(long int, int), int table_sz) {
  hashset *set = malloc(sizeof(hashset));

  if (set == NULL) return NULL;

  set->table_sz = table_sz;
  set->hash_fn = hash_fn ? hash_fn : default_hash;
  set->table = malloc(table_sz * sizeof(hashnode));

  for (int i = 0; i < set->table_sz; i++) {
    set->table[i] = NULL;
  }

  return set;
}

_Bool in_hset(hashset *set, long int key, struct cell *val) {
  int idx = set->hash_fn(key, (long) set->table_sz);

  hashnode *head = set->table[idx];
  while (head != NULL) {
    if (head->val == val) return 1;

    head = head->next;
  }

  return 0;
}

_Bool insert_hset(hashset *set, long int key, struct cell *val) {
  if (in_hset(set, key, val)) return 0;

  hashnode* new_node = malloc(sizeof(hashnode));
  new_node->val = val;

  int idx = set->hash_fn(key, (long) set->table_sz);

  new_node->next = set->table[idx];
  set->table[idx] = new_node;

  return 1;
}

_Bool rm_hset(hashset *set, long key, struct cell *val) {
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

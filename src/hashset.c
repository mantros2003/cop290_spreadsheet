#include <stdio.h>
#include <stdlib.h>

#define HASHTABLE_SIZE 10007

typedef struct hashnode {
  struct cell *val;
  hashnode *next;
} hashnode;

typedef struct hashset {
  int hashtable_size;
  hashnode **table;
  int (*hash_fn)(int, int);
} hashset;

hashset *mk_hashset(int (*hash_fn)(int, int), int table_sz) {
  hashset *set = malloc(sizeof(hashset));

  if (set == NULL) return NULL;

  set->hashtable_size = table_sz;
  set->hash_fn = hash_fn;
  set->table = malloc(table_sz * sizeof(hashnode));

  for (int i = 0; i < set->table_sz; i++) {
    set->table[i] = NULL;
  }

  return set;
}

_Bool insert_hset(hashset *set, int key, struct cell *val) {
  if (in_hset(hashset *set, int key, struct cell *val)) return 1;

  hashnode* new_node = malloc(sizeof(hashnode));
  new_node->val = val;

  int idx = set->hash_fn(key, set->table_sz);

  new_node->next = set->table[i];
  set->table[i] = new_node;
}

_Bool in_hset(hashset *set, int key, struct cell *val) {
  int idx = set->hash_fn(key, set->table_sz);

  hashnode *head = set->table[idx];
  while (head != NULL) {
    if (head->val == val) return 1;

    head = head->next;
  }

  return 0;
}

_Bool rm_hset(hashset *set, int key, struct cell *val) {
  int idx = set->hash_fn(key, set->table_sz);

  hashnode *curr = set->table[idx];
  hashnode *prev = NULL;

  while (head != NULL) {
    if (head->val == val) break;

    prev = head;
    head = head->next;
  }

  if (head == NULL) return 1;

  if (prev == NULL) set->table[idx] = curr->next;
  else prev->next = curr->next;

  free(curr);
}

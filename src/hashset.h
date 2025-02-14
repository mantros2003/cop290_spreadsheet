#ifndef HASHSET_H
#define HASHSET_H

#define HASHTABLE_SIZE 10007

typedef struct hashnode {
  struct cell *val;
  struct hashnode *next;
} hashnode;

typedef struct hashset {
  int table_sz;
  hashnode **table;
  int (*hash_fn)(long int, int);
} hashset;

int default_hash(long, int);

hashset *mk_hashset(int (*)(long, int), int);

_Bool in_hset(hashset*, long, struct cell*);

_Bool insert_hset(hashset*, long, struct cell*);

_Bool insert_hset(hashset*, long, struct cell*);

#endif // HASHSET_H

#ifndef UTILS_H_
#define UTILS_H_

#include "hashset.h"
#include "database.h"

struct cell;

void get_ip(char*, int);

void add_dep(struct cell*, struct cell*, char);

void add_dependency(database*, int, int, char);

void add_dep_range(database*, int, int, int, char);

void add_dep_ll(struct nodes_ll*, struct cell*);

void rm_all_dep(struct cell*);

struct nodes_ll *dfs_ud(struct cell*, hashset*, struct nodes_ll*);

struct nodes_ll *dfs_d(struct cell*, hashset*, struct nodes_ll*);

struct nodes_ll *connected_component(struct cell*);

_Bool traverse(struct cell*, hashset*, hashset*);

_Bool contains_cycle(struct nodes_ll *component);

struct nodes_ll *topo_sort(struct cell*);

_Bool cell_in_range(database*, int);

void free_isolated_cells(struct nodes_ll*);

#endif //UTILS_H_
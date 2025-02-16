#ifndef DATABASE_H_
#define DATABASE_H_

#define DATA int

#include "column.h"

/*
* Struct for database struct
*/
typedef struct {
  int num_cols;
  struct column_segment **cols;
} database;

database *mk_db(int);

void set(database*, int, int, DATA);

DATA get(database*, int, int);

struct column_segment *get_column(database*, int);

struct cell *get_cell(database*, int, int);

void free_db(database **sb);

#endif // DATABASE_H_

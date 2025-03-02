#include "database.h"
#include "column.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Make a new database struct and set all pointers to NULL
 */
database* mk_db(int num_cols, int num_rows) {
  database *db = malloc(sizeof(database));
  db->num_cols = num_cols;
  db->num_rows = num_rows;
  db->cols = malloc(sizeof(struct column_segment*) * num_cols);
  for (int i = 0; i < num_cols; i++) (db->cols)[i] = NULL;
  return db;
}

/*
 * Sets the data at a particular [r, c]
 */
void set(database *db, int row, int col, DATA data) {
  set_data(row, data, &((db->cols)[col]));
}

/*
 * Gets the data from [r, v]
 */
DATA get(database *db, int row, int col) {
  if ((db->cols)[col] == NULL) return 0;

  return get_data(row, (db->cols)[col]);
}

/*
 * Returns a pointer to head of column at index col
 */
struct column_segment *get_column(database *db, int col) {
  return (db->cols)[col];
}

/*
 * Returns the pointer to cell located at [row, col]
 */
struct cell *get_cell(database *db, int col, int row) {
  struct column_segment *column = get_column(db, col);

  if (column == NULL) return NULL;

  return get_cell_seg(row, column);
}

_Bool has_error(database *db, int row, int col) {
  struct cell *c = get_cell(db, col, row);

  if (c == NULL) return 0;

  return c->error;
}

/*
 * Helper function to free the memory
 */
void free_db(database **db) {
  for (int i = 0; i < (*db)->num_cols; i++) free_segment(&((*db)->cols[i]));
 
  free((*db)->cols);
  free(*db);
  *db = NULL;
}


// int main() {
//   int num_cols = 10;
//   database *db = mk_db(num_cols, 100);
//   for (int col = 0; col < num_cols - 1; col++) {
//     for (int row = 0; row < 500; row += 50) {
//       set(db, row, col, row * col + 1);
//     }
//   }

//   for (int col = 0; col < num_cols; col++) {
//     for (int row = 0; row < 500; row ++) {
//       printf("[%d, %d]:\t%d\n", row, col, get(db, row, col));
//     }
//   }
  
//   printf("%d\n", get(db, 0, 1));

//   free_db(&db);

//   printf("%d\n", get(db, 0, 1));

//   return 0;
// }

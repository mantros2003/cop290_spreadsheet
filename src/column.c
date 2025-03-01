#include "column.h"
#include "cell.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * Function that creates a new column segment and returns its head pointer
 */
struct column_segment* make_segment() {
  struct column_segment *seg = malloc(sizeof(struct column_segment));
  seg->start_idx = 0;
  seg->next = NULL;
  for (int i = 0; i < SEGMENT_LENGTH; i++) {
    (seg->segment)[i].data = 0;
    (seg->segment)[i].oper = ' ';
    (seg->segment)[i].error = 0;
    (seg->segment)[i].in_edges = NULL;
    (seg->segment)[i].out_edges = NULL;
  }

  return seg;
}

/*
 * Function to retrieve data from the storage structure, column_segment.
*/
DATA get_data(int idx, struct column_segment *head) {
  // Need to ensure that wherever we are invoking this function, idx is in range, i.e. less than the user defined num_rows.
  while (head != NULL && (idx < head->start_idx || idx >= head->start_idx + SEGMENT_LENGTH)) {
    head = head->next;
  }

  // The case when the segment where data should be is not initialized, i.e. contains default value 0
  if (head == NULL) return 0;

  return (head->segment)[idx % SEGMENT_LENGTH].data;
}

/*
 * Function to place data into the storage structure.
 * If the segment for idx is not initialized it will dynamically allocate memory.
 */
void set_data(int idx, DATA data, struct column_segment **head) {
  // Need to ensure that idx is not out of bounds wherever the function is being used
  // Checking if head pointer is NULL, then check if the current segment has idx
  struct column_segment *prev = NULL;
  while (*head != NULL && (idx < (*head)->start_idx || idx >= (*head)->start_idx + SEGMENT_LENGTH)) {
    prev = *head;
    head = &((*head)->next);
  }

  // The case when this column is being used for the first time so the head pointer itself is NULL
  // or the case when the segment for idx is not initialised
  if (*head == NULL) {
    *head = make_segment();
    (*head)->start_idx = (idx / SEGMENT_LENGTH) * SEGMENT_LENGTH;

    // prev pointer is NULL when the initial head pointer is NULL, i.e. the column is not iniitialized
    if (prev != NULL) prev->next = *head;
  }
  
  ((*head)->segment)[idx % SEGMENT_LENGTH].data = data;
}

/*
 * Returns pointer to the cell corresponding to the row
 */
struct cell *get_cell_seg(int row, struct column_segment *head) {
  while (head != NULL && (row < head->start_idx || row >= head->start_idx + SEGMENT_LENGTH)) head = head->next;

  if (head != NULL) return &((head->segment)[row % SEGMENT_LENGTH]);

  // The segment for cell is not initialized
  return NULL;
}

/*
 * Function to free the dynamically allocated storage segments
 */
void free_segment(struct column_segment **head) {
  struct column_segment *curr = *head;      // Pointer to the head of column segment struct to be freed
  struct column_segment *next_ptr;          // Pointer to store the next pointer value

  while (curr != NULL) {
    // First we free all isolated cells in the segment, then remove all dependencies
    for (int i = 0; i < SEGMENT_LENGTH; i++) {
      free_isolated_cells((curr->segment[i]).in_edges);
      rm_all_dep(&(curr->segment[i]));
    }

    next_ptr = curr->next;
    free(curr);
    curr = next_ptr;
  }

  // To handle dangling pointers
  *head = NULL;
}

/*
 * Function to print the data stored in the entire column after the head pointer
 */
void print_column(struct column_segment *head) {
  while (head != NULL) {
    for (int i = 0; i < SEGMENT_LENGTH; i++) printf("%d\t", get_data(i, head));
    head = head->next;
  }
  printf("\n");
}

/*
int main() {
  int num_cols = 5;
  struct column_segment* store[num_cols];

  printf("Size of storage: %lu bytes\n", sizeof(store));
  printf("size of struct: %lu bytes\n", sizeof(struct column_segment));

  for (int i = 0; i < num_cols; i++) {
    store[i] = NULL;

    printf("Set struct reference for index %d to NULL\n", i);

    for (int j = 0; j < 2 * SEGMENT_LENGTH; j++) {
      printf("Adding at %d %d\t", i, j);

      set_data(j, i + j, &store[i]);

      printf("Data at [%d, %d]: %d\n", i, j, get_data(j, store[i]));
    }
    // printf("Column %d", i + 1);
  }

  for (int i = 0; i < num_cols; i++) {
    printf("currently in segment %d\n", i);
    struct column_segment *curr = store[i];
    while (curr != NULL) {
      printf("current pointer: %p\n", (void*)curr);
      curr = curr->next;
    }
  }

  
  for (int i = 0; i< num_cols; i ++) free_segment(&store[i]);
  return 0;
}
*/
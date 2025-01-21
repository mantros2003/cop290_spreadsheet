#include<stdio.h>
#include<stdlib.h>

#define SEGMENT_LENGTH 100

/*
 * A segment of column to store data of size SEGMENT_LENGTH. Modeled as a linked list
 * to save memory while initializing.
 */
struct column_segment {
  int start_idx;                  // The first index stored in this segment
  int segment[SEGMENT_LENGTH];    // To store data, change it to struct for adding dependencies
  struct column_segment *next;    // Link to the next storage block
};

/*
 * Function to retrieve data from the storage structure, column_segment.
 */
int get_data(int idx, struct column_segment *head) {
  // Need to ensure that wherever we are invoking this function, idx is in range, i.e. less than the user defined num_rows.
  while (idx < head->start_idx || idx >= head->start_idx + SEGMENT_LENGTH) {
    head = head->next;
  }

  return (head->segment)[idx % SEGMENT_LENGTH];
}

/*
 * Function to place data into the storage structure.
 * If the segment for idx is not initialized it will dynamically allocate memory.
 */
int set_data(int idx, int data, struct column_segment **head) {
  // Need to ensure that idx is not out of bounds wherever the function is being used
  // The case when this column is being used for the first time so the head pointer itself is NULL
  if (*head == NULL) {
    struct column_segment *seg = malloc(sizeof(struct column_segment));
    seg->start_idx = (idx / SEGMENT_LENGTH) * SEGMENT_LENGTH;
    seg->next = NULL;

    *head = seg;
  }

  // Checking if the current segment has idx
  while (idx < (*head)->start_idx || idx >= (*head)->start_idx + SEGMENT_LENGTH) {
    // Code to handle the case when the segment for idx is not initialised
    if ((*head)->next == NULL) {
      struct column_segment *seg = malloc(sizeof(struct column_segment));
      seg->start_idx = (idx / SEGMENT_LENGTH) * SEGMENT_LENGTH;
      seg->next = NULL;

      (*head)->next = seg;
    }

    head = &((*head)->next);
  }
  
  ((*head)->segment)[idx % SEGMENT_LENGTH] = data;
  return 0;
}

/*
 * Function to free the dynamically allocated storage segments
 */
void free_segment(struct column_segment **head) {
  struct column_segment *curr = *head;      // Pointer to the head of column segment struct to be freed
  struct column_segment *next_ptr;          // Pointer to store the next pointer value

  while (curr != NULL) {
    next_ptr = curr->next;
    free(curr);
    curr = next_ptr;
  }

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

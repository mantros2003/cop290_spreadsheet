#ifndef COLUMN_H_
#define COLUMN_H_

#define SEGMENT_LENGTH 100

#include "cell.h"

struct cell;

/*
 * A segment of column to store data of size SEGMENT_LENGTH. Modeled as a linked list
 * to save memory while initializing.
 */
struct column_segment {
  int start_idx;                            // The first index stored in this segment
  struct cell segment[SEGMENT_LENGTH];      // To store data
  struct column_segment *next;              // Link to the next storage block
};

struct column_segment* make_segment();

int get_data(int idx, struct column_segment *head);

int set_data(int idx, int data, struct column_segment **head);

void free_segment(struct column_segment **head);

void print_column(struct column_segment *head);

#endif // COLUMN_H_

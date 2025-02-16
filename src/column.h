#ifndef COLUMN_H_
#define COLUMN_H_

#define SEGMENT_LENGTH 100
#define DATA int

#include "cell.h"

struct cell;

/*
 * A segment of column to store data of size SEGMENT_LENGTH. Modeled as a linked list
 * to save memory while initializing.
 */
struct column_segment {
  struct cell segment[SEGMENT_LENGTH];      // To store data
  struct column_segment *next;              // Link to the next storage block
  int start_idx;                            // The first index stored in this segment
};

struct column_segment* make_segment();

DATA get_data(int idx, struct column_segment *head);

void set_data(int idx, DATA data, struct column_segment **head);

struct cell *get_cell_seg(int, struct column_segment*);

void free_segment(struct column_segment **head);

void print_column(struct column_segment *head);

#endif // COLUMN_H_

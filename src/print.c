#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define CELL_WIDTH 12
#define MAX_ROWS 10
#define MAX_COLS 10

void generate_column_label(int col_index, char *label) {
    int i = 0;
    while (col_index >= 0) {
        label[i++] = 'A' + (col_index % 26);
        col_index /= 26;
        col_index--;
    }
    label[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = label[j];
        label[j] = label[i - j - 1];
        label[i - j - 1] = temp;
    }
}

void print_spreadsheet(database *db, int top_left_cell) {
    if (!db) {
        fprintf(stderr, "Invalid database pointer.\n");
        return;
    }

    int rows = db->num_rows;
    int cols = db->num_cols;

    int top_left_col = top_left_cell / 1000;
    int top_left_row = top_left_cell % 1000;

    int available_rows = rows - top_left_row;
    int available_cols = cols - top_left_col;

    rows = (available_rows < MAX_ROWS) ? available_rows : MAX_ROWS;
    cols = (available_cols < MAX_COLS) ? available_cols : MAX_COLS;

    if (rows <= 0 || cols <= 0) {
        fprintf(stderr, "No cells to display.\n");
        return;
    }
    
    char col_label[4];

    // Print column labels
    printf("     ");
    for (int j = 0; j < cols; j++) {
        generate_column_label(top_left_col + j, col_label);
        printf("%*s", CELL_WIDTH, col_label);
    }
    printf("\n");

    // Print rows with labels and values
    for (int i = 0; i < rows; i++) {
        printf("%3d  ", top_left_row + i + 1);

        for (int j = 0; j < cols; j++) {
            if (has_error(db, top_left_row + i, top_left_col + j)) {
                printf("%*s", CELL_WIDTH, "Err!");
            } else {
                int cell_value = get(db, top_left_row + i, top_left_col + j);
                printf("%*d", CELL_WIDTH, cell_value);
            }
        }
        printf("\n");
    }
}

// int main() {
//     // Example database initialization (same as before)
//     database db;
//     db.num_rows = 15;
//     db.num_cols = 30;

//     db.data = (int **)malloc(db.num_rows * sizeof(int *));
//     for (int i = 0; i < db.num_rows; i++) {
//         db.data[i] = (int *)malloc(db.num_cols * sizeof(int));
//         for (int j = 0; j < db.num_cols; j++) {
//             db.data[i][j] = (i + 1) * 1000 + (j + 1);
//         }
//     }

//     int top_left_cell = 1002;

//     print_spreadsheet(&db, top_left_cell); // No need to pass rows and cols

//     // Free the allocated memory for db.data (same as before)
//     for (int i = 0; i < db.num_rows; i++) {
//         free(db.data[i]);
//     }
//     free(db.data);

//     return 0;
// }
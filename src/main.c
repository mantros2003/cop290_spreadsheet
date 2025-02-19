#include "database.h"
#include "utils.h"          // Make utils.h
#include "_parser.h"        // Make parser.h
#include "print.h"
#include "evaluator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXROWS 999
#define MAXCOLS 18278
#define BUFFERSIZE 256

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Exactly 2 int arguments required\n");
        return 1;
    }

    static int num_rows, num_cols;
    num_rows = atoi(argv[1]);
    num_cols = atoi(argv[2]);

    if (num_rows < pow(10, strlen(argv[1]) - 1) || num_cols < pow(10, strlen(argv[2]) - 1)) {
        printf("Invalid parameters\n");
        return 1;
    }

    if (num_rows <= 0 || num_rows > MAXROWS || num_cols <= 0 || num_cols > MAXCOLS) {
        printf("Values too large\n");
        return 1;
    }

    int topleft_cell = 0;
    _Bool display_state = 1, running = 1;
    char buff[BUFFERSIZE];
    char *status_msg[10] = {"ok", "Bad Input", "Invalid range", "Cycle detected"};

    database *db = mk_db(num_cols, num_rows);

    print_spreadsheet(db, topleft_cell);
    printf("[0.0] (ok) > ");

    while (running) {
        get_ip(buff, BUFFERSIZE);

        time_t _start = time(NULL);
        response r = parse(buff);
        int status = evaluator(r, db, &topleft_cell, &display_state, &running);
        time_t _finish = time(NULL);

        if (status == -1) continue;

        if (display_state) print_spreadsheet(db, topleft_cell);

        printf("[%.1ld] ", _finish - _start);
        printf("(%s) > ", status_msg[status]);
    }

    free_db(&db);

    return 0;
}
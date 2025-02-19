#ifndef EVALUATOR_H_
#define EVALUATOR_H_

struct response;
struct database;

void evaluate(struct cell*);

void sleep_fn(struct cell*);

void max_fn(struct cell*);

void min_fn(struct cell*);

void avg_fn(struct cell*);

void sum_fn(struct cell*);

void stdev_fn(struct cell*);

int evaluator(response, database*, int*, _Bool*, _Bool*);

#endif //EVALUATOR_H_
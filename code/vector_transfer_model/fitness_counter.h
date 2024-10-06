#ifndef FITNESS_COUNTER_H
#define FITNESS_COUNTER_H

float calc_pythagoras(struct vec3 *analyzed_solution, struct vec3 *goal);
float calc_fitness(struct robot_organism *robot);
struct robot_organism **rank_population(struct population *population);

#endif // FITNESS_COUNTER_H

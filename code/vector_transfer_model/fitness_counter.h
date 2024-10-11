#ifndef FITNESS_COUNTER_H
#define FITNESS_COUNTER_H

float calculate_distance(struct vec3 pos1, struct vec3 pos2);
int compare_fitness(const void *a, const void *b);
float calc_fitness(struct robot_organism *robot);
struct robot_organism **rank_population(struct population *population);

#endif // FITNESS_COUNTER_H

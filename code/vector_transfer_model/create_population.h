#ifndef CREATE_POPULATION_H
#define CREATE_POPULATION_H

struct robot_organism *create_robot_not_inherited_organism();
struct population *create_not_inherited_population();
struct robot_organism *create_robot_inherited_organism(struct robot_organism *parentA, struct robot_organism *parentB);
struct population *create_inherited_population(struct robot_organism *parents[10]);

#endif // CREATE_POPULATION_H

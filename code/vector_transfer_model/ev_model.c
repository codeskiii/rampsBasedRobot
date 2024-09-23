#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.c"

/*
<param name="min" type="int">
   The minimum value.
</param>
<param name="max" type="int">
    The maximum value.
</param>
<returns>
    A random number between min and max.
</returns>
*/
int rd_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

/*
<param name="max" type="float">
    The maximum value.
</param>
<returns>
    A random number between 0 and max.
</returns>
*/
float *rd_float(float max) {
    float result = ((float)rand() / (float)RAND_MAX) * max;
    return &result;
}

/*
<returns>
    A new robot organism.
</returns>
*/
struct robot_organism *create_robot_not_inherited_organism() {
    struct robot_organism *currentRobot = malloc(sizeof(struct robot_organism));
    if (currentRobot == NULL) {
        return NULL;
    }

    currentRobot->goal = (struct vec3) {rd_int(-10, 10), rd_int(0, 10), rd_int(-10, 10)};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            currentRobot->wages[i][j] = rd_float(1.0);
        }
    }
    return currentRobot;
}

/*
<returns>
    A new population.
</returns>
*/
struct population *create_not_inherited_population() {
    srand(time(NULL));
    struct population *currentPopulation = malloc(sizeof(struct population));
    if (currentPopulation == NULL) {
        return NULL;
    }

    for (int i = 0; i < 100; i++) {
        currentPopulation->collector[i] = create_robot_not_inherited_organism();
    }
    return currentPopulation;
}

struct robot_organism *create_robot_inherited_organism(struct robot_organism *parentA,
                                                      struct robot_organism *parentB) {

    struct robot_organism *childRobot = malloc(sizeof(struct robot_organism));
    if (childRobot == NULL) {
        return NULL;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            childRobot->wages[i][j] = malloc(sizeof(float));
            *(childRobot->wages[i][j]) = (*(parentA->wages[i][j]) + *(parentB->wages[i][j])) / 2.0;
        }
    }

    return childRobot;
}

struct population *create_inherited_population(struct population *parent) {
    // srand(time(NULL));
    struct population *currentPopulation = malloc(sizeof(struct population));
    for (int i = 0; i < 10; i++) {
        for (int i = 0; i < 9; i++) {
            currentPopulation->collector[i] = create_robot_inherited_organism(parent->collector[i],
                                                                                parent->collector[i + 1]);
        }
    }
}

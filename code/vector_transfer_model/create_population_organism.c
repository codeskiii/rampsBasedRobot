#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "helpers.h"
#include "create_population.h"

/*
<returns>
    A new robot organism.
</returns>
*/
struct robot_organism *create_robot_not_inherited_organism() {
    struct robot_organism *currentRobot = (struct robot_organism*)malloc(sizeof(struct robot_organism));
    if (currentRobot == NULL) {
        printf("Error: Failed to allocate memory for currentRobot\n");
        return NULL;
    }

    currentRobot->goal = (struct vec3) {rd_int(-10, 10), rd_int(0, 10), rd_int(-10, 10)};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            *(currentRobot->wages[i][j]) = rd_float(0.8, 1.2);
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
    struct population *currentPopulation = (struct population*)malloc(sizeof(struct population));
    if (currentPopulation == NULL) {
        printf("Error: Failed to allocate memory for currentPopulation\n");
        return NULL;
    }

    for (int i = 0; i < 10; i++) {
        for (int i = 0; i < 9; i++) {
            currentPopulation->collector[i] = create_robot_not_inherited_organism();
        }
    }
    return currentPopulation;
}

/*
<param name="parentA" type="struct robot_organism *">
    The first parent.
</param>
<param name="parentB" type="struct robot_organism *">
    The second parent.
</param>
<returns>
    A new robot organism.
*/
struct robot_organism *create_robot_inherited_organism(struct robot_organism *parentA,
                                                      struct robot_organism *parentB) {
    struct robot_organism *childRobot = (struct robot_organism*)malloc(sizeof(struct robot_organism));
    if (childRobot == NULL) {
        printf("Error: Failed to allocate memory for childRobot\n");
        return NULL;
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            childRobot->wages[i][j] = (float*)malloc(sizeof(float));
            *(childRobot->wages[i][j]) = (*(parentA->wages[i][j]) + *(parentB->wages[i][j])) / 2.0;
        }
    }

    return childRobot;
}   

/*
<param name="parent" type="struct population *">
    The parent.
</param>
<returns>
    A new population.
</returns>
*/
struct population *create_inherited_population(struct robot_organism *parents[10]) {
    // srand(time(NULL));
    struct population *currentPopulation = (struct population*)malloc(sizeof(struct population));
    if (currentPopulation == NULL) {
        printf("Error: Failed to allocate memory for currentPopulation\n");
        return NULL;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            currentPopulation->collector[i * 9 + j] = create_robot_inherited_organism(parents[i], parents[(i + 1) % 10]);
        }
    }

    return currentPopulation;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "helpers.h"
#include "create_population.h"
#include "mutation.h"

void free_population(struct population *pop) {
    if (pop == NULL) return; 
    free(pop);
}
/*
<returns>
    A new robot organism.
</returns>
*/
struct robot_organism create_robot_not_inherited_organism() {
    //printf("allocating memory for organism\n");
    struct robot_organism *currentRobot = malloc(sizeof(struct robot_organism));
    if (currentRobot == NULL){
        printf("ERROR: create_robot_not_inherited_organism");
    }
    //printf("memory allocated\n");

    //printf("setting goal\n");
    currentRobot->goal = (struct vec3){rd_int(-10, 10), rd_int(0, 10), rd_int(-10, 10)};
    
    //printf("initializing wages\n");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            //printf("wage %d %d \n", i, j);
            currentRobot->wages[i][j] = (rd_float(0.8, 1.2)); // 
            //printf("wage inited\n");
            //fflush(stdout);
        }
    }

    return *currentRobot;
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

    for (int j = 0; j < 100; j++) {
            //printf("init of organism\n");
            currentPopulation->collector[j] = create_robot_not_inherited_organism();
            //printf("organism no. %d \n", j);
        }
    return currentPopulation;
}

/*
<param name="parentA" type="struct robot_organism *">
    The first parent.
</param>
<param name="parentB" type="struct robot_organism *">
    The second parent.
</returns>
    A new robot organism.
*/
struct robot_organism create_robot_inherited_organism(struct robot_organism *parentA,
                                                      struct robot_organism *parentB) {
    struct robot_organism *childRobot = (struct robot_organism*)malloc(sizeof(struct robot_organism));
    if (childRobot == NULL) {
        printf("ERROR: create_robot_inherited_organism");
        exit(1);
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            // Krzyżowanie
            if (rd_float(0, 1) < 0.5) {
                childRobot->wages[i][j] = parentA->wages[i][j];
            } else {
                childRobot->wages[i][j] = parentB->wages[i][j];
            }
        }
    }


    if (rd_float(0, 1) < 0.1) { 
        childRobot = mutate(childRobot);
    }

    return *childRobot;
}   

/*
<param name="parent" type="struct population *">
    The parent.
</param>
<returns>
    A new population.
</returns>
*/
struct population *create_inherited_population(struct robot_organism **parents) {
    struct population *currentPopulation = malloc(sizeof(struct population));
    if (currentPopulation == NULL) {
        fprintf(stderr, "ERROR: create_inherited_population\n");
        return NULL;
    }

    for (int i = 0; i < 100; i++) {
        int parentA_index = rand() % 10;
        int parentB_index;
        do {
            parentB_index = rand() % 10;
        } while (parentB_index == parentA_index);

        currentPopulation->collector[i] = create_robot_inherited_organism(parents[parentA_index],
                                                                          parents[parentB_index]);
    }

    return currentPopulation;
}

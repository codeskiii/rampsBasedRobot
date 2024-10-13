#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "helpers.h"
#include "create_population.h"
#include "mutation.h"

#define MEMWATCH 
#define MW_STDIO 

#include "memwatch.h"

#define WAGE_SIZE 12

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
    struct robot_organism currentRobot;
    currentRobot.goal = (struct vec3){rd_int(-20, 20), rd_int(-10, 10), rd_int(-20, 20)};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < WAGE_SIZE; j++) {
            currentRobot.wages[i][j] = rd_float(-2.0, 2.0);
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
    //srand(time(NULL));
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
    struct robot_organism childRobot; // Zmiana: obiekt zamiast wskaźnika

    // Uzupełnij wages dla childRobot na podstawie rodziców
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < WAGE_SIZE; j++) {
            float randomValue = rd_float(0, 1);
            if (randomValue < 0.9) {
                if (parentA->fitness > parentB->fitness) {
                    childRobot.wages[i][j] = (parentA->wages[i][j] * 9.0f + parentB->wages[i][j]) / 10.0f;
                } else {
                    childRobot.wages[i][j] = (parentA->wages[i][j] + parentB->wages[i][j] * 9.0f) / 10.0f;
                }
            } else {
                if (randomValue < 0.95) {
                    childRobot.wages[i][j] = (parentA->wages[i][j] * 2.0f + parentB->wages[i][j]) / 3.0f;
                } else {
                    childRobot.wages[i][j] = (parentA->wages[i][j] + parentB->wages[i][j] * 2.0f) / 3.0f;
                }
            }
        }
    }

    // Potencjalna mutacja
    if (rd_float(0, 1) < 0.1) {
        childRobot = mutate(childRobot); // Zastosuj mutację
    }

    return childRobot; // Zwróć obiekt dziecka
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
        //printf("Creating inherited object %d\n", i);
        currentPopulation->collector[i] = (create_robot_inherited_organism(parents[parentA_index],
                                                                          parents[parentB_index]));
    }

    return currentPopulation;
}

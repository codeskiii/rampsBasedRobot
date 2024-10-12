#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "create_population.h"

#define MAX_NO_CHANGE_STRAK 100

int count_not_diversed_streak (struct robot_organism **top_ranked)  {
    struct robot_organism top_organism_1 = *(top_ranked[0]);
    struct robot_organism top_organism_3 = *(top_ranked[1]);

    int output;
    
    if (fabs(top_organism_1.fitness - top_organism_3.fitness) >= 0.1 * top_organism_1.fitness) {
       output = 1;
    }
    else {
        output = 0;
    }
    return output;
}

struct robot_organism **fast_roll(struct robot_organism **top_ranked) {
    struct robot_organism **new_top_ranked = malloc(10 * sizeof(struct robot_organism*));

    for (int i = 0; i < 8; i++) {
        new_top_ranked[i] = top_ranked[i]; 
    }

    for (int i = 8; i < 10; i++) {
        new_top_ranked[i] = malloc(sizeof(struct robot_organism));

        *new_top_ranked[i] = create_robot_not_inherited_organism();
    }

    return new_top_ranked;
}

struct robot_organism **roll_them(struct robot_organism **top_ranked) {
    struct robot_organism **new_top_ranked = malloc(10 * sizeof(struct robot_organism*));

    int j = 9;

    for (int i = 0; i < 5; i++) {
        new_top_ranked[2 * i] = top_ranked[i];

        new_top_ranked[2 * i + 1] = top_ranked[j];
        j--;
    }

    return new_top_ranked;
}

int compare(const void *a, const void *b) {
    struct robot_organism *robotA = *(struct robot_organism **)a;
    struct robot_organism *robotB = *(struct robot_organism **)b;
    if (robotA->fitness < robotB->fitness) return -1;
    if (robotA->fitness > robotB->fitness) return 1;
    return 0;
}

struct robot_organism **sort_them(struct robot_organism **A, struct robot_organism **B) {
    // Allocate memory for the new array that will hold both A and B elements
    struct robot_organism **new_top_ranked = malloc(20 * sizeof(struct robot_organism*));
    
    // Copy elements from A and B to new_top_ranked
    for (int i = 0; i < 10; i++) {
        new_top_ranked[i] = A[i];
        new_top_ranked[10 + i] = B[i];
    }

    // Sort the combined array based on fitness
    qsort(new_top_ranked, 20, sizeof(struct robot_organism*), compare);

    // Return the sorted array
    return new_top_ranked;
}
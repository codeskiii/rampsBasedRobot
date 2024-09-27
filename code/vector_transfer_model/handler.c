#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.c"
#include "create_population_organism.c"

void run() {
    struct population *population = create_not_inherited_population();
    float epochs = 1000;

    for (int i = 0; i < epochs; i++) {
        printf("Start of epoch no: %d\n", i);
        struct population *predicted_population = predict_on_wages(population);

        // rank population
        struct robot_organism *top_ranked[10] = rank_population(population);

        // create new population
        population = create_inherited_population(top_ranked);
    }

    printf("END DEBUG\n");
}

int main() {
    run();
    return 0;
}
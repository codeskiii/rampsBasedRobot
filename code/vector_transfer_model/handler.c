#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "create_population.h"
#include "helpers.h"
#include "fitness_counter.h"
#include "vec6_to_vec3.h"
#include "predict_on_wages.h"

/*
<description>
    The main function to run the gentic algorithm.
</description>
*/
void run() {
    struct population *population = create_not_inherited_population();
    float epochs = 1000;

    for (int i = 0; i < epochs; i++) {
        printf("Start of epoch no: %d\n", i);
        predict_on_wages(population);

        // rank population
        struct robot_organism *top_ranked = rank_population(population);
        // create new population
        population = create_inherited_population(top_ranked);
    }

    printf("END DEBUG\n");
}

int main() {
    run();
    return 0;
}
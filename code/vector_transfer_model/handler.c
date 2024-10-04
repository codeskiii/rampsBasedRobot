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
    printf("init first population\n");
    fflush(stdout);
    struct population *population = create_not_inherited_population();
    float epochs = 1000;

    printf("end\n");

    printf("Start of training");
    for (int i = 0; i < epochs; i++) {
        printf("Start of epoch no: %d\n", i);
        fflush(stdout);

        printf("Predicting");
        fflush(stdout);
        predict_on_wages(population);

        // rank population
        printf("Ranking");
        fflush(stdout);
        struct robot_organism *top_ranked = rank_population((population));
        // create new population
        printf("Creating new population");
        fflush(stdout);
        population = create_inherited_population(top_ranked);
        
        printf("End of epoch");
        fflush(stdout);
    }

    printf("END\n");
    fflush(stdout);
}

int main() {
    printf("starting");
    fflush(stdout);
    run();
    return 0;
}
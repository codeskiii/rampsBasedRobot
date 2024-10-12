#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "create_population.h"
#include "helpers.h"
#include "fitness_counter.h"
#include "vec6_to_vec3.h"
#include "predict_on_wages.h"
#include "fast_quit.h"

#define MAX_NOT_DIVERSED 100

/*
<description>
    The main function to run the gentic algorithm.
</description>
*/
void run() {
    srand(time(NULL));
    
    printf("init first population\n");
    fflush(stdout);
    struct population *population = create_not_inherited_population();
    printf("end\n");
    float epochs = 100000;
    int not_diversed_strak = 0;

    printf("Start of training\n");
    for (int i = 0; i < epochs; i++) {
        printf("Start of epoch no: %d\n", i);
        fflush(stdout);

        // Predict on the current population's wages
        //printf("Predicting\n");
        predict_on_wages(population);

        // Rank population
        //printf("Ranking\n");
        struct robot_organism **top_ranked = rank_population((population));

        not_diversed_strak += count_not_diversed_streak(top_ranked);
        //if (not_diversed_strak >= MAX_NOT_DIVERSED){
        //    not_diversed_strak = 0;
        //    printf("Fast Roll...");
            top_ranked = fast_roll(top_ranked);
        //}

        // Print the high score for debugging/logging purposes
        //printf("High score\n");
        print_high_score(top_ranked);

        // Create a new population based on top-ranked individuals
        //printf("New population\n");
        struct population *new_population = create_inherited_population(top_ranked);

        // Free the old population before replacing it
        free_population(population);

        // Replace the old population with the new one
        population = new_population;
    }

    // Free the final population after the training is complete
    free_population(population);

    printf("END\n");
    fflush(stdout);
}

int main() {
    printf("starting\n");
    fflush(stdout);
    run();
    return 0;
}
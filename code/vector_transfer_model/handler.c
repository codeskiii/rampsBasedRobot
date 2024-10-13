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

#define MEMWATCH 
#define MW_STDIO 

#include "memwatch.h"

#define MAX_NOT_DIVERSED 50

/*
<description>
    The main function to run the gentic algorithm.
</description>
*/
void run() {
    srand(time(NULL));

    printf("init first population\n");
    fflush(stdout);
    
    struct population *population = create_not_inherited_population(); // Tworzenie pierwszej populacji
    printf("end\n");
    
    float epochs = 1000000000;
    int not_diversed_strak = 0;

    struct robot_organism **rolled_top_ranked;
    struct robot_organism **mine_saver;
    struct robot_organism **top_ranked;
    struct population *new_population;

    top_ranked = rank_population(population);
    mine_saver = rank_population(population);  // Ranking pierwszej populacji
    new_population = create_inherited_population(mine_saver);

    printf("Start of training\n");
    for (int i = 0; i < epochs; i++) {
        printf("Start of epoch no: %d\n", i);
        fflush(stdout);

        // Predict on the current population's wages
        //printf("Predicting\n");
        predict_on_wages(population);  // Przewidywanie

        // Rank population
        //printf("Ranking\n");
        top_ranked = rank_population(population);  // Ranking nowej populacji

        //printf("Not diversed stuff\n");
        not_diversed_strak += count_not_diversed_streak(top_ranked);
        if (not_diversed_strak >= MAX_NOT_DIVERSED) {
            not_diversed_strak = 0;
            printf("sort_them...\n");
            mine_saver = sort_them(mine_saver, top_ranked);
            top_ranked = mine_saver;
        }

        //printf("Fast rolling\n");
        top_ranked = fast_roll(top_ranked);  // Aktualizacja tablicy wskaźników

        // Print the high score for debugging/logging purposes
        print_high_score(top_ranked);
        print_high_score(mine_saver);

        // Create a new population based on top-ranked individuals
        //printf("Creating inherited population\n");
        new_population = create_inherited_population(mine_saver);

        // Free the old population before replacing it
        //printf("Freeing inherited population\n");
        free_population(population);  // Zwalnianie starej populacji
        population = new_population;  // Zastąpienie starą nową populacją

        // Zwalnianie dynamicznie alokowanych tablic wskaźników
        //printf("Freeing top_ranked");
        free(top_ranked);  // Zwalnianie `top_ranked`, który już nie będzie potrzebny
        //printf("Does this shit breaks here?\n");
    }

    // Free the final population after the training is complete
    free_population(population);  // Zwalnianie końcowej populacji

    printf("END\n");
    fflush(stdout);
}

int main() {
    printf("starting\n");
    fflush(stdout);
    run();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "create_population.h"

#define MAX_NO_CHANGE_STRAK 100

int count_not_diversed_streak (struct robot_organism **top_ranked)  {
    struct robot_organism top_organism_1 = *(top_ranked[0]);
    struct robot_organism top_organism_3 = *(top_ranked[2]);

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
    // Alokacja dynamiczna pamięci na 10 wskaźników do struktur robot_organism
    struct robot_organism **new_top_ranked = malloc(10 * sizeof(struct robot_organism*));

    // Skopiowanie pierwszych 6 elementów z top_ranked do new_top_ranked
    for (int i = 0; i < 6; i++) {
        new_top_ranked[i] = top_ranked[i];  // Kopiowanie wskaźników, nie tworzymy nowych obiektów
    }

    // Tworzenie 4 nowych obiektów robot_organism i umieszczanie ich w new_top_ranked od indeksu 6 do 9
    for (int i = 6; i < 10; i++) {
        // Alokacja pamięci dla nowego obiektu robot_organism
        new_top_ranked[i] = malloc(sizeof(struct robot_organism));

        // Inicjalizacja nowego obiektu za pomocą funkcji create_robot_not_inherited_organism()
        *new_top_ranked[i] = create_robot_not_inherited_organism();
    }

    // Zwrócenie nowej tablicy
    return new_top_ranked;
}
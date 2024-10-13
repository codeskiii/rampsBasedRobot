#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include "structs.h"
#include "helpers.h"

#define WAGE_SIZE 12
#define WAGE_MATRIX_SIZE 6

#define WAGE_MUT_PROB 0.45       
#define MUTATION_PROBABILITY 0.6  
#define MUTATION_RANGE_LOW 0.8
#define MUTATION_RANGE_HIGH 1.2

#define MIN_WAGE_VALUE -1000.0      
#define MAX_WAGE_VALUE 1000.0         

#define MEMWATCH 
#define MW_STDIO 

#include "memwatch.h"

/*
<param name="robot" type="struct robot_organism *">
    The robot to mutate.
</param>
<returns>
    The mutated robot.
*/
struct robot_organism mutate(struct robot_organism robot) {
    //if (robot == NULL) {
    //    fprintf(stderr, "ERROR: Null pointer passed to mutate\n");
    //    return NULL;  // Zwracamy NULL w przypadku błędu
    //}

    for (int i = 0; i < WAGE_MATRIX_SIZE; i++) {
        if (rd_float(0, 1) < MUTATION_PROBABILITY) {
            for (int j = 0; j < WAGE_SIZE; j++) {
                if (rd_float(0, 1) < WAGE_MUT_PROB) {
                    float mutationFactor = rd_float(MUTATION_RANGE_LOW, MUTATION_RANGE_HIGH);
                    if (rd_float(0, 1) < 0.5) {
                        robot.wages[i][j] *= mutationFactor;
                    } else {
                        robot.wages[i][j] += rd_float(-0.2, 0.2);
                    }

                    // Sprawdzanie NaN i Inf
                    if (isnan(robot.wages[i][j]) || isinf(robot.wages[i][j])) {
                        robot.wages[i][j] = FLT_MAX;  // Ustalamy wartość na maksymalną
                    }

                    // Ograniczenie wartości do zdefiniowanych granic
                    if (robot.wages[i][j] < MIN_WAGE_VALUE) {
                        robot.wages[i][j] = MIN_WAGE_VALUE;
                    }
                    if (robot.wages[i][j] > MAX_WAGE_VALUE) {
                        robot.wages[i][j] = MAX_WAGE_VALUE;
                    }
                }
            }
        }
    }
    return robot;
}
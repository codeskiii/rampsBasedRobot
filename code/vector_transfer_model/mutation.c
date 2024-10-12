#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "helpers.h"

#define WAGE_SIZE 12
#define WAGE_MATRIX_SIZE 6

#define WAGE_MUT_PROB 0.45       
#define MUTATION_PROBABILITY 0.6  
#define MUTATION_RANGE_LOW 0.8
#define MUTATION_RANGE_HIGH 1.2

#define MIN_WAGE_VALUE -2.0       
#define MAX_WAGE_VALUE 2.0         

/*
<param name="robot" type="struct robot_organism *">
    The robot to mutate.
</param>
<returns>
    The mutated robot.
*/
struct robot_organism *mutate(struct robot_organism *robot) {
    for (int i = 0; i < WAGE_MATRIX_SIZE; i++) {
        if (rd_float(0, 1) < MUTATION_PROBABILITY) {
            for (int j = 0; j < WAGE_SIZE; j++) {
                if (rd_float(0, 1) < WAGE_MUT_PROB) {
                    if (rd_float(0, 1) < 0.5) {
                        robot->wages[i][j] *= rd_float(MUTATION_RANGE_LOW, MUTATION_RANGE_HIGH);
                    } else {
                        robot->wages[i][j] += rd_float(-0.2, 0.2);
                    }
                    
                    if (robot->wages[i][j] < MIN_WAGE_VALUE) {
                        robot->wages[i][j] = MIN_WAGE_VALUE;
                    }
                    if (robot->wages[i][j] > MAX_WAGE_VALUE) {
                        robot->wages[i][j] = MAX_WAGE_VALUE;
                    }
                }
            }
        }
    }
    return robot;
}
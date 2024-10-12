#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "helpers.h"

#define WAGE_SIZE 12

#define WAGE_MUT_PROB 0.3

/*
<param name="robot" type="struct robot_organism *">
    The robot to mutate.
</param>
<returns>
    The mutated robot.
*/
struct robot_organism *mutate(struct robot_organism *robot) {
    //printf("MUTATION \n");
    for (int i = 0; i < 6; i++) {
        if ((rd_float(0, 1) < WAGE_MUT_PROB))
        for (int j = 0; j < WAGE_SIZE; j++) {
            robot->wages[i][j] *= rd_float(0.7, 1.3);
        }
    }
    return robot;
}
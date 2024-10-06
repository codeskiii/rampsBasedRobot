#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "helpers.h"

/*
<param name="robot" type="struct robot_organism *">
    The robot to mutate.
</param>
<returns>
    The mutated robot.
*/
struct robot_organism *mutate(struct robot_organism *robot) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            robot->wages[i][j] *= rd_float(0.7, 1.3);
        }
    }
    return robot;
}

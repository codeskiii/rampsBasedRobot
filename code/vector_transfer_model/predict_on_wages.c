#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.c"

// TO DO
float calculate_wages(float base, float *wages[6]) {
    
}

/*
<param name="robot" type="struct robot_organism *">
    The robot with any wages.
</param>
<returns>
    The prediction.
</returns>
*/
struct vec6 make_predictions_on_wages(struct robot_organism *robot) {
    struct vec6 *result = malloc(sizeof(struct vec6));
    if (result == NULL) {
        printf("Error: Failed to allocate memory for result\n");
        return (struct vec6) {0, 0, 0, 0, 0, 0};
    }

    struct vec3 *goal_vector = &robot->goal; 

    for (int i = 0; i < 6; i++) {
        for (int k = 0; k < 3; k++) {
            result->degree[i] = calculate_wages(goal_vector->degree[k], robot->wages[i]);   
        }
    }
}

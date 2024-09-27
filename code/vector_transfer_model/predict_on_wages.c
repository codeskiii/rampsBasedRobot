#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"

/*
<param name="base" type="float">
    The X value
</param>
<param name="wages" type="float *">
    wages for prediction making
</param> 
*/

float calculate_wages(float base, float *wages[6]) {
    /*
    X ** W_1 + X * W_2 ... = y
    */
   float result = 0;
   for (int i = 0; i < 6; i++) {
        result += powf(base, *wages[i]);
   }

   return result;
}

/*
<param name="robot" type="struct robot_organism *">
    The robot with any wages.
</param>
<returns>
    The prediction of vec6 wich is the question.
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
        float cup_holder = 0; 
        for (int k = 0; k < 3; k++) {
            cup_holder += calculate_wages(goal_vector->degree[k], robot->wages[i]);
        }
        result->degree[i] = cup_holder;
    }
    return *result;
}

/*
<param name="population" type="struct population *">
    The population of the robots.
</param>
<returns>
    The new population of the robots.
</returns>
*/
void predict_on_wages(struct population *population) {
    for (int i = 0; i < 100; i++) {
        struct robot_organism *robot = population->collector[i];
        robot->solution = make_predictions_on_wages(robot);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "predict_on_wages.h"
#include <float.h> 

#define WAGE_SIZE 6
#define GOAL_SIZE 3

/*
<param name="base" type="float">
    The X value
</param>
<param name="wages" type="float *">
    wages for prediction making
</param> 
*/

float calculate_wages(float base, float *wages) {
    /*
    X ** W_1 + X * W_2 ... = y
    */
   float result = 0.0f;
   for (int i = 0; i < WAGE_SIZE; i++) {
        result += powf(base, wages[i]);
   }
   return result;
}

/*
<param name="robot" type="struct robot_organism *">
    The robot with any wages.
</param>
<returns>
    The prediction of vec6 which is the question.
</returns>
*/
struct vec6 make_predictions_on_wages(struct robot_organism *robot) {
    struct vec6 result;
    struct vec3 *goal_vector = &robot->goal; 

    for (int i = 0; i < WAGE_SIZE; i++) {
        float cup_holder = 0.0f;
        for (int k = 0; k < GOAL_SIZE; k++) {
            cup_holder += calculate_wages(goal_vector->degree[k], robot->wages[i]);
        }

        if (isinf(cup_holder)) {
            cup_holder = FLT_MAX; // Ustaw jako FLT_MAX, gdy cup_holder jest nieskończonością
        }

        result.degree[i] = cup_holder;
        //printf("cupHolder: %f", cup_holder);
    }
    return result;
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
        struct robot_organism *robot = &population->collector[i];
        robot->solution = make_predictions_on_wages(robot);
    }
}
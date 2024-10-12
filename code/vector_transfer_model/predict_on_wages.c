#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "predict_on_wages.h"
#include <float.h> 
#include "fitness_counter.h"

#define WAGE_SIZE 12
#define ROBOT_SIZE 6
#define GOAL_SIZE 3

/*
<param name="base" type="float">
    The X value
</param>
<param name="wages" type="float *">
    wages for prediction making
</param> 
*/

float calculate_wages(struct vec3 *goal, float *wages) {
    /*
    X ** W_1 + X * W_2 ... = y
    */
   float result = 0.0f;

    for (int i = 0; i < GOAL_SIZE; i++) {
        float uw = 0.0f;
        for (int j = 0; j < WAGE_SIZE; j++) {
            uw += goal->degree[i] * wages[j];
        }
        result += uw;
    }

    if (isnan(result) || isinf(result)) {
        result = FLT_MAX;
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
    struct vec6 *result = (struct vec6*)malloc(sizeof(struct vec6));
    // TO RETHINK THIS SHIT:
    //struct vec3 *goal_vector = &robot->goal; 

    for (int i = 0; i < ROBOT_SIZE; i++) {
        float cup_holder = calculate_wages(&(robot->goal), robot->wages[i]);
        //printf("Wage: %d \n", i);

        //printf("calc wages\n");
        //for (int k = 0; k < GOAL_SIZE; k++) {
        //    cup_holder += calculate_wages(goal_vector->degree[k], robot->wages[i]);
        //      printf("Wage calculated: %f\n", cup_holder);
        //}

        if (isinf(cup_holder)) {
            //printf("Infinite cup_holder encountered, setting to FLT_MAX\n");
            cup_holder = FLT_MAX; // max float when cup_holder = inf
        }

        result->degree[i] = cup_holder;
        //printf("Finish\n");
        //printf("cupHolder: %f", cup_holder);
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
        //printf("Organism: %d \n", i);
        struct robot_organism *robot = &population->collector[i];
        robot->solution = make_predictions_on_wages(robot);
    }
}
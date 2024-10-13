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
#define POPULATION_SIZE 100

#define MEMWATCH 
#define MW_STDIO 

#include "memwatch.h"

/*
<param name="goal" type="struct vec3 *">
    Goal vector (target for the robot).
</param>
<param name="wages" type="float *">
    Wages for prediction.
</param> 
*/
float calculate_wages(struct vec3 *goal, float *wages) {
    float result = 0.0f;
    for (int i = 0; i < GOAL_SIZE; i++) {
        result += goal->degree[i] * wages[i];  
    }

    if (isnan(result) || isinf(result)) {
        result = FLT_MAX;
    }

    return result;
}

/*
<param name="robot" type="struct robot_organism *">
    The robot with wages.
</param>
<returns>
    The prediction vector (vec6).
</returns>
*/
struct vec6 make_predictions_on_wages(struct robot_organism *robot) {
    struct vec6 result; 
    for (int i = 0; i < ROBOT_SIZE; i++) {
        float cup_holder = calculate_wages(&(robot->goal), robot->wages[i]);

        if (isnan(cup_holder) || isinf(cup_holder) || isinf(cup_holder)) {
            cup_holder = FLT_MAX;
        }

        result.degree[i] = cup_holder;
    }
    return result;
}

/*
<param name="population" type="struct population *">
    The population of robots.
</param>
*/
void predict_on_wages(struct population *population) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        struct robot_organism *robot = &population->collector[i];
        robot->solution = make_predictions_on_wages(robot);
    }
}
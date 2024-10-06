#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "vec6_to_vec3.h"
#include "helpers.h"
#include "fitness_counter.h"

/*
<param name="analyzed_solution" type="struct vec3 *">
    The analyzed solution.
</param>
<param name="goal" type="struct vec3 *">
    The goal.
</param>
<returns>
    The distance between the analyzed solution and the goal.
*/
float cacl_pythagoras(struct vec3 *analyzed_solution, struct vec3 *goal) {
    float x_distance = (analyzed_solution->degree[0] - goal->degree[0]) * (analyzed_solution->degree[0] - goal->degree[0]);
    float y_distance = (analyzed_solution->degree[1] - goal->degree[1]) * (analyzed_solution->degree[1] - goal->degree[1]);
    float z_distance = (analyzed_solution->degree[2] - goal->degree[2]) * (analyzed_solution->degree[2] - goal->degree[2]);

    return sqrtf(x_distance + y_distance + z_distance);
}

/*
<param name="robot" type="struct robot_organism *">
    The robot with any fitness.
</param>
<returns>
    The fitness of the robot.
*/
float calc_fitness(struct robot_organism *robot) {
    float result;

    struct vec3 *analyzed_solution = vec6_to_vec3(&(robot->solution));
    float distance = cacl_pythagoras(analyzed_solution, &(robot->goal));

    result = 1.0f / distance;

    free(analyzed_solution);

    return result;
}

/*
<param name="population" type="struct population *">
    The population of the robots.
</param>
<returns>
    The top 10 robots with the highest fitness.
*/
struct robot_organism **rank_population(struct population *population) {
    struct robot_organism **top_ranked = malloc(10 * sizeof(struct robot_organism *));

    for (int i = 0; i < 10; i++) {
        top_ranked[i] = &(population->collector[i]);
    }

    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (calc_fitness(top_ranked[i]) < calc_fitness(top_ranked[j])) {
                struct robot_organism *temp = top_ranked[i];
                top_ranked[i] = top_ranked[j];
                top_ranked[j] = temp;
            }
        }
    }

    for (int i = 10; i < 100; i++) {
        float fitness = calc_fitness(&(population->collector[i]));
        if (fitness > calc_fitness(top_ranked[9])) {
            top_ranked[9] = &(population->collector[i]);

            for (int j = 8; j >= 0 && calc_fitness(top_ranked[j]) < fitness; j--) {
                struct robot_organism *temp = top_ranked[j];
                top_ranked[j] = top_ranked[j + 1];
                top_ranked[j + 1] = temp;
            }
        }
    }

    return top_ranked;
}

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

    struct vec3 *analyzed_solution = vec6_to_vec3(&robot->solution);
    float distance = cacl_pythagoras(analyzed_solution, &robot->goal);

    // standaryzation
    result = 1 / distance;

    return result;
}

/*
<param name="population" type="struct population *">
    The population of the robots.
</param>
<returns>
    The top 10 robots with the highest fitness.
*/
struct robot_organism *rank_population(struct population *population) {
    struct robot_organism *top_ranked = malloc(sizeof(struct robot_organism *) * 10);

    for (int i = 0; i < 10; i++) {
        float fitness = calc_fitness(population->collector[i]);
        top_ranked[i] = *(population->collector[i]);
    }

    for (int i = 10; i < 100; i++) {
        float fitness = calc_fitness(population->collector[i]);
        // Complexity:
        // O(n * 10) => O(population_size * top_size)
        for (int j = 0; j < 10; j++) {
            if (fitness > calc_fitness(&(top_ranked[j]))) {
                for (int k = 9; k > j; k--) {
                    top_ranked[k] = top_ranked[k - 1];
                }
                top_ranked[j] = *(population->collector[i]);
                break;
            }
        }
    }

    return top_ranked;
}

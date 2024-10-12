#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>
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
float calculate_distance(struct vec3 pos1, struct vec3 pos2) {
    float dx = powf(pos1.degree[0] - pos2.degree[0] ,2);
    float dy = powf(pos1.degree[1] - pos2.degree[1], 2);
    float dz = powf(pos1.degree[2] - pos2.degree[2], 2);
    //printf("=================== %f %f %f", dx, dy, dz);
    float distance_squared = dx + dy + dz;
    if ((isnan(distance_squared) || isinf(distance_squared))) {
        distance_squared = FLT_MAX;
    }
    float distance = sqrt(distance_squared);

    return distance;
}

/*
<param name="robot" type="struct robot_organism *">
    The robot with any fitness.
</param>
<returns>
    The fitness of the robot.
*/
float calc_fitness(struct robot_organism *robot) {
    struct vec3 *analyzed_solution = vec6_to_vec3(&(robot->solution));
    float distance = calculate_distance(*analyzed_solution, robot->goal);

    float base_fitness = 1.0f/distance + 0.01f;

    float wage_penalty = 0.0f;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            float wage = robot->wages[i][j];
            if (fabs(wage) > 10.0f) {
                wage_penalty += 0.01f * (fabs(wage) - 10.0f);
            }
        }
    }

    float efficiency_reward = 0.0f;
    float sum_of_squares = 0.0f;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            sum_of_squares += robot->wages[i][j] * robot->wages[i][j];
        }
    }
    efficiency_reward = 100.0f / (100.0f + sqrtf(sum_of_squares));

    float final_fitness = 0.9f * base_fitness + 0.1f * efficiency_reward; // - 0.1f * wage_penalty;

    //printf("distance: %f\n", distance);
    //printf("base_fitness: %f\n", base_fitness);
    //printf("wage_penalty: %f\n", wage_penalty);
    //printf("efficiency_reward: %f\n", efficiency_reward);

    free(analyzed_solution);

    if ((isnan(final_fitness) || isinf(final_fitness))) {
        final_fitness = FLT_MAX;
    }

    robot->fitness = final_fitness; 
    // printf("fitness: %f", final_fitness);
    return final_fitness;
}

int compare_fitness(const void *a, const void *b) {
    struct robot_organism *robotA = *(struct robot_organism **)a;
    struct robot_organism *robotB = *(struct robot_organism **)b;
    // Compare based on fitness values
    if (robotA->fitness < robotB->fitness) return 1; // Descending order
    if (robotA->fitness > robotB->fitness) return -1;
    return 0;
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
    if (top_ranked == NULL) {
        fprintf(stderr, "Memory allocation failed for top_ranked\n");
        return NULL;
    }

    for (int i = 0; i < 100; i++) {
        calc_fitness(&(population->collector[i]));
    }

    for (int i = 0; i < 10; i++) {
        top_ranked[i] = &(population->collector[i]);
    }

    qsort(top_ranked, 10, sizeof(struct robot_organism *), compare_fitness);

    for (int i = 10; i < 100; i++) {
        struct robot_organism *current_robot = &(population->collector[i]);
        float current_fitness = calc_fitness(current_robot);

        if (current_fitness > top_ranked[9]->fitness) {
            top_ranked[9] = current_robot;
            qsort(top_ranked, 10, sizeof(struct robot_organism *), compare_fitness);
        }
    }

    return top_ranked;
}

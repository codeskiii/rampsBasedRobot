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
float calc_distance(struct vec3 *analyzed_solution, struct vec3 *goal) {
    float x_distance = abs((analyzed_solution->degree[0]) - (goal->degree[0]));
    float y_distance = abs((analyzed_solution->degree[1]) - (goal->degree[1]));
    float z_distance = abs((analyzed_solution->degree[2]) - (goal->degree[2]));

    return sqrtf(powf(x_distance, 2) + powf(y_distance, 2) + powf(z_distance, 2));
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
    float distance = calc_distance(analyzed_solution, &(robot->goal));

    // Zmiana: Użyj eksponencjalnej funkcji dla base_fitness
    float base_fitness = expf(-distance);

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
    efficiency_reward = 1.0f / (1.0f + sqrtf(sum_of_squares));

    // Zmiana: Dostosuj wagi składników fitness
    float final_fitness = 0.7f * base_fitness + 0.2f * efficiency_reward - 0.1f * wage_penalty;

    printf("distance: %f\n", distance);
    printf("base_fitness: %f\n", base_fitness);
    printf("wage_penalty: %f\n", wage_penalty);
    printf("efficiency_reward: %f\n", efficiency_reward);

    free(analyzed_solution);

    robot->fitness = final_fitness; 
    // printf("fitness: %f", final_fitness);
    return final_fitness;
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

    for (int i = 0; i < 100; i++) {
        // Dodaj tę linię:
        calc_fitness(&(population->collector[i]));
    }

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

#include <stdio.h>
#include <stdlib.h>
#include "structs.c"

/*
<returns>
    A new robot organism.
</returns>
*/
struct robot_organism *create_robot_organism() {
    struct robot_organism *currentRobot = malloc(sizeof(struct robot_organism));
    currentRobot->goal = (struct vec3) {rd_num(-10, 10), rd_num(0, 10), rd_num(-10, 10)};
    for (int i = 0; i < 7; i++) {
        // simple wage init
        currentRobot->wages[i] = 1;
    }
    return currentRobot;
}

/*
<param name="min" type="int">
   The minimum value.
</param>
<param name="max" type="int">
    The maximum value.
</param>
<returns>
    A random number between min and max.
</returns>
*/
int rd_num(int min, int max) {
    return rand() % (max - min + 1) + min;
}

/*
<returns>
    A new population.
</returns>
*/
struct population *create_population() {
    struct population *currentPopulation = malloc(sizeof(struct population));
    for (int i = 0; i < 100; i++) {
        currentPopulation->collector[i] = create_robot_organism();
    }
}

int main() {
    srand(time(NULL));
    return 0;
}
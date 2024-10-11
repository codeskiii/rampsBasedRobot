#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "helpers.h"

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
int rd_int(int min, int max) {
    //srand(time(NULL));
    return rand() % (max - min + 1) + min;
}

/*
<param name="min" type="float">
    The minimum value.
</param>
<param name="max" type="float">
    The maximum value.
</param>
<returns>
    A random number between min and max.
</returns>
*/
float rd_float(float min, float max) {
    //printf("random start\n");
    //float x = ((float)rand() / (float)RAND_MAX) * (max - min) + min;
    //printf("debug\n");
    //srand(time(NULL));
    float result = ((float)rand() / (float)RAND_MAX) * (max - min) + min;
    return result;
}

void print_high_score (struct robot_organism **top_ranked) {
    struct robot_organism top_organism = *(top_ranked[0]);
    float high_score = top_organism.fitness;
    printf("best score of epoch = %f \n", high_score);
    /* FOR DEBUG
    for(int i=0; i<=5 ; i++){
        for (int j=0; j<=5; j++){
            printf("wage: %f \n", top_organism.wages[i][j]);
        }
    }
    */
    fflush(stdout);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structs.h"

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
    float result = ((float)rand() / (float)RAND_MAX) * (max - min) + min;
    return result;
}

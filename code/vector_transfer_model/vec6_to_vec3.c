#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "structs.h"
#include "vec6_to_vec3.h"

// arms lenghts

//meat
#define l1 7.0
#define l2 7.0
// nut
#define l3 2.0 

#define WAGE_SIZE 12

#define MEMWATCH 
#define MW_STDIO 

#include "memwatch.h"

/*
<param name="vec6" type="struct vec6 *">
    The input vector with 6 degrees.
</param>
<param name="index" type="int">
    The index of the matrix to create.
</param>
<returns>
    The resulting matrix.
*/
struct joint_matrix *create_joint_matrix(struct vec6 *vec6, int joint_index) {
    struct joint_matrix *matrix = (struct joint_matrix*)malloc(sizeof(struct joint_matrix));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    float theta_1 = vec6->degree[joint_index];
    float theta_2 = vec6->degree[joint_index+1];

    /*
    matrix->abc[0] = cos(theta) * l1;  // A = cos(theta_i)
    matrix->abc[1] = sin(theta) * l2;  // B = sin(theta_i)
    matrix->abc[2] = 1.0;         // C = d_i 
    */

    switch (joint_index) {
        // math :(
        case 0:
            matrix->abc[0] = sin(theta_1) * l1;
            if (isnan(matrix->abc[0]) || isinf(matrix->abc[0])) {
                matrix->abc[0] = FLT_MAX;
            }
            matrix->abc[1] = sin(theta_2) * l1;
            if (isnan(matrix->abc[1]) || isinf(matrix->abc[1])) {
                matrix->abc[1] = FLT_MAX;
            }
            matrix->abc[2] = cos(theta_2) * l1;
            if (isnan(matrix->abc[2]) || isinf(matrix->abc[2])) {
                matrix->abc[2] = FLT_MAX;
            }
            break;
        case 1:
            matrix->abc[0] = sin(theta_1) * l2;
            if (isnan(matrix->abc[0]) || isinf(matrix->abc[0])) {
                matrix->abc[0] = FLT_MAX;
            }
            matrix->abc[1] = sin(theta_2) * l2;
            if (isnan(matrix->abc[0]) || isinf(matrix->abc[0])) {
                matrix->abc[0] = FLT_MAX;
            }            
            matrix->abc[2] = cos(theta_2) * l2;
            if (isnan(matrix->abc[0]) || isinf(matrix->abc[0])) {
                matrix->abc[0] = FLT_MAX;
            }            
            break;
        case 2:
            matrix->abc[0] = sin(theta_1) * l3;
            if (isnan(matrix->abc[0]) || isinf(matrix->abc[0])) {
                matrix->abc[0] = FLT_MAX;
            }            
            matrix->abc[1] = sin(theta_2) * l3;
            if (isnan(matrix->abc[0]) || isinf(matrix->abc[0])) {
                matrix->abc[0] = FLT_MAX;
            }            
            matrix->abc[2] = cos(theta_2) * l3;
            if (isnan(matrix->abc[0]) || isinf(matrix->abc[0])) {
                matrix->abc[0] = FLT_MAX;
            }            
            break;
    }

    return matrix;
}

/*
<param name="vec6" type="struct vec6 *">
    The input vector with 6 degrees.
</param>
<returns>
    The resulting matrix storage.
</returns>
*/

struct joint_matrix_storage *create_whole_matrix(struct vec6 *vec6) {
    struct joint_matrix_storage *storage = (struct joint_matrix_storage*)malloc(sizeof(struct joint_matrix_storage));
    if (storage == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < 3; i++) {
        storage->collector[i] = create_joint_matrix(vec6, i);
    }
    
    return storage;
}

/*
<param name="matrix1" type="struct joint_matrix *">
    The first matrix to multiply.
</param>
<param name="matrix2" type="struct joint_matrix *">
    The second matrix to multiply.
</param>
<returns>
    The resulting matrix.
*/

struct joint_matrix *multiply_joint_matrix(struct joint_matrix *matrix1, struct joint_matrix *matrix2) {
    struct joint_matrix *result = (struct joint_matrix*)malloc(sizeof(struct joint_matrix));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Matrix multiplication logic
    result->abc[0] = matrix1->abc[0] * matrix2->abc[0];  // A
    result->abc[1] = matrix1->abc[1] * matrix2->abc[1];  // B
    result->abc[2] = matrix1->abc[2] * matrix2->abc[2];  // C
    
    return result;
}

/*
<param name="matrix_storage1" type="struct joint_matrix_storage *">
    The first matrix storage to multiply.
</param>
<param name="matrix_storage2" type="struct joint_matrix_storage *">
    The second matrix storage to multiply.
</param>
<returns>
    The resulting matrix storage.
</returns>
*/

struct joint_matrix_storage *multiply_whole_matrix(struct joint_matrix_storage *matrix_storage1,
                                                     struct joint_matrix_storage *matrix_storage2) {

    struct joint_matrix_storage *result = (struct joint_matrix_storage*)malloc(sizeof(struct joint_matrix_storage));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < WAGE_SIZE; i++) {
        result->collector[i] = multiply_joint_matrix(matrix_storage1->collector[i], matrix_storage2->collector[i]);
    }

    return result;
}
/*
<param name="vec6" type="struct vec6 *">
    The input vector with 6 degrees.
</param>

<returns>
    The resulting vector with 3 degrees.
</returns>
*/

struct vec3 *vec6_to_vec3(struct vec6 *vec6) {
    
    struct joint_matrix_storage *matrix_storage = create_whole_matrix(vec6);
    if (matrix_storage == NULL) {
        fprintf(stderr, "Nie udało się utworzyć macierzy\n");
        return NULL;
    }

    struct joint_matrix *result_matrix = matrix_storage->collector[0];
    
    for (int i = 1; i < 3; i++) {
        struct joint_matrix *temp_matrix = matrix_storage->collector[i];
        struct joint_matrix *new_result = multiply_joint_matrix(result_matrix, temp_matrix);
        
        if (new_result == NULL) {
            fprintf(stderr, "Błąd podczas mnożenia macierzy\n");
            // Zwolnij pamięć przed wyjściem
            for (int j = 0; j < 3; j++) {
                free(matrix_storage->collector[j]);
            }
            free(matrix_storage);
            return NULL;
        }
        
        if (i > 1) {
            free(result_matrix);
        }
        result_matrix = new_result;
    }

    struct vec3 *result_vec3 = malloc(sizeof(struct vec3));
    if (result_vec3 == NULL) {
        fprintf(stderr, "Nie udało się zaalokować pamięci dla vec3\n");
        // Zwolnij pamięć przed wyjściem
        free(result_matrix);
        for (int i = 0; i < 3; i++) {
            free(matrix_storage->collector[i]);
        }
        free(matrix_storage);
        return NULL;
    }

    result_vec3->degree[0] = result_matrix->abc[0];
    result_vec3->degree[1] = result_matrix->abc[1];
    result_vec3->degree[2] = result_matrix->abc[2];

    // Zwolnij zaalokowaną pamięć
    free(result_matrix);
    for (int i = 0; i < 3; i++) {
        free(matrix_storage->collector[i]);
    }
    free(matrix_storage);

    return result_vec3;
}
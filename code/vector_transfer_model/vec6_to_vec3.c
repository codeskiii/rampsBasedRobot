#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "vec6_to_vec3.h"

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
struct joint_matrix *create_joint_matrix(struct vec6 *vec6, int index) {
    struct joint_matrix *matrix = (struct joint_matrix*)malloc(sizeof(struct joint_matrix));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    float theta = vec6->degree[index];

    matrix->abc[0] = cos(theta);  // A = cos(theta_i)
    matrix->abc[1] = sin(theta);  // B = sin(theta_i)
    matrix->abc[2] = 1.0;         // C = d_i 
    
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
    
    for (int i = 0; i < 6; i++) {
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

    for (int i = 0; i < 6; i++) {
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
    struct joint_matrix *result_matrix = matrix_storage->collector[0];

    for (int i = 1; i < 6; i++) {
        struct joint_matrix *temp_matrix = matrix_storage->collector[i];
        struct joint_matrix *new_result = multiply_joint_matrix(result_matrix, temp_matrix);
        free(result_matrix);  // Free previous result
        result_matrix = new_result;
    }

    struct vec3 *result_vec3 = malloc(sizeof(struct vec3));  // Dynamically allocate memory
    result_vec3->degree[0] = result_matrix->abc[0];
    result_vec3->degree[1] = result_matrix->abc[1];
    result_vec3->degree[2] = result_matrix->abc[2];

    // Free allocated memory
    free(result_matrix);
    for (int i = 0; i < 6; i++) {
        free(matrix_storage->collector[i]);
    }
    free(matrix_storage);

    return result_vec3;
}
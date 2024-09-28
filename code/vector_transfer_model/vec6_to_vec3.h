#ifndef VEC6_TO_VEC3_H
#define VEC6_TO_VEC3_H

struct vec3 *vec6_to_vec3(struct vec6 *vec6);
struct joint_matrix *create_joint_matrix(struct vec6 *vec6, int index);
struct joint_matrix_storage *create_whole_matrix(struct vec6 *vec6);
struct joint_matrix *multiply_joint_matrix(struct joint_matrix *matrix1, struct joint_matrix *matrix2);
struct joint_matrix_storage *multiply_whole_matrix(struct joint_matrix_storage *matrix1, struct joint_matrix_storage *matrix2);

#endif // VEC6_TO_VEC3_H

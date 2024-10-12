#ifndef STRUCTS_H
#define STRUCTS_H

/*
<param name="degree" type="float[6]">
    The array of the vector.
</param>
*/

struct vec6 {
    float degree[6]; 
};

/*
<param name="degree" type="float[3]">
    The array of the vector.
</param>
*/

struct vec3 {
    float degree[3]; 
};

/*
<param name="abc" type="float[3]">
    The array of the matrix.
</param>
*/

struct joint_matrix {
    float abc[3];  
};

/*
<param name="collector" type="struct joint_matrix *">
    The collector of the matrix.
</param>
*/

struct joint_matrix_storage {
    struct joint_matrix *collector[3];
};

/*
<param name="goal" type="struct vec3">
    The goal of the robot.
</param>
<param name="solution" type="struct vec6">
    The solution of the robot. Its provided by model.
</param>
<param name="analyzed_solution" type="struct vec3">
    The analyzed solution of the robot.
</param>
<param name="fitness" type="double">
    The fitness of the robot.
</param>
<param name="wages" type="double *">
    The wages of the robot. To evolve.
</param>
*/

struct robot_organism {
    struct vec3 goal;

    // x**y x**y_2 x**y_3 itd
    // 1*x + 6 * y ->
    float wages[6][12];

    struct vec6 solution;
    struct vec3 analyzed_solution;

    float fitness;
};

/*
<param name="collector" type="struct robot_organism *">
    The collector of the robot.
</param>
<param name="size" type="int">
    The size of the population.
</param>
*/

struct population {
    struct robot_organism collector[100];
};

#endif // STRUCTS_H

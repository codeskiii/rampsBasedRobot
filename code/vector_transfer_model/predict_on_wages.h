#ifndef PREDICT_ON_WAGES_H
#define PREDICT_ON_WAGES_H

float calculate_wages(struct vec3 *goal, float *wages);
struct vec6 make_predictions_on_wages(struct robot_organism *robot);
void predict_on_wages(struct population *population);

#endif
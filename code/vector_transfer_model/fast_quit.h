#ifndef FAST_QUIT_H
#define FAST_QUIT_H

int count_not_diversed_streak (struct robot_organism **top_ranked);
struct robot_organism **fast_roll(struct robot_organism **top_ranked);
struct robot_organism **roll_them(struct robot_organism **top_ranked);
int compare(const void *a, const void *b);
struct robot_organism **sort_them(struct robot_organism **A, struct robot_organism **B);

#endif
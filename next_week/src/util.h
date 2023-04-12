#ifndef UTIL_H
#define UTIL_H

#include <limits>
#include <cstdlib>

const double PI = 3.1415926535897932385;
const double INF_DOUBLE = std::numeric_limits<double>::infinity();

double deg_to_rad(double degrees);

void init_random();

double random();
double random_range(double min,double max);
int rand_int(int min,int max);

#endif
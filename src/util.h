#ifndef UTIL_H
#define UTIL_H

#include <limits>
#include <cstdlib>

const double PI = 3.1415926535897932385;
const double INF_DOUBLE = std::numeric_limits<double>::infinity();

double random();
double random_range(double min,double max);

#endif
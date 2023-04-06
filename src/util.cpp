#include "util.h"


double deg_to_rad(double degrees){
    return degrees * PI / 180.0;
}


double random(){
    return double(rand()) / RAND_MAX;
}

double random_range(double min,double max){
    return random()*(max - min) + min;
}
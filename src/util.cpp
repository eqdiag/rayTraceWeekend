#include "util.h"

double random(){
    return double(rand()) / RAND_MAX;
}

double random_range(double min,double max){
    return random()*(max - min) + min;
}
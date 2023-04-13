#include "util.h"
#include <cstdlib>
#include <ctime>


double deg_to_rad(double degrees){
    return degrees * PI / 180.0;
}

void init_random(){
    srand(time(NULL));
    rand();
}


double random(){
    return double(rand()) / RAND_MAX;
}

double random_range(double min,double max){
    return random()*(max - min) + min;
}

int rand_int(int min,int max){
    return int(random()*(max + 1 - min) + min);
}

#ifndef PERLIN_H
#define PERLIN_H

#include "vec3.h"

class Perlin{
    private:
        static const int num_points = 256;
        int * x_values;
        int * y_values;
        int * z_values;
        Vec3 * values;

        int * generate_permutation() const;
        double interpolate(double u,double v,double w,Vec3 c[2][2][2]) const;


    public:
        Perlin();
        ~Perlin();

        double noise(const Point3& p) const;
        double turb(const Point3& p,int layers = 8) const;
};


#endif
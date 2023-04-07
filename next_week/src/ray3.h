#ifndef RAY3_HPP
#define RAY3_HPP

#include "vec3.h"
#include <ostream>

class Ray3{
    private:
        Point3 p;
        Vec3 v;
        double time;

    public:
        Ray3();
        Ray3(Point3 p,Point3 v,double time);

        Point3 getPoint() const;
        Vec3 getDirection() const;
        double getTime() const;

        Point3 cast(double t) const;
};

std::ostream& operator<<(std::ostream& os,const Ray3& ray);

#endif
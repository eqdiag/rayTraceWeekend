#ifndef HIT_H
#define HIT_H

#include "vec3.h"
#include "ray3.h"
#include <optional>

struct Hit{
    double t;
    Point3 point;
    Vec3 normal;
    bool front_face{true};

    Hit(double t,Point3 point,Vec3 normal,bool front_face);
};


class Hittable{
    public:
        virtual std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const = 0;
};

#endif
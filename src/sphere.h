#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hit.h"
#include "ray3.h"
#include <optional>

class Sphere: public Hittable{
    private:
        Point3 center;
        double radius;
    public:
        Sphere();
        Sphere(Point3 center,double radius);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
};


#endif
#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hit.h"
#include "ray3.h"
#include <optional>
#include <memory>
#include "material.h"

class Sphere: public Hittable{
    private:
        Point3 center;
        double radius;
        std::shared_ptr<Material> material;
    public:
        Sphere(std::shared_ptr<Material> material);
        Sphere(Point3 center,double radius,std::shared_ptr<Material> material);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
};


#endif
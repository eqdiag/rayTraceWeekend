#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hit.h"
#include "ray3.h"
#include <optional>
#include <memory>
#include "material.h"
#include <iostream>

class Sphere: public Hittable{
    private:
        Point3 center;
        double radius;
        std::shared_ptr<Material> material;
    public:
        Sphere(std::shared_ptr<Material> material);
        Sphere(Point3 center,double radius,std::shared_ptr<Material> material);

        Point3 getCenter() const;
        double getRadius() const;


        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;

};

std::ostream& operator<<(std::ostream& os,const Sphere& rhs);

class MovingSphere: public Hittable{
    private:
        Point3 start_center;
        Point3 end_center;
        double radius;
        std::shared_ptr<Material> material;

        Point3 getCenter(double time) const;

    public:
        MovingSphere(std::shared_ptr<Material> material);
        MovingSphere(Point3 start_center,Point3 end_center,double radius,std::shared_ptr<Material> material);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;

};


#endif
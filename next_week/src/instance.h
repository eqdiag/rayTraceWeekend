#ifndef INSTANCE_H
#define INSTANCE_H

#include "hit.h"
#include "vec3.h"
#include "material.h"

class Translation: public Hittable{
    private:
        Vec3 translation;
        std::shared_ptr<Hittable> object;
    public:
        Translation(const Vec3& translation,std::shared_ptr<Hittable> object);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;
};

class RotateY: public Hittable{
    private:
        double cos_angle;
        double sin_angle;
        std::shared_ptr<Hittable> object;
        bool has_box;
        AABB bbox;

    public:
        RotateY(double angle,std::shared_ptr<Hittable> object);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;
};


#endif
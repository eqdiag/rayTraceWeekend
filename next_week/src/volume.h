#ifndef VOLUME_H
#define VOLUME_H

#include "hit.h"
#include "material.h"

class ConstantMedium: public Hittable{
    private:
        std::shared_ptr<Hittable> boundary_object;
        std::shared_ptr<Material> material;
        double neg_inv_density;
    public:
        ConstantMedium(std::shared_ptr<Hittable> boundary_object,std::shared_ptr<Texture> texture,double C);
        ConstantMedium(std::shared_ptr<Hittable> boundary_object,const Color3& color,double C);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;
};

#endif
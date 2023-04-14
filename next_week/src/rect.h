#ifndef RECT_H
#define RECT_H

#include "hit.h"
#include <memory>
#include "material.h"

class RectXY: public Hittable{
    private:
        double z;
        double xmin,xmax;
        double ymin,ymax;
        std::shared_ptr<Material> material;
    public:
        RectXY(double z,double xmin,double xmax,double ymin,double ymax,std::shared_ptr<Material> material);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;
};

class RectXZ: public Hittable{
    private:
        double y;
        double xmin,xmax;
        double zmin,zmax;
        std::shared_ptr<Material> material;
    public:
        RectXZ(double y,double xmin,double xmax,double zmin,double zmax,std::shared_ptr<Material> material);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;
};

class RectYZ: public Hittable{
    private:
        double x;
        double ymin,ymax;
        double zmin,zmax;
        std::shared_ptr<Material> material;
    public:
        RectYZ(double x,double ymin,double ymax,double zmin,double zmax,std::shared_ptr<Material> material);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;
};

class Box: public Hittable{
    private:
        Point3 p0;
        Point3 p1;
        HitList faces;
    public:
        Box(const Point3& p0,const Point3& p1,std::shared_ptr<Material> material);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;
};


#endif
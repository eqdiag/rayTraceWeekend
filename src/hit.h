#ifndef HIT_H
#define HIT_H

#include "vec3.h"
#include "ray3.h"
#include "material.h"
#include <optional>
#include <vector>
#include <memory>

//Forward declaration
struct Material;

struct Hit{
    double t;
    Point3 point;
    Vec3 normal;
    bool front_face{true};
    std::shared_ptr<Material> material;
    Hit();
    Hit(double t,Point3 point,Vec3 normal,bool front_face);
};

class Hittable{
    public:
        virtual std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const = 0;
};


class HitList: public Hittable{
    private:
        std::vector<std::shared_ptr<Hittable>> objects;

    public:
        HitList();
        HitList(std::shared_ptr<Hittable> object);

        void add(std::shared_ptr<Hittable> object);
        void empty();

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
};




#endif
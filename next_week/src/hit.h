#ifndef HIT_H
#define HIT_H

#include "vec3.h"
#include "ray3.h"
#include "material.h"
#include "aabb.h"
#include <optional>
#include <vector>
#include <memory>
#include <ostream>
#include <cmath>

//Forward declaration
struct Material;
struct AABB;

struct Hit{
    double t;
    Point3 point;
    Vec3 normal;
    bool front_face{true};
    std::shared_ptr<Material> material;
    Hit();
    Hit(double t,Point3 point,Vec3 normal,bool front_face);

    void set_face_normal(const Ray3& ray,const Vec3& out_normal){
        front_face = ray.getDirection().dot(out_normal) < 0.0;
        normal = front_face ? out_normal : -out_normal;
    }
};

std::ostream& operator<<(std::ostream& os,const Hit& hit);

class Hittable{
    public:
        virtual std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const = 0;
        virtual bool getBoundingBox(double time0,double time1,AABB& box) const = 0;
};


class HitList: public Hittable{
    private:
        std::vector<std::shared_ptr<Hittable>> objects;

    public:
        HitList();
        HitList(std::shared_ptr<Hittable> object);

        void add(std::shared_ptr<Hittable> object);
        void empty();
        const std::vector<std::shared_ptr<Hittable>>& getObjects() const;
        std::vector<std::shared_ptr<Hittable>>& getObjectsMut();


        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const override;
        bool getBoundingBox(double time0,double time1,AABB& box) const override;

};




#endif
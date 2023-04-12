#ifndef BVH_H
#define BVH_H

#include "aabb.h"
#include "hit.h"
#include <memory>

class BVHNode: public Hittable{
    private:
        AABB bbox;
        std::shared_ptr<Hittable> left_child;
        std::shared_ptr<Hittable> right_child;
    public:
        BVHNode(std::vector<std::shared_ptr<Hittable>>& objects,size_t start,size_t end,double time0,double time1);
        BVHNode(HitList& hitlist,double time0,double time1);

        std::optional<Hit> getHit(const Ray3& ray,double tmin,double tmax) const;
        bool getBoundingBox(double time0,double time1,AABB& box) const;

};

bool compareBox(const std::shared_ptr<Hittable> a,const std::shared_ptr<Hittable> b,int axis);
bool compareBox_x(const std::shared_ptr<Hittable> a,const std::shared_ptr<Hittable> b);
bool compareBox_y(const std::shared_ptr<Hittable> a,const std::shared_ptr<Hittable> b);
bool compareBox_z(const std::shared_ptr<Hittable> a,const std::shared_ptr<Hittable> b);


#endif
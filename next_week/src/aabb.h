#ifndef AABB_H
#define AABB_H

#include "hit.h"
#include "vec3.h"
#include "ray3.h"
#include <iostream>

class AABB{
    private:
        Vec3 p0;
        Vec3 p1;

    public:
        AABB();
        AABB(const Point3& p0,const Point3& p1);

        Point3 getMin() const;
        Point3 getMax() const;

        bool isHit(const Ray3& ray,double tmin,double tmax) const;

        AABB mergeBoxes(const AABB& rhs) const;
};

std::ostream& operator<<(std::ostream& os,const AABB& rhs);





#endif
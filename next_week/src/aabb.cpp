#include "aabb.h"


AABB::AABB()
:p0{},p1{}
{

}


AABB::AABB(const Point3& p0,const Point3& p1)
:p0{p0},p1{p1}
{

}

Point3 AABB::getMin() const
{
    return p0;
}

Point3 AABB::getMax() const
{
    return p1;
}

bool AABB::isHit(const Ray3& ray,double tmin,double tmax) const
{
    Point3 p = ray.getPoint();
    Vec3 v = ray.getDirection();
    
    //std::cerr << ray << std::endl;

    //X-axis
    double tx0 = (p0.x() - p.x())/v.x();
    double tx1 = (p1.x() - p.x())/v.x();
    double tx_min = fmin(tx0,tx1);
    double tx_max = fmax(tx0,tx1); 
    //Compute overlapping interval
    tmin = fmax(tmin,tx_min);
    tmax = fmin(tmax,tx_max);

    //std::cerr << tmin << " " << tmax << std::endl;

    if(tmax <= tmin) return false;

    //Y-axis
    double ty0 = (p0.y() - p.y())/v.y();
    double ty1 = (p1.y() - p.y())/v.y();
    double ty_min = fmin(ty0,ty1);
    double ty_max = fmax(ty0,ty1); 
    //Compute overlapping interval
    tmin = fmax(tmin,ty_min);
    tmax = fmin(tmax,ty_max);

    //std::cerr << tmin << " " << tmax << std::endl;


    if(tmax <= tmin) return false;

    //Z-axis
    double tz0 = (p0.z() - p.z())/v.z();
    double tz1 = (p1.z() - p.z())/v.z();
    double tz_min = fmin(tz0,tz1);
    double tz_max = fmax(tz0,tz1); 
    //Compute overlapping interval
    tmin = fmax(tmin,tz_min);
    tmax = fmin(tmax,tz_max);

    //std::cerr << tmin << " " << tmax << std::endl;


    //Is this still a valid interval?
    return tmin < tmax;
}

AABB AABB::mergeBoxes(const AABB& rhs) const
{
    Point3 pl
    {
        fmin(p0.x(),rhs.p0.x()),
        fmin(p0.y(),rhs.p0.y()),
        fmin(p0.z(),rhs.p0.z()),
    };

    Point3 pr
    {
        fmax(p1.x(),rhs.p1.x()),
        fmax(p1.y(),rhs.p1.y()),
        fmax(p1.z(),rhs.p1.z()),
    };

    return AABB{pl,pr};
}

std::ostream& operator<<(std::ostream& os,const AABB& rhs)
{
    os << "Min: " << rhs.getMin() << " Max: " << rhs.getMax();
    return os;
}

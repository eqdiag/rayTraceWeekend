#include "ray3.h"

Ray3::Ray3()
:p{},v{},time{0.0}
{

}

Ray3::Ray3(Point3 p,Point3 v,double time)
:p{p},v{v},time{time}
{

}

Point3 Ray3::getPoint() const{
    return p;
}

Vec3 Ray3::getDirection() const{
    return v;
}

double Ray3::getTime() const{
    return time;
}


Point3 Ray3::cast(double t) const{
    return p + v*t;
}

std::ostream& operator<<(std::ostream& os,const Ray3& ray){
    os << "P: " << ray.getPoint() << " -> " << "V: " << ray.getDirection(); 
    return os;
}
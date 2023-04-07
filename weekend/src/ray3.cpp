#include "ray3.h"

Ray3::Ray3()
:p{},v{}
{

}

Ray3::Ray3(Point3 p,Point3 v)
:p{p},v{v}
{

}

Point3 Ray3::getPoint() const{
    return p;
}

Vec3 Ray3::getDirection() const{
    return v;
}

Point3 Ray3::cast(double t) const{
    return p + v*t;
}

std::ostream& operator<<(std::ostream& os,const Ray3& ray){
    os << "P: " << ray.getPoint() << " -> " << "V: " << ray.getDirection(); 
    return os;
}
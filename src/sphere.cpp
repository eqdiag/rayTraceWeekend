#include "sphere.h"
#include <cmath>

Sphere::Sphere()
:center{},radius{1.0}
{

}

Sphere::Sphere(Point3 center,double radius)
:center{center},radius{radius}
{

}

std::optional<Hit> Sphere::getHit(const Ray3& ray,double tmin,double tmax) const{
    Vec3 p(ray.getPoint());
    Vec3 v(ray.getDirection());

    Vec3 dx = p - center;

    double a = v.dot(v);
    double b = 2.0*v.dot(dx);
    double c = dx.dot(dx) - radius*radius;
    double discrim = b*b-4*a*c;
    //return discrim >= 0.0;
    if(discrim < 0.0){
        return {};
    }
    double discrim_root = sqrt(discrim_root);
    
    float t0 = (-b - discrim)/(2.*a);
    //t0 will always be closer if valid
    if(t0 > tmin && t0 < tmax){
        Point3 q(ray.cast(t0));
        bool front_face = v.dot(q - center) < 0.0;
        return std::make_optional<Hit>(Hit(t0,q,(q-center).normalize(),front_face));
    }

    float t1 = (-b + discrim)/(2.*a);

    if(t1 > tmin && t1 < tmax){
        Point3 q(ray.cast(t1));
        bool front_face = v.dot(q - center) < 0.0;
        return std::make_optional<Hit>(Hit(t0,q,(q-center).normalize(),front_face));
    }

    //If execution gets here, no positive real roots
    return {};
    
}
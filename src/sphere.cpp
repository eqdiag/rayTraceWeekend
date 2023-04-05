#include "sphere.h"
#include <cmath>

Sphere::Sphere(std::shared_ptr<Material> material)
:center{},radius{1.0},material{material}
{

}

Sphere::Sphere(Point3 center,double radius,std::shared_ptr<Material> material)
:center{center},radius{radius},material{material}
{

}

std::optional<Hit> Sphere::getHit(const Ray3& ray,double tmin,double tmax) const{
    
  
    Vec3 p = ray.getPoint();
    Vec3 v = ray.getDirection();

    Vec3 dx = p - center;

    double a = v.dot(v);
    double b_half = v.dot(dx);
    double c = dx.dot(dx) - radius*radius;
    double discrim = b_half*b_half - a*c;
    if(discrim < 0.0){
        return {};
    }
    double discrim_root = sqrt(discrim);
    
    float t = (-b_half - discrim_root) / a;
    if(t < tmin || t > tmax){
        t = (-b_half + discrim_root) / a;
        if(t < tmin || t > tmax){
            //No real roots in valid interval
            return {};
        }
    }
    

    Hit hit{};
    hit.t = t;
    hit.point = ray.cast(t);
    Vec3 normal = (hit.point - center)/radius;
    hit.set_face_normal(ray,normal);
    hit.material = material;

    return std::make_optional<Hit>(hit);

}
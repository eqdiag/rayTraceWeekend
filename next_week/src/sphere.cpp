#include "sphere.h"
#include <cmath>
#include "util.h"

Sphere::Sphere(std::shared_ptr<Material> material)
:center{},radius{1.0},material{material}
{

}

Sphere::Sphere(Point3 center,double radius,std::shared_ptr<Material> material)
:center{center},radius{radius},material{material}
{

}

Point3 Sphere::getCenter() const
{
    return center;
}

double Sphere::getRadius() const
{
    return radius;
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
    getTexCoords(hit.u,hit.v,normal);

    return std::make_optional<Hit>(hit);

}

bool Sphere::getBoundingBox(double time0,double time1,AABB& box) const
{
    //std::cerr << "Sphere box: " << *this << std::endl;

    box = {
        center - Vec3(radius),
        center + Vec3(radius)
    };
    return true;
}

void Sphere::getTexCoords(double& u,double &v,Point3& p)
{
    double phi = acos(p.y());
    double theta = atan2(-p.z(),p.x()) + PI;

    u = theta / (2*PI);
    v = phi / PI;
}


std::ostream& operator<<(std::ostream& os,const Sphere& rhs)
{
    os << "center: " << rhs.getCenter() << " radius: " << rhs.getRadius() << std::endl;
    return os;
}



MovingSphere::MovingSphere(std::shared_ptr<Material> material)
:start_center{},end_center{},radius{1.0},material{material}
{

}

MovingSphere::MovingSphere(Point3 start_center,Point3 end_center,double radius,std::shared_ptr<Material> material)
:start_center{start_center},end_center{end_center},radius{radius},material{material}
{

}

Point3 MovingSphere::getCenter(double time) const{
    return start_center*(1.- time) + end_center*time;
}


std::optional<Hit> MovingSphere::getHit(const Ray3& ray,double tmin,double tmax) const{
    Vec3 p = ray.getPoint();
    Vec3 v = ray.getDirection();

    Vec3 dx = p - getCenter(ray.getTime());

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
    Vec3 normal = (hit.point - getCenter(ray.getTime()))/radius;
    hit.set_face_normal(ray,normal);
    hit.material = material;

    return std::make_optional<Hit>(hit);
};

bool MovingSphere::getBoundingBox(double time0,double time1,AABB& box) const
{
    AABB box0 = {
        getCenter(time0) - Vec3(radius),
        getCenter(time0) + Vec3(radius)
    };

    AABB box1 = {
        getCenter(time1) - Vec3(radius),
        getCenter(time1) + Vec3(radius)
    };

    box = box0.mergeBoxes(box1);

    return true;
}

#include "material.h"

Lambertian::Lambertian(const Color3& albedo)
:albedo(albedo)
{

}

bool Lambertian::scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const{

    Vec3 direction = hit.normal + Vec3::random_unit_vec3();
    if(direction.effectively_zero()){
        direction = hit.normal;
    }

    out = Ray3(hit.point,direction);
    attenuation = albedo;

    return true;
}

Metal::Metal(const Color3& albedo,double fuzz)
:albedo(albedo),fuzz{fuzz < 1. ? fuzz : 1.}
{

}

bool Metal::scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const{

    Vec3 direction = in.getDirection().normalize().reflect(hit.normal);
    out = Ray3(hit.point,direction + Vec3::random_unit_vec3()*fuzz);
    attenuation = albedo;
    return direction.dot(hit.normal) > 0.0;
}
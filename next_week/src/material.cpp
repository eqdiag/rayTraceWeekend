#include "material.h"
#include <iostream>
#include <cmath>

Lambertian::Lambertian(const Color3& albedo)
:albedo(albedo)
{

}

bool Lambertian::scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const{

    Vec3 direction = hit.normal + Vec3::random_unit_vec3();
    if(direction.effectively_zero()){
        direction = hit.normal;
    }

    out = Ray3(hit.point,direction,in.getTime());
    attenuation = albedo;

    return true;
}

Metal::Metal(const Color3& albedo,double fuzz)
:albedo(albedo),fuzz{fuzz < 1. ? fuzz : 1.}
{

}

bool Metal::scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const{

    Vec3 direction = in.getDirection().normalize().reflect(hit.normal);
    out = Ray3(hit.point,direction + Vec3::random_unit_vec3()*fuzz,in.getTime());
    attenuation = albedo;
    return direction.dot(hit.normal) > 0.0;
}

Dielectric::Dielectric(double index_of_refraction)
:ir{index_of_refraction}
{

}

bool Dielectric::scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const
{
  
    attenuation = Color3(1.0, 1.0, 1.0);
    double refraction_ratio = hit.front_face ? (1.0/ir) : ir;

    Vec3 unit_direction = in.getDirection().normalize();
    double cos_theta = -unit_direction.dot(hit.normal);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool must_reflect = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;


    //Reflect if in denser medium and at a shallow grazing angle
    //Also some fraction of the time to account for fraction of energy due
    //to reflection
    if (must_reflect || schlick_reflectance(cos_theta, refraction_ratio) > rand())
        direction = unit_direction.reflect( hit.normal);
    else
        direction = unit_direction.refract(hit.normal, refraction_ratio);

    out = Ray3(hit.point, direction,in.getTime());
    return true;

}

double Dielectric::schlick_reflectance(double cosine, double ref_idx) {
    double r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}
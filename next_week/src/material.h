#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray3.h"
#include "hit.h"
#include "texture.h"
#include <memory>

//Forward declaration
struct Hit;

class Material{
    public:
        virtual bool scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const = 0;

        //By default a material emits nothing
        virtual Color3 emission(double u,double v,const Point3& p) const{
            return Color3{0.};
        }
};

class Lambertian: public Material{
    private:
        std::shared_ptr<Texture> albedo;

    public:
        Lambertian(const std::shared_ptr<Texture> albedo);
        Lambertian(const Color3& color);


        virtual bool scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const override;

};

class Metal: public Material{
    private:
        std::shared_ptr<Texture> albedo;
        double fuzz;

    public:
        Metal(const std::shared_ptr<Texture> albedo,double fuzz);

        virtual bool scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const override;

};

class Dielectric: public Material{
    private:
        double ir;

        static double schlick_reflectance(double cosine, double ref_idx);

    public:
        Dielectric(double index_of_refraction);

        virtual bool scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const override;

};

class DiffuseLight: public Material{
    private:
        std::shared_ptr<Texture> texture;
    public:
        DiffuseLight(const std::shared_ptr<Texture> texture);
        DiffuseLight(const Color3& color);

        bool scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const override;

        Color3 emission(double u,double v,const Point3& p) const override;
};


#endif
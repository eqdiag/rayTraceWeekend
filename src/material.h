#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray3.h"
#include "hit.h"

//Forward declaration
struct Hit;

class Material{
    public:
        virtual bool scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const = 0;
};

class Lambertian: public Material{
    private:
        Color3 albedo;

    public:
        Lambertian(const Color3& albedo);

        virtual bool scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const override;

};

class Metal: public Material{
    private:
        Color3 albedo;
        double fuzz;

    public:
        Metal(const Color3& albedo,double fuzz);

        virtual bool scatter(const Ray3& in,const Hit& hit,Ray3& out,Color3& attenuation) const override;

};


#endif
#ifndef TEXTURE_H
#define TEXTURE_H

#include "vec3.h"
#include <memory>

class Texture{
    public:
        virtual Color3 getColor(double u,double v,const Point3& p) const = 0;
};

class FlatTexture : public Texture{
    private:
        Color3 color;
    public:
        FlatTexture(const Color3& color);
        FlatTexture(double r,double g,double b);
        Color3 getColor(double u,double v,const Point3& p) const override;
};

class CheckerTexture: public Texture{
    private:
        std::shared_ptr<Texture> tex0;
        std::shared_ptr<Texture> tex1;
    public:
        CheckerTexture(std::shared_ptr<Texture> tex0,std::shared_ptr<Texture> tex1);
        Color3 getColor(double u,double v,const Point3& p) const;
};


#endif
#ifndef TEXTURE_H
#define TEXTURE_H

#include "vec3.h"
#include "perlin.h"
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

class ImageTexture: public Texture{
    private:
        const static int bytes_per_pixel = 3;
        int bytes_per_scanline;
        int width,height,num_channels;
        unsigned char * img;
    public:
        ImageTexture(const char * path);
        ~ImageTexture();
        Color3 getColor(double u,double v,const Point3& p) const override;
};

class CheckerTexture: public Texture{
    private:
        std::shared_ptr<Texture> tex0;
        std::shared_ptr<Texture> tex1;
        double scale;
    public:
        CheckerTexture(std::shared_ptr<Texture> tex0,std::shared_ptr<Texture> tex1);
        CheckerTexture(std::shared_ptr<Texture> tex0,std::shared_ptr<Texture> tex1,double scale);
        Color3 getColor(double u,double v,const Point3& p) const;
};

class NoiseTexture: public Texture{
    private:
        Perlin noise_src;
        double scale;
    public:
        NoiseTexture();
        NoiseTexture(double scale);
        Color3 getColor(double u,double v,const Point3& p) const;
};


#endif
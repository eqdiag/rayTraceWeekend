#include "texture.h"
#include <cmath>
#include <iostream>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

FlatTexture::FlatTexture(const Color3& color)
:color{color}
{

}

FlatTexture::FlatTexture(double r,double g,double b)
:color{r,g,b}
{
    
}


Color3 FlatTexture::getColor(double u,double v,const Point3& p) const
{
    return color;
}

ImageTexture::ImageTexture(const char * path)
{
    img = stbi_load("../assets/images/earthmap.jpg",&width,&height,&num_channels,bytes_per_pixel);

     if(img == nullptr){
        std::cerr << "Error loading image!\n";
    }

    std::cerr << "Loaded image:\n" << path << "\n(width,height,channels) = (" << width << "," << height << "," << num_channels << ")\n";

    bytes_per_scanline = bytes_per_pixel* width;
}

ImageTexture::~ImageTexture()
{
    stbi_image_free(img);
}

Color3 ImageTexture::getColor(double u,double v,const Point3& p) const
{
    if(img == nullptr) return Color3{0.0,1.,1.};
    u = std::clamp(u,0.0,1.0);
    v = std::clamp(v,0.0,1.0);

    auto i = static_cast<int>(u * width);
    auto j = static_cast<int>(v * height);

    // Clamp integer mapping, since actual coordinates should be less than 1.0
    if (i >= width)  i = width-1;
    if (j >= height) j = height-1;

    const auto color_scale = 1.0 / 255.0;
    auto pixel = img + j*bytes_per_scanline + i*bytes_per_pixel;

    return Color3(color_scale*pixel[0], color_scale*pixel[1], color_scale*pixel[2]);
}

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> tex0,std::shared_ptr<Texture> tex1)
:CheckerTexture{tex0,tex1,1.0}
{

}

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> tex0,std::shared_ptr<Texture> tex1,double scale)
:tex0{tex0},tex1{tex1},scale{1.0}
{

}


Color3 CheckerTexture::getColor(double u,double v,const Point3& p) const
{
    double value = sin(scale*p.x())*sin(scale*p.y())*sin(scale*p.z());
    if(value < 0) return tex0->getColor(u,v,p);
    return tex1->getColor(u,v,p);
}

NoiseTexture::NoiseTexture()
:noise_src{},scale{1.0}
{

}

NoiseTexture::NoiseTexture(double scale)
:scale{scale}
{

}


Color3 NoiseTexture::getColor(double u,double v,const Point3& p) const
{
    //return Color3{1.0}*0.5*(1.0+noise_src.noise(p*scale));
    //return Color3{1.0}*noise_src.turb(p*scale);
    return Color3{1.0}*0.5*(1.0 + sin(scale*p.x() + 10.*noise_src.turb(p)));
}
#include "texture.h"
#include <cmath>

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

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> tex0,std::shared_ptr<Texture> tex1)
:tex0{tex0},tex1{tex1}
{

}

Color3 CheckerTexture::getColor(double u,double v,const Point3& p) const
{
    double value = sin(4.0*p.x())*sin(4.0*p.y())*sin(4.0*p.z());
    if(value < 0) return Color3{0.0};
    return Color3{1.0};
}
#include <iostream>
#include "vec3.h"
#include "ray3.h"
#include "sphere.h"
#include "util.h"
#include "hit.h"
#include <cassert>
#include <cmath>

Color3 background(const Ray3& ray){
    double t = (ray.getDirection().y() + 1.)*.5;

    return Color3{1.0,1.0,1.0}*(1.-t) + Color3{.54,.81,.94}*t;
}

Color3 shade(const Ray3& ray,const Hittable& scene,int depth){

    if(depth <= 0){
        return Color3{0.0,0.0,0.0};
    }

    std::optional<Hit> hit{scene.getHit(ray,0.001,INF_DOUBLE)};


    if(hit.has_value()){

        auto material = hit.value().material;
        Ray3 out{};
        Color3 attenuation{};
        if(material->scatter(ray,hit.value(),out,attenuation)){
            return shade(out,scene,depth-1)*attenuation;
        }
        return Color3{0.0};
    }

    return background(ray);
}

void ouputColor(const Color3& color){

    //Gamma 2 corrected color (gamma = 2 for 1/gamma power)
    Color3 outColor{sqrt(color.r()),sqrt(color.g()),sqrt(color.b())};

    std::cout << 
    static_cast<int>(outColor.r()*255.999) << " " <<
    static_cast<int>(outColor.g()*255.999) << " " <<
    static_cast<int>(outColor.b()*255.999) << " ";
}

int main(){


    //Image params
    const double aspect_ratio = 16./9.;
    const int WIDTH = 600;
    const int HEIGHT = static_cast<int>(WIDTH/aspect_ratio);
    int samples_per_pixel = 100;
    int max_depth = 50;

    //Camera setup
    double view_height = 2.0;
    double view_width = aspect_ratio * view_height;
    double focal_length = 1.0;


    Point3 eye{};
    Vec3 dx(view_width,0.0,0.0);
    Vec3 dy(0.0,view_height,0.0);
    Point3 lower_left = eye - dx*0.5 - dy*0.5 - Vec3(0,0,focal_length);


    //Scene materials
    auto ground = std::make_shared<Lambertian>(Lambertian{Color3{0.8,0.8,0.0}});
    auto material_center = std::make_shared<Lambertian>(Lambertian{Color3{0.7,0.3,0.3}});
    auto material_left = std::make_shared<Metal>(Metal{Color3{0.8},0.3});
    auto material_right = std::make_shared<Metal>(Metal{Color3{0.8,0.6,0.2},1.0});


    //Scene geometry
    HitList scene;
    scene.add(std::make_shared<Sphere>(Point3(0.,0.,-1.),0.5,material_center));
    scene.add(std::make_shared<Sphere>(Point3(-1.0,0.,-1.),0.5,material_left));
    scene.add(std::make_shared<Sphere>(Point3(1.0,0.,-1.),0.5,material_right));
    scene.add(std::make_shared<Sphere>(Point3(0,-100.5,-1),100,ground));

    Ray3 ray(Point3{},Vec3{0.0,0.0,-1.0});

    //Iterate through pixels and shade

    std::cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";  
    std::cerr << "Starting Render" << std::endl;
    for(int i = HEIGHT - 1;i >= 0;i--){
        for(int j = 0;j < WIDTH;j++){

            //Multi sample here
            Color3 color{};

            for(int sample = 0;sample< samples_per_pixel;sample++){
                double u = (double(j) + random())/(WIDTH - 1);
                double v = (double(i) + random())/(HEIGHT - 1);
        

                Point3 eye{};
                Point3 screen_point(lower_left + dx*u + dy*v);
                Vec3 direction(screen_point - eye);
                Ray3 ray(eye,direction);

                color += shade(ray,scene,max_depth);
            }
            color /= double(samples_per_pixel);

            ouputColor(color);
        }
        std::cout << "\n";
        std::cerr << "Lines rendered: " << (HEIGHT - i) << "/"
        << HEIGHT << std::endl;
    }
    std::cerr << "Rendering complete!\n";
}
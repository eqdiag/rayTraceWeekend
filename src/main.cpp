#include <iostream>
#include "vec3.h"
#include "ray3.h"
#include "sphere.h"
#include "util.h"

Color3 background(const Ray3& ray){
    double t = (ray.getDirection().y() + 1.)*.5;
    return Color3(1.0,1.0,1.0)*(1.-t) + Color3(.54,.81,.94)*t;
}

void ouputColor(const Color3& color){
    std::cout << 
    static_cast<int>(color.r()*255.999) << " " <<
    static_cast<int>(color.g()*255.999) << " " <<
    static_cast<int>(color.b()*255.999) << " ";
}

int main(){

    //Image params
    const double aspect_ratio = 16./9.;
    const int WIDTH = 800;
    const int HEIGHT = static_cast<int>(WIDTH/aspect_ratio);

    //Camera setup
    double view_height = 2.0;
    double view_width = aspect_ratio * view_height;
    double focal_length = 1.0;



    Point3 eye{};
    Vec3 dx(view_width,0.0,0.0);
    Vec3 dy(0.0,view_height,0.0);
    Point3 lower_left = eye - dx*0.5 - dy*0.5 - Vec3(0,0,focal_length);


    //Scene geometry
    Sphere sphere(Point3(0.,0.,-2.),1.);

    Ray3 ray(Point3{},Vec3{0.0,0.0,-1.0});

    //Iterate through pixels and shade

    std::cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";  
    std::cerr << "Starting Render" << std::endl;
    for(int i = HEIGHT - 1;i >= 0;i--){
        for(int j = 0;j < WIDTH;j++){

            double u = double(j)/(WIDTH - 1);
            double v = double(i)/(HEIGHT - 1);

            Point3 eye{};
            Point3 screen_point(lower_left + dx*u + dy*v);
            Vec3 direction(screen_point - eye);
            Ray3 ray(eye,direction);

            Color3 color{};

            std::optional<Hit> hit{sphere.getHit(ray,0.0,INF_DOUBLE)};

            if(hit.has_value()){
                Vec3 normal = hit.value().normal;
                color = (normal + Vec3(1.))*0.5;
            }else{
                color = background(ray);
            }

           
            ouputColor(color);
        }
        std::cout << "\n";
        std::cerr << "Lines rendered: " << (HEIGHT - i) << "/"
        << HEIGHT << std::endl;
    }
    std::cerr << "Rendering complete!\n";
}
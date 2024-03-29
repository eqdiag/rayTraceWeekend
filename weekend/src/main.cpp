#include <iostream>
#include "vec3.h"
#include "ray3.h"
#include "sphere.h"
#include "util.h"
#include "hit.h"
#include <cassert>
#include <cmath>
#include "camera.h"

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

HitList basic_scene(){
    auto ground = std::make_shared<Lambertian>(Color3{0.8,0.8,0.0});
    auto material_center = std::make_shared<Lambertian>(Color3{0.1,0.2,0.5});
    auto material_left = std::make_shared<Dielectric>(1.5);
    auto material_right = std::make_shared<Metal>(Color3{0.8,0.6,0.2},1.0);


    //Scene geometry
    HitList scene;
    scene.add(std::make_shared<Sphere>(Point3(0.,0.,-1.),0.5,material_center));
    scene.add(std::make_shared<Sphere>(Point3(-1.0,0.0,-1.0),0.5,material_left));
    scene.add(std::make_shared<Sphere>(Point3(-1.0,0.0,-1.0),-0.45,material_left));
    scene.add(std::make_shared<Sphere>(Point3(1.0,0.,-1.),0.5,material_right));
    scene.add(std::make_shared<Sphere>(Point3(0,-100.5,-1),100,ground));

    return scene;
}

HitList random_scene() {
    HitList scene;

    auto ground_material = std::make_shared<Lambertian>(Color3(0.5, 0.5, 0.5));
    scene.add(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random();
            Point3 center(a + 0.9*random(), 0.2, b + 0.9*random());

            if ((center - Point3(4, 0.2, 0)).norm() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color3::random_vec3(0.0,1.0) * Color3::random_vec3(0.0,1.0);
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    scene.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color3::random_vec3(0.5, 1);
                    auto fuzz = random_range(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    scene.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    scene.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }


    auto material1 = std::make_shared<Dielectric>(1.5);
    scene.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color3(0.4, 0.2, 0.1));
    scene.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color3(0.7, 0.6, 0.5), 0.0);
    scene.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return scene;
}

int main(){


    //Image params
    const double aspect_ratio = 3.0/2.0;
    const int WIDTH = 1200;
    const int HEIGHT = static_cast<int>(WIDTH/aspect_ratio);

    //Sampling params
    int samples_per_pixel = 500;
    int max_depth = 50;

    //Camera
    Point3 from(13,2,3);
    Point3 at(0,0,0);
    Vec3 up(0,1,0);
    double f_dist = 10.0;
    double aperture = 0.1;

    Camera cam(from,at,up,20.0,aspect_ratio,aperture,f_dist);

    auto scene = random_scene();
    

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

                Ray3 ray = cam.getRay(u,v);

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
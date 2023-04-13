#include <iostream>
#include "vec3.h"
#include "ray3.h"
#include "sphere.h"
#include "util.h"
#include "hit.h"
#include <cassert>
#include <cmath>
#include "camera.h"
#include "bvh.h"
#include "rect.h"
#include <memory>

Color3 background(const Ray3& ray){
    double t = (ray.getDirection().y() + 1.)*.5;

    return Color3{1.0,1.0,1.0}*(1.-t) + Color3{.54,.81,.94}*t;
}

Color3 shade(const Ray3& ray,const Hittable& scene,int depth,bool has_background){

    if(depth <= 0){
        return Color3{0.0,0.0,0.0};
    }

    std::optional<Hit> hit{scene.getHit(ray,0.001,INF_DOUBLE)};


    if(hit.has_value()){

        auto material = hit.value().material;
        Ray3 out{};
        Color3 attenuation{};
        Color3 color(material->emission(hit.value().u,hit.value().v,hit.value().point));
        if(material->scatter(ray,hit.value(),out,attenuation)){
            color += shade(out,scene,depth-1,has_background)*attenuation;
        }
        return color;
    }

    if(has_background) return background(ray);
    //Otherwise return no light
    return Color3{0.0};
}

void ouputColor(const Color3& color){

    //Gamma 2 corrected color (gamma = 2 for 1/gamma power)
    Color3 outColor{sqrt(color.r()),sqrt(color.g()),sqrt(color.b())};

    std::cout << 
    static_cast<int>(outColor.r()*255.999) << " " <<
    static_cast<int>(outColor.g()*255.999) << " " <<
    static_cast<int>(outColor.b()*255.999) << " ";
}


HitList random_scene(bool use_checker) {
    HitList scene;

    std::shared_ptr<Material> ground_material;

    if(use_checker){
        auto white = std::make_shared<FlatTexture>(Color3{1.0});
        auto black = std::make_shared<FlatTexture>(Color3{0.0});
        ground_material = std::make_shared<Lambertian>(std::make_shared<CheckerTexture>(white,black,4.0));
    }else{
        ground_material = std::make_shared<Lambertian>(std::make_shared<FlatTexture>(Color3(0.5, 0.5, 0.5)));
    }

    scene.add(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random();
            Point3 center(a + 0.9*random(), 0.2, b + 0.9*random());

            if ((center - Point3(4, 0.2, 0)).norm() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = std::make_shared<FlatTexture>(Color3::random_vec3(0.0,1.0) * Color3::random_vec3(0.0,1.0));
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    Point3 center_end = center + Vec3(0.0,random_range(0.0,0.5),0.0);
                    scene.add(std::make_shared<MovingSphere>(center,center_end, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = std::make_shared<FlatTexture>(Color3::random_vec3(0.5, 1));
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

    auto material2 = std::make_shared<Lambertian>(std::make_shared<FlatTexture>(Color3(0.4, 0.2, 0.1)));
    scene.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(std::make_shared<FlatTexture>(Color3(0.7, 0.6, 0.5)), 0.0);
    scene.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));


    //return scene;
    return HitList(std::make_shared<BVHNode>(scene,0.0,1.0));
}

BVHNode test_scene_with_bvh(int size){
    HitList scene;

    auto ground_material = std::make_shared<Lambertian>(std::make_shared<FlatTexture>(Color3(0.5, 0.5, 0.5)));
    auto ball_material = std::make_shared<Lambertian>(std::make_shared<FlatTexture>(Color3(0.8, 0.3, 0.3)));

    scene.add(std::make_shared<Sphere>(Point3(0,-1001,0), 1000, ground_material));

    for(int i = -size;i < size;i++){
        for(int j = -size;j < size;j++){
            scene.add(std::make_shared<Sphere>(Point3(-1 + 2*i,0,-1 + 2*j), 0.75, ball_material));
        }
    }

    return BVHNode(scene,0.0,1.0);
}

HitList test_scene_without_bvh(int size){
    HitList scene;

    auto ground_material = std::make_shared<Lambertian>(std::make_shared<FlatTexture>(Color3(0.5, 0.5, 0.5)));
    auto ball_material = std::make_shared<Lambertian>(std::make_shared<FlatTexture>(Color3(0.8, 0.3, 0.3)));

    scene.add(std::make_shared<Sphere>(Point3(0,-1001,0), 1000, ground_material));

    for(int i = -size;i < size;i++){
        for(int j = -size;j < size;j++){
            scene.add(std::make_shared<Sphere>(Point3(-1 + 2*i,0,-1 + 2*j), 0.75, ball_material));
        }
    }

    return scene;
}

HitList two_spheres(){
    HitList scene;

    auto checker = std::make_shared<CheckerTexture>(
        std::make_shared<FlatTexture>(Color3{0.2,0.3,0.1}),
        std::make_shared<FlatTexture>(Color3{0.9,0.9,0.9}),
        4.0
    );

    scene.add(std::make_shared<Sphere>(Point3(0,-10, 0), 10, std::make_shared<Lambertian>(checker)));
    scene.add(std::make_shared<Sphere>(Point3(0,10, 0), 10, std::make_shared<Lambertian>(checker)));

    return scene;
}

HitList perlin_scene(){
    HitList scene;

    auto marble = std::make_shared<NoiseTexture>(2.0);

    auto checker = std::make_shared<CheckerTexture>(
        std::make_shared<FlatTexture>(Color3{0.1}),
        std::make_shared<FlatTexture>(Color3{1.0})
    );

    auto earth = std::make_shared<ImageTexture>("../assets/images/earthmap.jpg");


    scene.add(std::make_shared<Sphere>(Point3(0,-1000, 0), 1000, std::make_shared<Metal>(checker,0.0)));
    scene.add(std::make_shared<Sphere>(Point3(10,10, 0), 10, std::make_shared<Lambertian>(marble)));
    scene.add(std::make_shared<Sphere>(Point3(-10,10, 0), 10, std::make_shared<Lambertian>(earth)));


    return scene;
}

HitList light_test_1(){

    HitList scene;

    auto marble = std::make_shared<NoiseTexture>(2.0);

    auto checker = std::make_shared<CheckerTexture>(
        std::make_shared<FlatTexture>(Color3{0.1}),
        std::make_shared<FlatTexture>(Color3{1.0}),
        0.25
    );

    auto light = std::make_shared<DiffuseLight>(Color3{2.});


    scene.add(std::make_shared<Sphere>(Point3(0,-1000, 0), 1000, std::make_shared<Lambertian>(checker)));
    scene.add(std::make_shared<Sphere>(Point3(0,5, 10), 5, std::make_shared<Lambertian>(marble)));
    scene.add(std::make_shared<Sphere>(Point3(-15,10, 5), 5, light));
    scene.add(std::make_shared<Sphere>(Point3(15,10, 5), 5, light));
    scene.add(std::make_shared<RectXY>(-10,-5,5,10,20,light));
    scene.add(std::make_shared<RectXZ>(5,-5,5,-10,-5,light));
    scene.add(std::make_shared<RectXZ>(25,-5,5,-10,-5,light));
    scene.add(std::make_shared<RectYZ>(10,10,20,-10,-5,light));
    scene.add(std::make_shared<RectYZ>(-10,10,20,-10,-5,light));


    //scene.add(std::make_shared<RectYZ>(5,-7,7,-5,5,light));



    return scene;
}

HitList cornell_box(){

    HitList scene;

    auto red   = std::make_shared<Lambertian>(Color3(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(Color3(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(Color3(.12, .45, .15));
    auto light = std::make_shared<DiffuseLight>(Color3(15, 15, 15));

    scene.add(std::make_shared<RectYZ>(555,0, 555, 0, 555, green));
    scene.add(std::make_shared<RectYZ>(0,0, 555, 0, 555, red));
    scene.add(std::make_shared<RectXZ>(554,213, 343, 227, 332, light));
    scene.add(std::make_shared<RectXZ>(0,0, 555, 0, 555, white));
    scene.add(std::make_shared<RectXZ>(555,0, 555, 0, 555, white));
    scene.add(std::make_shared<RectXY>(555,0, 555, 0, 555,white));

    return scene;
}

int main(int argc,char** argv){

    init_random();


    //Image params
    double aspect_ratio = 16.0/9.0;
    int WIDTH = 400;
    int HEIGHT = static_cast<int>(WIDTH/aspect_ratio);

    //Sampling params
    int samples_per_pixel = 200;
    int max_depth = 50;


    Point3 from;
    Point3 at;
    Vec3 up;
    double f_dist;
    double aperture;

    Camera cam;

    int scene_number;
    int num_scenes = 6;


    if(argc != 2){
        std::cerr << "Usage: *.exe <scene_count>\n";
        return 1;
    }

    int value = argv[1][0] - '0';

    if(value < 0 || value >= num_scenes){
        std::cerr << "Usage: *.exe <scene_count>\n";
        return 1;
    }

    scene_number = value;
    std::cerr << "Selected scene " << scene_number << std::endl;


    HitList scene;

    bool has_background = true;

    switch (scene_number)
    {
        case 0:
            from = Point3(13,2,3);
            at = Point3(0,0,0);
            up = Vec3(0,1,0);
            f_dist = 10.0;
            aperture = 0.1;
            cam = Camera(from,at,up,20.0,aspect_ratio,aperture,f_dist,0.0,1.0);
            scene = random_scene(false);
            break;
        case 1:
            from = Point3(13,2,3);
            at = Point3(0,0,0);
            up = Vec3(0,1,0);
            f_dist = 10.0;
            aperture = 0.0;
            cam = Camera(from,at,up,20.0,aspect_ratio,aperture,f_dist,0.0,1.0);
            scene = random_scene(true);
            break;

        case 2:
            from = Point3(13,2,3);
            at = Point3(0,0,0);
            up = Vec3(0,1,0);
            f_dist = 10.0;
            aperture = 0.0;
            cam = Camera(from,at,up,40.0,aspect_ratio,aperture,f_dist,0.0,1.0);
            scene = two_spheres();
            break;
        case 3:
            from = Point3(-5,20,40);
            at = Point3(0,5,0);
            up = Vec3(0,1,0);
            f_dist = 10.0;
            aperture = 0.0;
            cam = Camera(from,at,up,40.0,aspect_ratio,aperture,f_dist,0.0,1.0);
            scene = perlin_scene();
            break;
        case 4:
            from = Point3(0,10,40);
            at = Point3(0,10,0);
            up = Vec3(0,1,0);
            f_dist = 10.0;
            aperture = 0.0;
            cam = Camera(from,at,up,60.0,aspect_ratio,aperture,f_dist,0.0,1.0);
            has_background = false;
            scene = light_test_1();
            break;
        case 5:
            from = Point3(278, 278, -800);
            at = Point3(278, 278, 0);
            up = Vec3(0,1,0);
            f_dist = 1.0;
            aperture = 0.0;
            aspect_ratio = 1.0;
            HEIGHT = static_cast<int>(WIDTH/aspect_ratio);
            cam = Camera(from,at,up,40.0,aspect_ratio,aperture,f_dist,0.0,1.0);
            has_background = false;
            scene = cornell_box();
            break;

        default:
            break;
    }

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


                color += shade(ray,scene,max_depth,has_background);
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
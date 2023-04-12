#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray3.h"

class Camera{
    private:  
        double fov;
        double aspect_ratio;
        Vec3 eye;
        Vec3 lower_left;
        Vec3 right;
        Vec3 up;
        double lens_radius;
        double initial_time,final_time;
    public:

        Camera();

        //Focal dist specifies the distance to the image plane where
        //everything is in focus
        Camera(Vec3 eye,Vec3 lookAt,Vec3 iup,
            double fov,double aspect_ratio,
            double aperture,
            double focus_dist,
            double initial_time,
            double final_time
        );
        Ray3 getRay(double u,double v) const;
};


#endif
#include "camera.h"
#include <cmath>
#include "util.h"

Camera::Camera()
{
    
}


Camera::Camera(Vec3 eye,Vec3 lookAt,Vec3 iup,
            double fov,double aspect_ratio,double aperture,
            double focus_dist,
            double initial_time = 0.0,
            double final_time = 0.0
)
:fov{fov},aspect_ratio{aspect_ratio},eye{eye},up{up},initial_time{initial_time},final_time{final_time}
{
    double view_height = 2.0*tan(deg_to_rad(0.5*fov));
    double view_width = aspect_ratio * view_height;


    Vec3 lookDir = (lookAt - eye).normalize();
    Vec3 tempRight = lookDir.cross(iup).normalize();
    Vec3 tempUp = tempRight.cross(lookDir).normalize();


    right = tempRight * view_width*focus_dist;
    up = tempUp * view_height*focus_dist;
    lower_left = eye - right*0.5 - up*0.5 + lookDir*focus_dist;
    lens_radius = 0.5 * aperture;
}

Ray3 Camera::getRay(double u,double v) const{
    Vec3 deye = Vec3::random_unit_disk() * lens_radius;
    Point3 eye_adjusted = eye + right*deye.x() + up*deye.y();
    double random_time = random_range(initial_time,final_time);
    return Ray3(eye_adjusted,lower_left + right*u + up*v - eye_adjusted,random_time);
}

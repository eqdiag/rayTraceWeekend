#include "volume.h"
#include "util.h"

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary_object,std::shared_ptr<Texture> texture,double C)
:boundary_object{boundary_object},material{std::make_shared<Isotropic>(texture)},neg_inv_density{-1.0/C}
{

}

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> boundary_object,const Color3& color,double C)
:boundary_object{boundary_object},material{std::make_shared<Isotropic>(color)},neg_inv_density{-1.0/C}
{

}

std::optional<Hit> ConstantMedium::getHit(const Ray3& ray,double tmin,double tmax) const
{
    //Assumes convex boundary regions

    //First get two intersections (handles case when in the volume as well)
    //Basically enter and exit points since assumed convex
    auto hleft = boundary_object->getHit(ray,-INF_DOUBLE,INF_DOUBLE);
    if(!hleft.has_value()) return {};
    auto hright = boundary_object->getHit(ray,hleft.value().t + .00001,INF_DOUBLE);
    if(!hright.has_value()) return {};

    //Clamp values
    if(hleft.value().t < tmin ) hleft.value().t = tmin;
    if(hright.value().t > tmax ) hright.value().t = tmax;
    if(hleft.value().t >= hright.value().t) return {};
    if(hleft.value().t < 0) hleft.value().t = 0;

    double ray_length = ray.getDirection().norm();
    double dist_in_volume = (hright.value().t - hleft.value().t)/ray_length;
    double rand_hit_dist = neg_inv_density * log(random());

    if(rand_hit_dist > dist_in_volume) return {};

    Hit hit;
    hit.t = hleft.value().t + rand_hit_dist/ray_length;
    hit.point = ray.cast(hit.t);
    hit.normal = Vec3(0,1,0); //Doesn't matter because iso material
    hit.front_face = true; //Also doesn't matter
    hit.material = material;

    return hit;
}

bool ConstantMedium::getBoundingBox(double time0,double time1,AABB& box) const
{
    return boundary_object->getBoundingBox(time0,time1,box);
}
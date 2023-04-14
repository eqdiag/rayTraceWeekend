#include "instance.h"
#include "util.h"

Translation::Translation(const Vec3& translation,std::shared_ptr<Hittable> object)
:translation{translation},object{object}
{

}

std::optional<Hit> Translation::getHit(const Ray3& ray,double tmin,double tmax) const
{
    Ray3 new_ray(ray.getPoint() - translation,ray.getDirection(),ray.getTime());
    auto hit = object->getHit(new_ray,tmin,tmax);
    if(!hit.has_value()) return {};

    hit.value().point += translation;
    hit.value().set_face_normal(new_ray,hit.value().normal);

    return hit;
}

bool Translation::getBoundingBox(double time0,double time1,AABB& box) const{
    AABB temp_box;
    if(!object->getBoundingBox(time0,time1,temp_box)) return false;
    box = AABB(
        temp_box.getMin() + translation,
        temp_box.getMax() + translation
    );  
    return true;
}

RotateY::RotateY(double angle,std::shared_ptr<Hittable> object)
:object{object}
{
    double rad = deg_to_rad(angle);
    sin_angle = sin(rad);
    cos_angle = cos(rad);
    has_box = object->getBoundingBox(0, 1, bbox);

    Point3 min( INF_DOUBLE,  INF_DOUBLE,  INF_DOUBLE);
    Point3 max(-INF_DOUBLE, -INF_DOUBLE, -INF_DOUBLE);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i*bbox.getMax().x() + (1-i)*bbox.getMin().x();
                auto y = j*bbox.getMax().y() + (1-j)*bbox.getMin().y();
                auto z = k*bbox.getMax().z() + (1-k)*bbox.getMin().z();

                auto newx =  cos_angle*x + sin_angle*z;
                auto newz = -sin_angle*x + cos_angle*z;

                Vec3 temp(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], temp[c]);
                    max[c] = fmax(max[c], temp[c]);
                }
            }
        }
    }

    bbox = AABB(min, max);
}

std::optional<Hit> RotateY::getHit(const Ray3& ray,double tmin,double tmax) const
{
    auto origin = ray.getPoint();
    auto direction = ray.getDirection();

    origin[0] = cos_angle*ray.getPoint()[0] - sin_angle*ray.getPoint()[2];
    origin[2] = sin_angle*ray.getPoint()[0] + cos_angle*ray.getPoint()[2];

    direction[0] = cos_angle*ray.getDirection()[0] - sin_angle*ray.getDirection()[2];
    direction[2] = sin_angle*ray.getDirection()[0] + cos_angle*ray.getDirection()[2];

    Ray3 rotated_ray(origin, direction, ray.getTime());

    auto hit = object->getHit(rotated_ray, tmin, tmax);

    if (!hit.has_value()) return {};

    auto p = hit.value().point;
    auto normal = hit.value().normal;

    p[0] =  cos_angle*hit.value().point[0] + sin_angle*hit.value().point[2];
    p[2] = -sin_angle*hit.value().point[0] + cos_angle*hit.value().point[2];

    normal[0] =  cos_angle*hit.value().normal[0] + sin_angle*hit.value().normal[2];
    normal[2] = -sin_angle*hit.value().normal[0] + cos_angle*hit.value().normal[2];

    hit.value().point = p;
    hit.value().set_face_normal(rotated_ray, normal);

    return hit;
}

bool RotateY::getBoundingBox(double time0,double time1,AABB& box) const
{
    if(!has_box) return false;
    box = bbox;
    return true;
}
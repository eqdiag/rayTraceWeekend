#include "rect.h"

RectXY::RectXY(double z,double xmin,double xmax,double ymin,double ymax,std::shared_ptr<Material> material)
:z{z},xmin{xmin},xmax{xmax},ymin{ymin},ymax{ymax},material{material}
{

}

std::optional<Hit> RectXY::getHit(const Ray3& ray,double tmin,double tmax) const
{
    double t = (z - ray.getPoint().z())/ ray.getDirection().z();
    if(t < tmin || t > tmax) return {};

    Point3 p = ray.cast(t);
    if(p.x() < xmin || p.x() > xmax) return {};
    if(p.y() < ymin || p.y() > ymax) return {};

    Vec3 normal(0.0,0.0,1.0);

    Hit hit;
    hit.t = t;
    hit.point = p;
    hit.front_face = ray.getDirection().dot(normal) < 0.0;
    hit.set_face_normal(ray,normal);
    hit.material = material;
    hit.u = (p.x() / (xmax - xmin));
    hit.v = (p.y() / (ymax - ymin));
    return std::make_optional<Hit>(hit);
}

bool RectXY::getBoundingBox(double time0,double time1,AABB& box) const
{
    box = AABB(Point3(xmin,ymin,z - 0.0001),Point3(xmax,ymax,z + 0.0001));
    return true;
}

RectXZ::RectXZ(double y,double xmin,double xmax,double zmin,double zmax,std::shared_ptr<Material> material)
:y{y},xmin{xmin},xmax{xmax},zmin{zmin},zmax{zmax},material{material}
{

}

std::optional<Hit> RectXZ::getHit(const Ray3& ray,double tmin,double tmax) const
{
    double t = (y - ray.getPoint().y())/ ray.getDirection().y();
    if(t < tmin || t > tmax) return {};

    Point3 p = ray.cast(t);
    if(p.x() < xmin || p.x() > xmax) return {};
    if(p.z() < zmin || p.z() > zmax) return {};

    Vec3 normal(0.0,-1.0,0.0);

    Hit hit;
    hit.t = t;
    hit.point = p;
    hit.front_face = ray.getDirection().dot(normal) < 0.0;
    hit.set_face_normal(ray,normal);
    hit.material = material;
    hit.u = (p.x() / (xmax - xmin));
    hit.v = (p.z() / (zmax - zmin));
    return std::make_optional<Hit>(hit);
}

bool RectXZ::getBoundingBox(double time0,double time1,AABB& box) const
{
    box = AABB(Point3(xmin,y - 0.0001,zmin),Point3(xmax,y + 0.0001,zmax));
    return true;
}

RectYZ::RectYZ(double x,double ymin,double ymax,double zmin,double zmax,std::shared_ptr<Material> material)
:x{x},ymin{ymin},ymax{ymax},zmin{zmin},zmax{zmax},material{material}
{

}

std::optional<Hit> RectYZ::getHit(const Ray3& ray,double tmin,double tmax) const
{
    double t = (x - ray.getPoint().x())/ ray.getDirection().x();
    if(t < tmin || t > tmax) return {};

    Point3 p = ray.cast(t);
    if(p.y() < ymin || p.y() > ymax) return {};
    if(p.z() < zmin || p.z() > zmax) return {};

    Vec3 normal(-1.0,0.0,0.0);

    Hit hit;
    hit.t = t;
    hit.point = p;
    hit.front_face = ray.getDirection().dot(normal) < 0.0;
    hit.set_face_normal(ray,normal);
    hit.material = material;
    hit.u = (p.z() / (zmax - zmin));
    hit.v = (p.y() / (ymax - ymin));
    return std::make_optional<Hit>(hit);
}

bool RectYZ::getBoundingBox(double time0,double time1,AABB& box) const
{
    box = AABB(Point3(x - 0.0001,ymin,zmin),Point3(x + 0.0001,ymax,zmax));
    return true;
}
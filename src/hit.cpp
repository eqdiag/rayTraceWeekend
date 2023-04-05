#include "hit.h"

Hit::Hit(double t,Point3 point,Vec3 normal,bool front_face)
:t{t},point{point},normal{normal},front_face{front_face}
{

}

Hit::Hit()
{

}

std::ostream& operator<<(std::ostream& os,const Hit& hit){
    os << "t: " << hit.t << "\n" <<
    "P: " << hit.point << "\n" <<
    "N: " << hit.normal << "\n" <<
    "Front Facing: " << hit.front_face << "\n" << 
    std::endl;

    return os;
}


HitList::HitList(){

}

HitList::HitList(std::shared_ptr<Hittable> object){
    add(object);
}

void HitList::add(std::shared_ptr<Hittable> object){
    objects.push_back(object);
}

void HitList::empty(){
    objects.clear();
}

std::optional<Hit> HitList::getHit(const Ray3& ray,double tmin,double tmax) const{
    std::optional<Hit> closest{};
    double current_t = tmax;
    for(auto& obj: objects){
        auto hit = obj->getHit(ray,tmin,tmax);
        if(hit.has_value()){
            //Update if closer intersection found
            if(hit.value().t < current_t){
                closest = std::make_optional<Hit>(hit.value());
                current_t = hit.value().t;
            }
        }
    }

    return closest;
}
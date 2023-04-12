#include "bvh.h"
#include <algorithm>
#include "util.h"
#include <iostream>


BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>>& objects,size_t start,size_t end,double time0,double time1)
{
    int random_axis = rand_int(0,2);
    auto predicate = (random_axis == 0) ? compareBox_x : (random_axis == 1) ? compareBox_y : compareBox_z;

    auto len = end - start;

    if(len == 1){
        left_child = objects[start];
        right_child = objects[start];
    }else if(len == 2){
        left_child = objects[start];
        right_child = objects[start+1];
    }else{
        std::sort(objects.begin() + start,objects.begin() + end,predicate);

        auto mid = start + len/2;

        //Crudely split objects here
        left_child = std::make_shared<BVHNode>(objects,start,mid,time0,time1);
        right_child = std::make_shared<BVHNode>(objects,mid,end,time0,time1);
    }

    //Merge boxes based on recursion
    AABB left_box,right_box;

    if(!left_child->getBoundingBox(time0,time1,left_box) || !right_child->getBoundingBox(time0,time1,right_box)){
        std::cerr << "BVH node can't compute bounding box of child!\n";
    }

    bbox = left_box.mergeBoxes(right_box);
}

BVHNode::BVHNode(HitList& hitlist,double time0,double time1)
:BVHNode(hitlist.getObjectsMut(),0,hitlist.getObjects().size(),time0,time1)
{

}


std::optional<Hit> BVHNode::getHit(const Ray3& ray,double tmin,double tmax) const{
    if(!bbox.isHit(ray,tmin,tmax)) return {};

    auto left_hit = left_child->getHit(ray,tmin,tmax);
    if(left_hit.has_value()){
        auto right_hit = right_child->getHit(ray,tmin,tmax);
        if(right_hit.has_value()){
            if(left_hit.value().t < right_hit.value().t){
                return left_hit;
            }
            return right_hit;
        }
        return left_hit;
    }

    auto right_hit = right_child->getHit(ray,tmin,tmax);
    if(right_hit.has_value()) return right_hit;

    return {};
}

bool BVHNode::getBoundingBox(double time0,double time1,AABB& box) const
{
    box = bbox;
    return true;
}

bool compareBox(const std::shared_ptr<Hittable> a,const std::shared_ptr<Hittable> b,int axis){
    AABB left_box,right_box;

    if(!a->getBoundingBox(0,0,left_box) || !b->getBoundingBox(0,0,right_box)){
        std::cerr << "BVH node compare: couldn't get bounding box\n";
    }    

    if(axis == 0){
        return left_box.getMin().x() < right_box.getMin().x();
    }else if(axis == 1){
        return left_box.getMin().y() < right_box.getMin().y();
    }
    return left_box.getMin().z() < right_box.getMin().z();
}

bool compareBox_x(const std::shared_ptr<Hittable> a,const std::shared_ptr<Hittable> b)
{
    return compareBox(a,b,0);
}

bool compareBox_y(const std::shared_ptr<Hittable> a,const std::shared_ptr<Hittable> b)
{
    return compareBox(a,b,1);
}

bool compareBox_z(const std::shared_ptr<Hittable> a,const std::shared_ptr<Hittable> b)
{
    return compareBox(a,b,2);
}
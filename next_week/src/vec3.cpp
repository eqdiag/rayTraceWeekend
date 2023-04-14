#include "vec3.h"
#include <cmath>
#include <cassert>
#include "util.h"
#include <iostream>

Vec3::Vec3()
:v{0.,0.,0.}
{

}

Vec3::Vec3(double x)
:v{x,x,x}
{

}


Vec3::Vec3(double x, double y, double z)
:v{x,y,z}
{

}

Vec3::Vec3(const Vec3& rhs)
:v{rhs.x(),rhs.y(),rhs.z()}
{

}

Vec3& Vec3::operator=(const Vec3& rhs){
    assert(this != &rhs);
    v[0] = rhs.x();
    v[1] = rhs.y();
    v[2] = rhs.z();
    return *this;
}

double Vec3::x() const{
    return v[0];
}

double Vec3::y() const{
    return v[1];
}

double Vec3::z() const{
    return v[2];
}

double Vec3::r() const{
    return v[0];
}

double Vec3::g() const{
    return v[1];
}

double Vec3::b() const{
    return v[2];
}

Vec3 Vec3::operator-() const{
    return Vec3(-v[0],-v[1],-v[2]);
}

Vec3 Vec3::operator+(const Vec3& rhs) const{
    return Vec3(v[0] + rhs.x(),v[1] + rhs.y(),v[2] + rhs.z());
}

Vec3 Vec3::operator-(const Vec3& rhs) const{
    return Vec3(v[0] - rhs.x(),v[1] - rhs.y(),v[2] - rhs.z());
}

Vec3 Vec3::operator*(const Vec3& rhs) const{
    return Vec3(v[0]*rhs.x(),v[1]*rhs.y(),v[2]*rhs.z());
}


Vec3 Vec3::operator*(double scalar) const{
    return Vec3(v[0]*scalar,v[1]*scalar,v[2]*scalar);
}

Vec3 Vec3::operator/(double scalar) const{
    return *this * (1.0 / scalar);
}

double Vec3::operator[](int index) const
{
    return v[index];
}

double& Vec3::operator[](int index)
{
    return v[index];
}

Vec3& Vec3::operator+=(const Vec3& rhs){
    v[0]+= rhs.x();
    v[1]+= rhs.y();
    v[2]+= rhs.z();
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& rhs){
    v[0]-= rhs.x();
    v[1]-= rhs.y();
    v[2]-= rhs.z();
    return *this;
}

Vec3& Vec3::operator*=(double scalar){
    v[0]*= scalar;
    v[1]*= scalar;
    v[2]*= scalar;
    return *this;
}

Vec3& Vec3::operator/=(double scalar){
    return *this *= (1.0/ scalar);
}

double Vec3::dot(const Vec3& rhs) const{
    return v[0]*rhs.x() + v[1]*rhs.y() + v[2]*rhs.z();
}

Vec3 Vec3::cross(const Vec3& rhs) const{
    return Vec3(
        v[1]*rhs.z() - v[2]*rhs.y(),
        v[2]*rhs.x() - v[0]*rhs.z(),
        v[0]*rhs.y() - v[1]*rhs.x()
    );
}

double Vec3::norm2() const{
    return this->dot(*this);
}

double Vec3::norm() const{
    return sqrt(norm2());
}

Vec3 Vec3::normalize() const{
    return *this / norm();
}

bool Vec3::effectively_zero() const{
    return norm2() < 0.0001;
}

Vec3 Vec3::reflect(const Vec3& normal) const{
    return *this - normal*2.0*this->dot(normal);
}

Vec3 Vec3::refract(const Vec3& normal,double ir) const{
 
    double cos_theta = -this->dot(normal);
    Vec3 r_out_perp =  (*this + normal*cos_theta) * ir;
    Vec3 r_out_parallel = normal * -sqrt(fabs(1.0 - r_out_perp.norm2()));
    return r_out_perp + r_out_parallel;
}


Vec3 Vec3::random_vec2(double min,double max){
    return Vec3(random_range(min,max),random_range(min,max),0.0);
}

Vec3 Vec3::random_vec3(){
    return Vec3(random(),random(),random());
}

Vec3 Vec3::random_vec3(double min,double max){
    return Vec3(random_range(min,max),random_range(min,max),random_range(min,max));
}

Vec3 Vec3::random_unit_sphere(){
    while(true){
        Vec3 v(random_vec3(-1.,1.));
        if(v.norm2() > 1) continue;
        return v;
    }
}

Vec3 Vec3::random_unit_disk(){
    while(true){
        Vec3 v(random_vec2(-1.,1.));
        if(v.norm2() > 1.0) continue;
        return v;
    }
}


Vec3 Vec3::random_unit_vec3(){
    return random_unit_sphere().normalize();
}




std::ostream& operator<<(std::ostream& os,const Vec3& v){
    os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
    return os;
}


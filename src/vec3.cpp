#include "vec3.h"
#include <cmath>
#include <cassert>

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

Vec3 Vec3::operator*(double scalar) const{
    return Vec3(v[0]*scalar,v[1]*scalar,v[2]*scalar);
}

Vec3 Vec3::operator/(double scalar) const{
    return *this * (1.0 / scalar);
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
    return *this / norm2();
}

bool Vec3::effectively_zero() const{
    return norm2() < 0.0001;
}


std::ostream& operator<<(std::ostream& os,const Vec3& v){
    os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
    return os;
}

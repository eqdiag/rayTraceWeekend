#ifndef VEC3_H
#define VEC3_H

#include <ostream>

class Vec3{
    private:
        double v[3];

    public: 

        Vec3();
        Vec3(double x);
        Vec3(double x,double y,double z);
        Vec3(const Vec3& rhs);
        Vec3& operator=(const Vec3& rhs);

        double x() const;
        double y() const;
        double z() const;

        double r() const;
        double g() const;
        double b() const;

        //Math operations

        Vec3 operator-() const;

        Vec3 operator+(const Vec3& rhs) const;
        Vec3 operator-(const Vec3& rhs) const;
        Vec3 operator*(const Vec3& rhs) const;

        Vec3 operator*(double scalar) const;
        Vec3 operator/(double scalar) const;

        Vec3& operator+=(const Vec3& rhs);
        Vec3& operator-=(const Vec3& rhs);
        Vec3& operator*=(double scalar);
        Vec3& operator/=(double scalar);

        double dot(const Vec3& rhs) const;
        Vec3 cross(const Vec3& rhs) const;

        double norm2() const;
        double norm() const;
        Vec3 normalize() const;

        bool effectively_zero() const;

        Vec3 reflect(const Vec3& normal) const;
        Vec3 refract(const Vec3& normal,double ir) const;

        static Vec3 random_vec2(double min,double max);
        static Vec3 random_vec3();
        static Vec3 random_vec3(double min,double max);
        static Vec3 random_unit_sphere();
        //3rd component always zero
        static Vec3 random_unit_disk();
        static Vec3 random_unit_vec3();

};

std::ostream& operator<<(std::ostream& os,const Vec3& v);


using Point3 = Vec3;
using Color3 = Vec3;



#endif
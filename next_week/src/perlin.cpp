#include "perlin.h"
#include "util.h"
#include <cmath>

#include <iostream>

Perlin::Perlin()
{

    values = new Vec3[num_points];
    for(int i = 0;i < num_points;i++){
        values[i] = Vec3::random_vec3(-1,1).normalize();
    }

    x_values = generate_permutation();
    y_values = generate_permutation();
    z_values = generate_permutation();
}

Perlin::~Perlin()
{
    delete[] values;
    delete[] x_values;
    delete[] y_values;
    delete[] z_values;
}


double Perlin::noise(const Point3& p) const
{
    int x = static_cast<int>(floor(p.x()));
    int y = static_cast<int>(floor(p.y()));
    int z = static_cast<int>(floor(p.z()));

    double u = p.x() - floor(p.x());
    double v = p.y() - floor(p.y());
    double w = p.z() - floor(p.z());


    
    //Generate random corner vectors on cube
    Vec3 c[2][2][2];

    for (int di=0; di < 2; di++)
    {
        for (int dj=0; dj < 2; dj++)
        {
            for (int dk=0; dk < 2; dk++)
            {
                c[di][dj][dk] = 
                values[
                    x_values[(x+di) & 255] ^
                    y_values[(y+dj) & 255] ^
                    z_values[(z+dk) & 255]
                ];
            }
        }
    }
                
    return interpolate(u,v,w,c);
}

double Perlin::turb(const Point3& p,int layers) const
{
    double sum = 0;
    Point3 q = p;
    double amplitude = 1.0;
    for(int i =0;i<layers;i++){
        sum += amplitude*noise(q);
        amplitude *= 0.5;
        q *= 2.0;
    }

    return fabs(sum);
}


double Perlin::interpolate(double u,double v,double w,Vec3 c[2][2][2]) const{
    auto sum = 0.0;

    double uu = u*u*(3-2*u);
    double vv = v*v*(3-2*v);
    double ww = w*w*(3-2*w);

    for (int i=0; i < 2; i++){
        for (int j=0; j < 2; j++){
            for (int k=0; k < 2; k++)
            {
                sum += (i*uu + (1-i)*(1-uu))*
                        (j*vv + (1-j)*(1-vv))*
                        (k*ww + (1-k)*(1-ww))*
                        c[i][j][k].dot(Vec3(u,v,w) - Vec3(i,j,k));
            }
        }
    }

    return sum;
}


int * Perlin::generate_permutation() const
{
    int * p = new int[num_points];
    //init array
    for(int i =0;i < num_points;i++){
        p[i] = i;
    }

    //Do random swaps
    for(int i = num_points-1;i > 0;i--){
        int new_index = rand_int(0,i);
        int temp = p[i];
        p[i] = p[new_index];
        p[new_index] = temp;
    }
    return p;
}

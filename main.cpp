#include <iostream>
#include <fstream>

#include "rangen.h"

#include "vec3.h"
#include "ray.h"
#include "camera.h"

#include "sphere.h"
#include "hitablelist.h"

#include "material.h"
#include "lambertian.h"
#include "metal.h"

#include "float.h"

vec3 color(const ray &r, hitable *world, int depth)
{
    hit_record rec;
    if(world->hit(r, 0.001, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if ( depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, ++depth);
        }
        else {
            return vec3(0.0, 0.0, 0.0);
        }        
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    
    
    std::ofstream myfile("test.ppm");

    myfile << "P3\n" << nx << " " << ny << "\n255\n";
    
    hitable *list[4];
    
    list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1.0, 0.0, -1.0), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
    list[3] = new sphere(vec3(-1.0, 0.0, -1.0), 0.5, new metal(vec3(0.8, 0.8, 0.8)));
    
    hitable *world = new hitable_list(list, 4);
    
    camera cam;

    for(int j = ny - 1; j >= 0; --j) {
        for(int i = 0; i < nx; ++i) {
            vec3 col(0.0, 0.0, 0.0);
            
            for(int s = 0; s < ns; ++s) {
                float u = float(i + dis(gen)) / float(nx);
                float v = float(j + dis(gen)) / float(ny);
                
                ray r = cam.get_ray(u, v);
                
                //vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }
            
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());

            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }

    myfile.close();
}

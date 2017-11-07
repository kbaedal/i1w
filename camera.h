#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ray.h"

class camera 
{
    public:   
        camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) { // vfov is top to bottom in degrees
            vec3 u, v, w;
            float theta = vfov * kPI / 180.0;
            float half_height = tan(theta/2.0);
            float half_width = aspect * half_height;
            origin = lookfrom;
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);
            lower_left_corner = origin - half_width * u - half_height * v - w;
            horizontal = 2.0 * half_width * u;
            vertical = 2.0 * half_height * v;
            
        }
        ray get_ray(float s, float t)
        {
            return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
        }
        
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 origin;
};

#endif // __CAMERA_H__
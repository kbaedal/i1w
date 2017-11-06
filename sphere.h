#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "hitable.h"

class sphere : public hitable
{
    public:
        sphere() {};
        sphere(vec3 cen, float r) : center(cen), radius(r) {}
        
        virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
        
        vec3    center;
        float   radius;
};

bool sphere::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    vec3 oc = r.origin() - center;
    
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    
    float discriminant = b * b - 4.0 * a * c;
    
    if( discriminant > 0.0) {
        float temp = (-b - sqrt(discriminant)) / (2.0 * a);
        
        if(temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            
            return true;
        }
        
        temp = (-b + sqrt(discriminant)) / (2.0 * a);
        
        if(temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            
            return true;
        }        
    }
    
    return false;
}

#endif // __SPHERE_H__
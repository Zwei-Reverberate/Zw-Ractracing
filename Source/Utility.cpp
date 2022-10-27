#include "..\Header\Utility.h"

vec3 random_in_unit_sphere()
{
    while (true) 
    {
        auto p = random(-1, 1);
        if (p.squared_length() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3& normal)
{
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

#ifndef RAY_H
#define RAY_H
#include "../Header/vec3.h" // vec3 表示一个三维向量

class Ray
{
public:
    point3 orig;
    vec3 dir;
public:
    Ray();
    Ray(const point3& origin, const vec3& direction);
    point3 origin() const;
    vec3 direction() const;
    point3 at(double t) const;
};

#endif


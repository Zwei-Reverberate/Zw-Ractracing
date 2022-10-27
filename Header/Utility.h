#ifndef UTILITY_H
#define UTILITY_H
#include <cmath>
#include <limits>
#include <random>

#include "../Header/vec3.h"

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double random_double() 
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max)
{
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

// ÏÞ¶¨ x µÄ·¶Î§
inline double clamp(double x, double min, double max) 
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline vec3 random_in_unit_disk() 
{
    vec3 p;
    do 
    {
        p = 2.0 * vec3(random_double(), random_double(), 0) - vec3(1, 1, 0);
    } 
    while (dot(p, p) >= 1.0);
    return p;
}

inline static vec3 random()
{
    return vec3(random_double(), random_double(), random_double());
}
inline static vec3 random(double min, double max)
{
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

vec3 random_in_unit_sphere();
vec3 random_unit_vector();
vec3 random_in_hemisphere(const vec3& normal);

#endif


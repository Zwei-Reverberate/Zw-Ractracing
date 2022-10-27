#ifndef CAMERA_H
#define CAMERA_H
#include "../Header/vec3.h"
#include "../Header/Utility.h"
#include "../Header/Ray.h"
class Camera
{
public:
    point3 origin;
    vec3 horizontal;
    vec3 vertical; 
    point3 lower_left_corner; 

public:
	Camera();
    Camera
    (
        point3 lookfrom,
        point3 lookat,
        vec3   vup,
        double vfov, // vertical field-of-view in degrees
        double aspect_ratio
    );
    Ray get_ray(double s, double t);
};

#endif

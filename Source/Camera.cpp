#include "..\Header\Camera.h"

Camera::Camera()
{
}

Camera::Camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio)
{
    auto theta = degrees_to_radians(vfov);
    auto h = tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    auto w = unit_vector(lookfrom - lookat); // z Öá
    auto u = unit_vector(cross(vup, w)); // x Öá
    auto v = cross(w, u); // y Öá

    origin = lookfrom;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    
}

Ray Camera::get_ray(double s, double t)
{
    return Ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
}

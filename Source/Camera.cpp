#include "..\Header\Camera.h"

Camera::Camera()
{
}

Camera::Camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist)
{
    auto theta = degrees_to_radians(vfov);
    auto h = tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w = unit_vector(lookfrom - lookat); // z Öá
    u = unit_vector(cross(vup, w)); // x Öá
    v = cross(w, u); // y Öá

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

    lens_radius = aperture / 2;
}

Ray Camera::get_ray(double s, double t)
{
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();

    return Ray
    (
        origin + offset,
        lower_left_corner + s * horizontal + t * vertical - origin - offset
    );
}

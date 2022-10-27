#include "..\Header\Material.h"

Lambertian::Lambertian(const color& a)
{
	albedo = a;
}

bool Lambertian::scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const
{
    auto scatter_direction = rec.normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

Metal::Metal()
{
}

Metal::Metal(const color& a)
{
    albedo = a;
}

bool Metal::scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const
{
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

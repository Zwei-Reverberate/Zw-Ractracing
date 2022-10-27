#include "..\Header\Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(point3 cen, double r, std::shared_ptr<Material> m)
{
	center = cen;
	radius = r;
	mat_ptr = m;
}

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	auto a = r.direction().squared_length();
	auto half_b = dot(oc, r.direction());
	auto c = oc.squared_length() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) 
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;

	return true;
}

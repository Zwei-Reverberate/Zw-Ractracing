#ifndef SPHERE_H
#define SPHERE_H
#include "../Header/Hittable.h"

class Sphere : public Hittable
{
public:
	point3 center;
	double radius;
	Sphere();
	Sphere(point3 cen, double r, std::shared_ptr<Material> m);
	std::shared_ptr<Material> mat_ptr;

	virtual bool hit
	(
		const Ray& r,
		double t_min,
		double t_max,
		hit_record& rec
	)const override;
};

#endif

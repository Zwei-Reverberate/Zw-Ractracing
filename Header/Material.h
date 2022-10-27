#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Header/Ray.h"
#include "../Header/Hittable.h"
#include "../Header/Utility.h"

class Material
{
public:
	virtual bool scatter
	(
		const Ray& r_in, //r_in为入射光线,
		const hit_record& rec, 
		vec3& attenuation, // attenuation 意思为衰减量
		Ray& scattered // scattered为散射光线
	) const = 0;
};


class Lambertian : public Material
{
public:
	color albedo; // 反射率

public:
	Lambertian(const color& a);
	virtual bool scatter
	(
		const Ray& r_in,
		const hit_record& rec,
		color& attenuation,
		Ray& scattered
	) const override;
};

class Metal : public Material
{
public:
	color albedo;
	double fuzz;

public:
	Metal();
	Metal(const color& a, double f);
	virtual bool scatter
	(
		const Ray& r_in,
		const hit_record& rec,
		color& attenuation,
		Ray& scattered
	) const override;
};

class Dielectric : public Material
{
public:
	double ir; // Index of Refraction

public:
	Dielectric();
	Dielectric(double index_of_refraction);
	virtual bool scatter
	(
		const Ray& r_in,
		const hit_record& rec,
		color& attenuation,
		Ray& scattered
	) const override;

private:
	static double reflectance(double cosine, double ref_idx) 
	{
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};

#endif

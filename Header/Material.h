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

public:
	Metal();
	Metal(const color& a);
	virtual bool scatter
	(
		const Ray& r_in,
		const hit_record& rec,
		color& attenuation,
		Ray& scattered
	) const override;
};

#endif

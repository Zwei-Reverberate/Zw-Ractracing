#ifndef HITTABLELIST_H
#define HITTABLELIST_H
#include "../Header/Hittable.h"
#include <memory>
#include <vector>

class HittableList :public Hittable
{
public:
	std::vector<std::shared_ptr<Hittable>> objects;

	HittableList();
	HittableList(std::shared_ptr<Hittable> object);
	void clear();
	void add(std::shared_ptr<Hittable> object);
	// 遍历数组中的所有物体，记录当前光线命中的最近的物体
	virtual bool hit
	(
		const Ray& r,
		double t_min,
		double t_max,
		hit_record& rec
	)const override;
};


#endif

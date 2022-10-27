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
	// ���������е��������壬��¼��ǰ�������е����������
	virtual bool hit
	(
		const Ray& r,
		double t_min,
		double t_max,
		hit_record& rec
	)const override;
};


#endif

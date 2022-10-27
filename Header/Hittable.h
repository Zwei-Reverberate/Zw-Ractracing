#ifndef HITTABLE_H
#define HITTABLE_H
#include "../Header/vec3.h"
#include "../Header/Ray.h"

// 此句声明使得可不包含 Material 头文件，防止重复包含
class Material;

struct hit_record
{
    point3 p; // 命中点坐标
    vec3 normal; // 命中点法线
    std::shared_ptr<Material> mat_ptr;
    double t; // 命中点法线
    bool front_face; // 标记正面

    inline void set_face_normal(const Ray& r, const vec3& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    Hittable();
    virtual bool hit
    (
        const Ray& r,
        double t_min, // 限定光线的最小长度
        double t_max, // 限定光线的最大长度
        hit_record& rec // 记录命中信息
    ) const = 0;
};


#endif


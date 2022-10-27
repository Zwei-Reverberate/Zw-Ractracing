#ifndef HITTABLE_H
#define HITTABLE_H
#include "../Header/vec3.h"
#include "../Header/Ray.h"

// �˾�����ʹ�ÿɲ����� Material ͷ�ļ�����ֹ�ظ�����
class Material;

struct hit_record
{
    point3 p; // ���е�����
    vec3 normal; // ���е㷨��
    std::shared_ptr<Material> mat_ptr;
    double t; // ���е㷨��
    bool front_face; // �������

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
        double t_min, // �޶����ߵ���С����
        double t_max, // �޶����ߵ���󳤶�
        hit_record& rec // ��¼������Ϣ
    ) const = 0;
};


#endif


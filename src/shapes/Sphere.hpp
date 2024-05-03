/*
** EPITECH PROJECT, 2024
** Sphere.hpp
** File description:
** sphere class
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "Vector3D.hpp"
    #include "Ray.hpp"
    #include "AShape.hpp"
    #include "Interval.hpp"
    #include "IMaterial.hpp"
    #include <memory>

namespace rtx
{
    class Sphere : public virtual rtx::AShape
    {
    private:
        double _radius;
        std::shared_ptr<rtx::IMaterial> _material;

    public:
        Sphere();
        Sphere(rtx::Point3D _center, double radius, std::shared_ptr<rtx::IMaterial> material);
        ~Sphere() = default;

        bool hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const override;
    };
}

#endif

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

namespace rtx
{
    class Sphere : public virtual rtx::AShape
    {
    public:
        Sphere();
        Sphere(rtx::Point3D center, double radius);
        ~Sphere() = default;

        double radius;

        bool hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const override;
    };
}

#endif

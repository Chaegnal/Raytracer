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
    #include "ITransformation.hpp"
    #include <memory>

namespace rtx
{
    class Sphere : public virtual rtx::AShape
    {
    private:
        double _radius;
        std::shared_ptr<rtx::IMaterial> _material;

        static void sphereHitsAngle(const rtx::Point3D& p, double& u, double& v);
    public:
        Sphere();
        Sphere(rtx::Point3D _center, double radius, std::shared_ptr<rtx::IMaterial> material);
        Sphere(rtx::Point3D _center, double radius, std::shared_ptr<rtx::IMaterial> material, std::shared_ptr<rtx::ITransformation> _transformation);
        ~Sphere() = default;

        bool hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const override;
    };
}

#endif

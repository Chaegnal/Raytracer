/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-yanis.harkouk
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
    #define CYLINDER_HPP_

    #include "Vector3D.hpp"
    #include "Ray.hpp"
    #include "AShape.hpp"
    #include "Interval.hpp"
    #include "IMaterial.hpp"
    #include <memory>

namespace rtx
{
    class Cylinder : public virtual rtx::AShape
    {
        public:
            Cylinder();
            Cylinder(rtx::Point3D center, double radius, double height, std::shared_ptr<rtx::IMaterial> material);
            bool hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const override;
        private:
            double _radius;
            double _height;
    };
}

#endif /* !CYLINDER_HPP_ */

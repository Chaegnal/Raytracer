/*
** EPITECH PROJECT, 2024
** backup
** File description:
** Plane
*/

#ifndef PLAN_HPP_
    #define PLAN_HPP_

    #include "AShape.hpp"

namespace rtx
{
    class Plane : public virtual rtx::AShape {
        public:
            Plane(const rtx::Point3D &position, const rtx::Vector3D &xVector, const rtx::Vector3D &yVector, std::shared_ptr<rtx::IMaterial> mat);

            bool hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const override;

        private:
            rtx::Point3D _position;
            rtx::Vector3D _xVector;
            rtx::Vector3D _yVector;
            rtx::Vector3D _w;
            rtx::Vector3D normal;
            double D;
    };
};

#endif /* !PLAN_HPP_ */

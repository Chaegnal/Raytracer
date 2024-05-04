/*
** EPITECH PROJECT, 2024
** backup
** File description:
** Plan
*/

#ifndef PLAN_HPP_
    #define PLAN_HPP_

    #include "AShape.hpp"

namespace rtx
{
    class Plan : public virtual rtx::AShape {
        public:
            Plan(rtx::Point3D position, rtx::Vector3D xVector, rtx::Vector3D yVector, std::shared_ptr<rtx::IMaterial> mat);

            bool hits(const rtx::Ray& r, rtx::Interval ray_t, rtx::HitRecord& rec) const override;

        private:
            rtx::Point3D _position;
            rtx::Vector3D _xVector;
            rtx::Vector3D _yVector;
            rtx::Vector3D _w;
            std::shared_ptr<rtx::IMaterial> _material;
            rtx::Vector3D normal;
            double D;
    };
};

#endif /* !PLAN_HPP_ */

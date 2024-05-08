/*
** EPITECH PROJECT, 2024
** AShape.hpp
** File description:
** Abstract implementation for IShape
*/

#ifndef ASHAPE_HPP_
    #define ASHAPE_HPP_

    #include "IShape.hpp"
    #include "ITransformation.hpp"
    #include "Vector3D.hpp"

namespace rtx
{
    class AShape : public virtual rtx::IShape
    {
    public:
        virtual ~AShape() = default;

        rtx::Point3D center;
        std::shared_ptr<rtx::ITransformation> transformation = nullptr;

        virtual bool hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const = 0;
    };
}

#endif

/*
** EPITECH PROJECT, 2024
** HitRecord.hpp
** File description:
** ray hits
*/

#ifndef HITRECORD_HPP_
    #define HITRECORD_HPP_

    #include "Vector3D.hpp"
    #include "Ray.hpp"

namespace rtx
{
    class HitRecord
    {
    public:
        rtx::Point3D point;
        rtx::Vector3D normal;
        double t;
        bool frontFace;

        void setFaceNormal(const rtx::Ray &ray, const rtx::Vector3D &outwardNormal);
    };
}

#endif

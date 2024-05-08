/*
** EPITECH PROJECT, 2024
** Rotation.hpp
** File description:
** rotation of rays
*/

#ifndef ROTATION_HPP_
    #define ROTATION_HPP_

    #include "ATransformation.hpp"

namespace rtx
{
    class Rotation : public virtual rtx::ATransformation
    {
    public:
        Rotation();
        Rotation(const rtx::Vector3D &axis);
        ~Rotation() = default;

        void transform(rtx::Ray &ray) override;
    };
}

#endif

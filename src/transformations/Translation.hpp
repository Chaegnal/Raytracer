/*
** EPITECH PROJECT, 2024
** Translation.hpp
** File description:
** translation of rays
*/

#ifndef TRANSLATION_HPP_
    #define TRANSLATION_HPP_

    #include "ATransformation.hpp"

namespace rtx
{
    class Translation : public virtual rtx::ATransformation
    {
    public:
        Translation();
        Translation(const rtx::Vector3D &axis);
        ~Translation() = default;

        void transform(rtx::Ray &ray) override;
    };
}

#endif

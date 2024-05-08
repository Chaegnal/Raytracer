/*
** EPITECH PROJECT, 2024
** ITransformation.hpp
** File description:
** Interface for transformations
*/

#ifndef ITRANSFORMATION_HPP_
    #define ITRANSFORMATION_HPP_

    #include "Ray.hpp"
    #include "Vector3D.hpp"

namespace rtx
{
    class ITransformation
    {
    public:
        virtual ~ITransformation() = default;

        virtual void transform(rtx::Ray &ray) = 0;
    };
}

#endif

/*
** EPITECH PROJECT, 2024
** backup
** File description:
** ITextures
*/

#ifndef ITEXTURES_HPP_
    #define ITEXTURES_HPP_

    #include "Ray.hpp"
    #include "HitRecord.hpp"
    #include "Interval.hpp"

namespace rtx
{
    class ITextures {
        public:
            virtual ~ITextures() = default;

            virtual rtx::Color textureColor(double u, double v, const rtx::Point3D& p) const = 0;
    };
};

#endif /* !ITEXTURES_HPP_ */

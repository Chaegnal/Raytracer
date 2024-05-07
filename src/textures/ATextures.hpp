/*
** EPITECH PROJECT, 2024
** backup
** File description:
** ATextures
*/

#ifndef ATEXTURES_HPP_
    #define ATEXTURES_HPP_

    #include "ITextures.hpp"

namespace rtx
{
    class ATextures : public virtual rtx::ITextures{
        public:
            virtual rtx::Color textureColor(double u, double v, const rtx::Point3D& p) const = 0;
    };
};

#endif /* !ATEXTURES_HPP_ */

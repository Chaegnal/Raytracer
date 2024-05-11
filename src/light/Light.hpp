/*
** EPITECH PROJECT, 2024
** backup
** File description:
** Light
*/

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

    #include "ATextures.hpp"
    #include "ALight.hpp"
    #include "SolidColor.hpp"

namespace rtx
{
    class Light : public virtual rtx::ALight {
        public:
            Light() {};
            Light(std::shared_ptr<rtx::ITextures> tex);
            Light(const rtx::Color& emit);

            rtx::Color lightEmission(double u, double v, const rtx::Point3D& point) const override;
            rtx::Color ambientLight(double ambient, rtx::Color& actualColor, rtx::Color& defaultColor) const override;

        private:
            std::shared_ptr<rtx::ITextures> _texture;
    };
};

#endif /* !LIGHT_HPP_ */

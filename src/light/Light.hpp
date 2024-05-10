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
            Light(const rtx::Color& emit, rtx::Vector3D lookat, rtx::Point3D pos);

            rtx::Color lightEmition(double u, double v, const rtx::Point3D& point) const override;
            rtx::Color ambientLight(double ambient, rtx::Color& actualColor, rtx::Color& defaultColor) const override {
                if (actualColor.x == 0.00 && actualColor.y == 0.00 && actualColor.z == 0.00) {
                    actualColor.x = defaultColor.x * ambient;
                    actualColor.y = defaultColor.y * ambient;
                    actualColor.z = defaultColor.z * ambient;
                }
                return actualColor;
            }

        private:
            bool isOriented = false;
            rtx::Vector3D _lookat;
            rtx::Point3D _pos;
            std::shared_ptr<rtx::ITextures> _texture;
    };
};

#endif /* !LIGHT_HPP_ */

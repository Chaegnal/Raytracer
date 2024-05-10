/*
** EPITECH PROJECT, 2024
** merge
** File description:
** ALight
*/

#ifndef ALIGHT_HPP_
    #define ALIGHT_HPP_

    #include "ILight.hpp"

namespace rtx
{
    class ALight : public virtual rtx::ILight
    {
    protected:
        rtx::Color _albedo;

    public:
        virtual ~ALight() = default;

        virtual rtx::Color lightEmition(double u, double v, const rtx::Point3D& point) const {
            return rtx::Color(0,0,0);
        }
        virtual rtx::Color ambientLight(double ambient, rtx::Color& actualColor, rtx::Color& defaultColor) const {
            if (actualColor.x == 0.00 && actualColor.y == 0.00 && actualColor.z == 0.00) {
                actualColor.x = defaultColor.x * ambient;
                actualColor.y = defaultColor.y * ambient;
                actualColor.z = defaultColor.z * ambient;
            }
            return actualColor;
        }
    };
}

#endif /* !ALIGHT_HPP_ */

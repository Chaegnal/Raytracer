/*
** EPITECH PROJECT, 2024
** backup
** File description:
** Light
*/

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

    #include "ATextures.hpp"
    #include "AMaterial.hpp"
    #include "SolidColor.hpp"

namespace rtx
{
    class Light : public virtual rtx::AMaterial {
        public:
            Light(std::shared_ptr<rtx::ITextures> tex);
            Light(const rtx::Color& emit);

            rtx::Color lightEmition(double u, double v, const rtx::Point3D& point) const override;

        private:
            std::shared_ptr<rtx::ITextures> _texture;
    };
};

#endif /* !LIGHT_HPP_ */

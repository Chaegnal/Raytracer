/*
** EPITECH PROJECT, 2024
** backup
** File description:
** TextureChecker
*/

#ifndef TEXTURECHECKER_HPP_
#define TEXTURECHECKER_HPP_

    #include "ATextures.hpp"
    #include "SolidColor.hpp"

namespace rtx
{
    class TextureChecker : public rtx::ATextures {
        public:
            TextureChecker(double scale, std::shared_ptr<rtx::ITextures> even, std::shared_ptr<rtx::ITextures> odd);
            TextureChecker(double scale, const rtx::Color& c1, const rtx::Color& c2);

            rtx::Color textureColor(double u, double v, const rtx::Point3D& p) const override;

        private:
            double _scale;
            std::shared_ptr<rtx::ITextures> _even;
            std::shared_ptr<rtx::ITextures> _odd;
    };
};

#endif /* !TEXTURECHECKER_HPP_ */

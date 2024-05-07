/*
** EPITECH PROJECT, 2024
** backup
** File description:
** Light
*/

#include "Light.hpp"

rtx::Light::Light(std::shared_ptr<rtx::ITextures> tex)
{
    _texture = tex;
}

rtx::Light::Light(const rtx::Color& emit)
{
    _texture = std::make_shared<rtx::SolidColor>(emit);
}

rtx::Color rtx::Light::lightEmition(double u, double v, const rtx::Point3D& point) const
{
    return _texture->textureColor(u, v, point);
}
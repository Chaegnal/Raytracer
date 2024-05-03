/*
** EPITECH PROJECT, 2024
** Matte.hpp
** File description:
** matte material
*/

#ifndef MATTE_HPP_
    #define MATTE_HPP_

    #include "AMaterial.hpp"
    #include "Vector3D.hpp"

namespace rtx
{
    class Matte : public virtual rtx::AMaterial
    {
    public:
        Matte(const rtx::Color &albedo);
        ~Matte() = default;

        bool reflect(const rtx::Ray &rayIn, const rtx::HitRecord &rec, rtx::Color &attenuation, rtx::Ray &reflected) const override;
    };
}

#endif

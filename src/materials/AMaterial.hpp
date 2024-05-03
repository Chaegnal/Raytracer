/*
** EPITECH PROJECT, 2024
** AMaterial.hpp
** File description:
** IMaterial abstract declaration
*/

#ifndef AMATERIAL_HPP_
    #define AMATERIAL_HPP_

    #include "IMaterial.hpp"

namespace rtx
{
    class AMaterial : public virtual rtx::IMaterial
    {
    protected:
        rtx::Color _albedo;

    public:
        virtual ~AMaterial() = default;

        virtual bool reflect(const rtx::Ray &rayIn, const rtx::HitRecord &rec, rtx::Color &attenuation, rtx::Ray &reflected) const
            {
                return false;
            }
    };
}

#endif

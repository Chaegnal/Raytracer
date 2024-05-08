/*
** EPITECH PROJECT, 2024
** ATransformation.hpp
** File description:
** ITransformation abstract declaration
*/

#ifndef ATRANSFORMATION_HPP_
    #define ATRANSFORMATION_HPP_

    #include "ITransformation.hpp"

namespace rtx
{
    class ATransformation : public virtual rtx::ITransformation
    {
    protected:
        rtx::Vector3D _axis;

    public:
        virtual ~ATransformation() = default;

        virtual void transform(rtx::Ray &ray) = 0;
    };
}

#endif /* !ATRANSFORMATION_HPP_ */

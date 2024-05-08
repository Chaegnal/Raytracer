/*
** EPITECH PROJECT, 2024
** Translation.cpp
** File description:
** translation of rays
*/

#include "Translation.hpp"
#include "Matrix3D.hpp"

rtx::Translation::Translation()
{
    _axis = rtx::Vector3D();
}

rtx::Translation::Translation(const rtx::Vector3D &axis)
{
    _axis = axis;
}

void rtx::Translation::transform(rtx::Ray &ray)
{
    ray.direction += _axis;
}

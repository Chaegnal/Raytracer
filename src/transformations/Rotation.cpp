/*
** EPITECH PROJECT, 2024
** Rotation.cpp
** File description:
** rotation of rays
*/

#include "Rotation.hpp"
#include "Matrix3D.hpp"

rtx::Rotation::Rotation()
{
    _axis = rtx::Vector3D();
}

rtx::Rotation::Rotation(const rtx::Vector3D &axis)
{
    _axis = axis;
}

void rtx::Rotation::transform(rtx::Ray &ray)
{
    if (_axis.x == 0 && _axis.y == 0 && _axis.z == 0)
        return;
    double theta = _axis.unitVector().length();
    double c = cos(theta);
    double s = sin(theta);
    double t = 1.0 - c;
    double ux = _axis.x;
    double uy = _axis.y;
    double uz = _axis.z;
    rtx::Matrix3D rotationMatrix(
        rtx::Vector3D(c + (ux * ux) * t, uy * ux * t + uz * s, uz * ux * t - uy * s),
        rtx::Vector3D(ux * uz * t - uz * s, c + (uy * uy) * t, uz * uy * t + ux * s),
        rtx::Vector3D(ux * uz * t + uy * s, uy * uz * t - ux * s, c + (uz * uz) * t)
    );

    ray.direction = rotationMatrix * ray.direction;
}

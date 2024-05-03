/*
** EPITECH PROJECT, 2024
** Ray.cpp
** File description:
** ray class
*/

#include "Ray.hpp"
#include "Vector3D.hpp"

rtx::Ray::Ray()
    : origin()
    , direction()
    {}

rtx::Ray::Ray(rtx::Point3D origin, rtx::Vector3D direction)
    : origin(origin)
    , direction(direction)
    {}

rtx::Ray::Ray(const Ray &other)
    : origin(other.origin)
    , direction(other.direction)
    {}

rtx::Point3D rtx::Ray::at(double t) const
{
    return origin + (direction * t);
}

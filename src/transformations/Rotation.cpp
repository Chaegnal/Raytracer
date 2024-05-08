/*
** EPITECH PROJECT, 2024
** Rotation.cpp
** File description:
** rotation of rays
*/

#include "Rotation.hpp"
#include "Matrix3D.hpp"

rtx::Rotation::Rotation(std::shared_ptr<rtx::IShape> shape, const rtx::Vector3D &axis, double angle)
{
    _axis = axis;
    _shape = shape;
    _bBox = shape->getBoundingBox();

    rtx::Point3D min(infinity, infinity, infinity);
    rtx::Point3D max(-infinity, -infinity, -infinity);

    double theta = degToRad(angle);
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    double oneMinT = 1.0 - theta;
    double ux = _axis.x;
    double uy = _axis.y;
    double uz = _axis.z;
    _rotationMatrix = rtx::Matrix3D(
        rtx::Vector3D(cosTheta + (ux * ux) * oneMinT, uy * ux * oneMinT + uz * sinTheta, uz * ux * oneMinT - uy * sinTheta),
        rtx::Vector3D(ux * uz * oneMinT - uz * sinTheta, cosTheta + (uy * uy) * oneMinT, uz * uy * oneMinT + ux * sinTheta),
        rtx::Vector3D(ux * uz * oneMinT + uy * sinTheta, uy * uz * oneMinT - ux * sinTheta, cosTheta + (uz * uz) * oneMinT)
    );
}

rtx::Rotation::Rotation(std::shared_ptr<rtx::IShape> shape, const rtx::Vector3D &axis)
{
    _axis = axis;
    _shape = shape;

    double theta = atan2(_axis.unitVector().y, _axis.unitVector().x);
    if (theta < 0.0)
        theta += 2.0 * M_PI;
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    double oneMinT = 1.0 - theta;
    double ux = _axis.x;
    double uy = _axis.y;
    double uz = _axis.z;
    _rotationMatrix = rtx::Matrix3D(
        rtx::Vector3D(cosTheta + (ux * ux) * oneMinT, uy * ux * oneMinT + uz * sinTheta, uz * ux * oneMinT - uy * sinTheta),
        rtx::Vector3D(ux * uz * oneMinT - uz * sinTheta, cosTheta + (uy * uy) * oneMinT, uz * uy * oneMinT + ux * sinTheta),
        rtx::Vector3D(ux * uz * oneMinT + uy * sinTheta, uy * uz * oneMinT - ux * sinTheta, cosTheta + (uz * uz) * oneMinT)
    );
}

bool rtx::Rotation::hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const
{
    rtx::Ray rotatedRay(_rotationMatrix * ray.origin, _rotationMatrix * ray.direction);

    if (_shape->hits(rotatedRay, rayT, rec) == false)
        return false;

    rec.point = _rotationMatrix * rec.point;
    rec.normal = _rotationMatrix * rec.normal;
    return true;
}

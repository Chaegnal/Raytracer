/*
** EPITECH PROJECT, 2024
** Vector3D.cpp
** File description:
** 3d vector
*/

#include "Vector3D.hpp"
#include <memory>

rtx::Vector3D::Vector3D()
    : x(0.0)
    , y(0.0)
    , z(0.0)
    {}

rtx::Vector3D::Vector3D(double x, double y, double z)
    : x(x)
    , y(y)
    , z(z)
    {}

rtx::Vector3D::Vector3D(const rtx::Vector3D &other)
    : x(other.x)
    , y(other.y)
    , z(other.z)
    {}

rtx::Vector3D rtx::Vector3D::randomVectInSphere()
{
    while (true) {
        rtx::Vector3D point = rtx::Vector3D::random(-1.0, 1.0);

        if (point.lengthSquared() < 1.0)
            return point;
    }
}

rtx::Vector3D rtx::Vector3D::randomVectOnSphere(const rtx::Vector3D &normal)
{
    rtx::Vector3D randomUnitVect = rtx::Vector3D::randomUnitVector();

    if (randomUnitVect.dot(normal) > 0.0)
        return randomUnitVect;
    return randomUnitVect * -1.0;
}

bool rtx::Vector3D::closeToZero() const
{
    double tolerance = 0.00000001;

    return (fabs(x) < tolerance) && (fabs(y) < tolerance) && (fabs(z) < tolerance);
}

rtx::Vector3D rtx::Vector3D::refract(const rtx::Vector3D &other, double etaIOverEtaT)
{
    double cosTheta = fmin((*this * (-1.0)).dot(other), 1.0);
    rtx::Vector3D rayOutPerPoint = ((other * cosTheta) + *this) * etaIOverEtaT;
    rtx::Vector3D rayOutParallel = other * (-sqrt(fabs(rayOutPerPoint.lengthSquared() - 1.0)));

    return rayOutPerPoint + rayOutParallel;
}

rtx::Vector3D rtx::Vector3D::randomInUnitDisk()
{
    while (true) {
        rtx::Vector3D vect = rtx::Vector3D(randomValue(-1.0, 1.0), randomValue(-1.0, 1.0), 0.0);

        if (vect.lengthSquared() < 1.0)
            return vect;
    }
}

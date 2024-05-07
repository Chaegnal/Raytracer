/*
** EPITECH PROJECT, 2024
** Sphere.cpp
** File description:
** sphere class
*/

#include "Sphere.hpp"
#include "Vector3D.hpp"
#include "Interval.hpp"
#include <cmath>
#include <iostream>

rtx::Sphere::Sphere()
    : _radius(0.0)
    , _material(nullptr)
    {
        center = rtx::Point3D();
    }

rtx::Sphere::Sphere(rtx::Point3D _center, double radius, std::shared_ptr<rtx::IMaterial> material)
    : _radius(radius >= 0.0 ? radius : 0.0)
    , _material(material)
    {
        center = _center;
    }

bool rtx::Sphere::hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const
{
    rtx::Vector3D diff = center - ray.origin;
    double a = ray.direction.lengthSquared();
    double b = ray.direction.dot(diff);
    double c = diff.lengthSquared() - (_radius * _radius);
    double d = (b * b) - a * c;

    if (d < 0.0)
        return false;

    double root = (b - sqrt(d)) / a;

    if (!rayT.surrounds(root)) {
        root = (b + sqrt(d)) / a;
        if (!rayT.surrounds(root))
            return false;
    }
    rec.t = root;
    rec.point = ray.at(rec.t);
    rtx::Vector3D outwardNormal = (rec.point - center) / _radius;
    rec.setFaceNormal(ray, outwardNormal);
    sphereHitsAngle(outwardNormal, rec.u, rec.v);
    rec.material = _material;
    return true;
}

void rtx::Sphere::sphereHitsAngle(const rtx::Point3D& p, double& u, double& v)
{
    auto theta = acos(-p.y);
    auto phi = atan2(-p.z, p.x) + M_PI;

    u = phi / (2 * M_PI);
    v = theta / M_PI;
}


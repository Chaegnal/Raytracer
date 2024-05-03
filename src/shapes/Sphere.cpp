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
    : radius(0.0)
    {
        center = rtx::Point3D();
    }

rtx::Sphere::Sphere(rtx::Point3D _center, double _radius)
    : radius(_radius >= 0.0 ? _radius : 0.0)
    {
        center = _center;
    }

bool rtx::Sphere::hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const
{
    rtx::Vector3D diff = center - ray.origin;
    double a = ray.direction.lengthSquared();
    double b = ray.direction.dot(diff);
    double c = diff.lengthSquared() - (radius * radius);
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
    rtx::Vector3D outwardNormal = (rec.point - center) / radius;
    rec.setFaceNormal(ray, outwardNormal);
    return true;
}


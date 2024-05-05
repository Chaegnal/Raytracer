/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-yanis.harkouk
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

rtx::Cylinder::Cylinder() : _radius(1.0), _height(1.0), _material(nullptr)
{
    center = rtx::Point3D();
}

rtx::Cylinder::Cylinder(rtx::Point3D center, double radius, double height, std::shared_ptr<rtx::IMaterial> material) : _radius(radius), _height(height), _material(material)
{
    this->center = center;
}

bool rtx::Cylinder::hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const
{
    rtx::Vector3D diff = ray.origin - center;
    double a = (ray.direction.x * ray.direction.x) + (ray.direction.z * ray.direction.z);
    double b = 2 * ((ray.direction.x * diff.x) + (ray.direction.z * diff.z));
    double c = (diff.x * diff.x) + (diff.z * diff.z) - (_radius * _radius);
    double d = (b * b) - 4 * (a * c);

    if (d < 0.0)
        return false;

    double root = (-b - sqrt(d)) / (2 * a);

    if (!rayT.surrounds(root)) {
        root = (- b + sqrt(d)) / (2 * a);
        if (!rayT.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.point = ray.at(rec.t);

    double len_max = sqrt(pow(_height / 2, 2) + pow(_radius, 2));
    rtx::Vector3D distance = rec.point - center;

    if (distance.length() > len_max) {
        root = (- b + sqrt(d)) / (2 * a);
        rec.t = root;
        rec.point = ray.at(rec.t);
        distance = rec.point - center;
        if (distance.length() > len_max)
            return false;
    }

    rtx::Vector3D outwardNormal = rec.point - center;
    rec.setFaceNormal(ray, outwardNormal);
    rec.material = _material;
    if (rec.point.y >= center.y && rec.point.y <= center.y + _height)
        return true;
    return false;
}

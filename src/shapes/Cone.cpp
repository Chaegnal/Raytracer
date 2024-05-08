/*
** EPITECH PROJECT, 2024
** rtx
** File description:
** Cone
*/

#include "Cone.hpp"

rtx::Cone::Cone() : _radius(1.0), _height(1.0), _material(nullptr)
{
    center = rtx::Point3D();
}

rtx::Cone::Cone(rtx::Point3D center, double radius, double height, std::shared_ptr<rtx::IMaterial> material) : _radius(radius), _height(height), _material(material)
{
    this->center = center;
}

rtx::Cone::Cone(rtx::Point3D center, double radius, double height, std::shared_ptr<rtx::IMaterial> material, std::shared_ptr<ITransformation> transformation) : _radius(radius), _height(height), _material(material)
{
    this->center = center;
    this->transformation = transformation;
}

bool rtx::Cone::hits(const rtx::Ray &ray, rtx::Interval rayT, rtx::HitRecord &rec) const
{
    rtx::Ray tmpRay(ray);
    if (transformation != nullptr)
        transformation->transform(tmpRay);
    rtx::Vector3D diff = tmpRay.origin - center;
    double k = _radius / _height;
    double a = std::pow(tmpRay.direction.x, 2) + std::pow(tmpRay.direction.z, 2) - (std::pow(k, 2) * std::pow(tmpRay.direction.y, 2));
    double b = 2 * ((tmpRay.direction.x * diff.x) + (tmpRay.direction.z * diff.z) - (std::pow(k, 2) * tmpRay.direction.y * (tmpRay.origin.y - center.y)));
    double c = std::pow(diff.x, 2) + std::pow(diff.z, 2) - (std::pow(k, 2) * std::pow(diff.y, 2));
    double d = (b * b) - 4 * (a * c);

    if (d < 0.0)
        return false;

    double root = (-b - std::sqrt(d)) / (2 * a);

    if (!rayT.surrounds(root)) {
        root = (- b + std::sqrt(d)) / (2 * a);
        if (!rayT.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.point = tmpRay.at(rec.t);

    double len_max = std::sqrt(std::pow(_height / 2, 2) + std::pow(_radius, 2));
    rtx::Vector3D distance = rec.point - center;

    if (distance.length() > len_max) {
        root = (- b + std::sqrt(d)) / (2 * a);
        rec.t = root;
        rec.point = tmpRay.at(rec.t);
        distance = rec.point - center;
        if (distance.length() > len_max)
            return false;
    }

    rtx::Vector3D outwardNormal = rec.point - center;
    rec.setFaceNormal(tmpRay, outwardNormal);
    rec.material = _material;
    if (rec.point.y >= center.y && rec.point.y <= center.y + _height)
        return true;
    return false;
}

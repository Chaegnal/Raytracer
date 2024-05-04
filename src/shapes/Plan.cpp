/*
** EPITECH PROJECT, 2024
** backup
** File description:
** Plan
*/

#include "Plan.hpp"

rtx::Plan::Plan(rtx::Point3D position, rtx::Vector3D xVector, rtx::Vector3D yVector, std::shared_ptr<rtx::IMaterial> mat) : _position(position), _xVector(xVector), _yVector(yVector), _material(mat)
{
    auto n = _xVector.cross(_yVector);
    normal = n.unitVector();
    D = normal.dot(_position);
    _w = n / n.dot(n);
}

bool rtx::Plan::hits(const rtx::Ray& r, rtx::Interval ray_t, rtx::HitRecord& rec) const
{
    double denom = normal.dot(r.direction);

    if (fabs(denom) < 1e-8)
        return false;

    double t = (D - normal.dot(r.origin)) / denom;
    if (!ray_t.contains(t))
        return false;

    rtx::Point3D hitPoint = r.at(t);
    rtx::Vector3D planIntersectionVect = hitPoint - _position;
    rtx::Vector3D newU = _xVector;
    double alpha = _w.dot(planIntersectionVect.cross(_yVector));
    double beta =  _w.dot(newU.cross(planIntersectionVect));

    rtx::Interval unitInterval = rtx::Interval(0, 1);
    if (!unitInterval.contains(alpha) || !unitInterval.contains(beta))
        return false;

    rec.u = alpha;
    rec.v = beta;
    rec.t = t;
    rec.point = hitPoint;
    rec.material = _material;
    rec.setFaceNormal(r, normal);

    return true;
}

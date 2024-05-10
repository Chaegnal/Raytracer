/*
** EPITECH PROJECT, 2024
** rtx
** File description:
** Factory
*/

#include "Factory.hpp"
#include "Parsing.hpp"
#include "Vector3D.hpp"
#include "macros.hpp"
#include "SphereBuilder.hpp"
#include "ConeBuilder.hpp"
#include "CylinderBuilder.hpp"
#include "PlaneBuilder.hpp"
#include "TriangleBuilder.hpp"
#include <vector>
#include <libconfig.h++>
#include "Rotation.hpp"
#include "Translation.hpp"

rtx::Factory::Factory(libconfig::Config &conf) : _conf(conf)
{
}

void rtx::Factory::createWorldFromConfFile(rtx::Scene &world)
{
    createPlaneFromConfFile(world);
    createConeFromConfFile(world);
    createCylinderFromConfFile(world);
    createSphereFromConfFile(world);
    createTriangleFromConfFile(world);
    createLightFromConfFile(world);
}

std::shared_ptr<rtx::IShape> rtx::Factory::applyTransformation(rtx::Parsing::TransfoInfo &transfoInfo, std::shared_ptr<rtx::IShape> &shape) const
{
    if (transfoInfo.transformation == "translation")
        return rtx::Factory::createTransformation<rtx::Translation>(shape, rtx::Vector3D(transfoInfo.x, transfoInfo.y, transfoInfo.z));
    if (transfoInfo.transformation == "rotation")
        return rtx::Factory::createTransformation<rtx::Rotation>(shape, rtx::Vector3D(transfoInfo.x, transfoInfo.y, transfoInfo.z), transfoInfo.angle);
    return shape;
}

void rtx::Factory::createSphereFromConfFile(rtx::Scene &world)
{
    rtx::SphereBuilder builder;
    std::vector<rtx::Parsing::SphereInfo> spheres = rtx::Parsing::parseSphere(_conf);

    for (auto &sphere : spheres) {
        builder.setPosition(rtx::Point3D(sphere.x, sphere.y, sphere.z));
        builder.setRadius(sphere.radius);
        if (sphere.material.material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(sphere.material.extra));
        if (sphere.material.material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(sphere.material.r, sphere.material.g, sphere.material.b)));
        if (sphere.material.material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(sphere.material.r, sphere.material.g, sphere.material.b), sphere.material.extra));
        world.add(builder.getProduct());
    }
}

void rtx::Factory::createCylinderFromConfFile(rtx::Scene &world)
{
    rtx::CylinderBuilder builder;
    std::vector<rtx::Parsing::CylinderConeInfo> cylinders = rtx::Parsing::parseCylinder(_conf);

        for (int i = 0; i != cylinders.size(); i++) {
            builder.setPosition(rtx::Point3D(cylinders[i].x, cylinders[i].y, cylinders[i].z));
            builder.setRadius(cylinders[i].radius);
            builder.setHeight(cylinders[i].height);
            builder.setIsCapped(cylinders[i].isCapped);
            if (cylinders[i].material.material == "Dielectric")
                builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(cylinders[i].material.extra));
            if (cylinders[i].material.material == "Matte")
                builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(cylinders[i].material.r, cylinders[i].material.g, cylinders[i].material.b)));
            if (cylinders[i].material.material == "Metal")
                builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(cylinders[i].material.r, cylinders[i].material.g, cylinders[i].material.b), cylinders[i].material.extra));
            world.add(builder.getProduct());
    }
}

void rtx::Factory::createConeFromConfFile(rtx::Scene &world)
{
    rtx::ConeBuilder builder;
    std::vector<rtx::Parsing::CylinderConeInfo> cones = rtx::Parsing::parseCone(_conf);

        for (auto &cone : cones) {
            builder.setPosition(rtx::Point3D(cone.x, cone.y, cone.z));
            builder.setRadius(cone.radius);
            builder.setHeight(cone.height);
            if (cone.material.material == "Dielectric")
                builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(cone.material.extra));
            if (cone.material.material == "Matte")
                builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(cone.material.r, cone.material.g, cone.material.b)));
            if (cone.material.material == "Metal")
                builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(cone.material.r, cone.material.g, cone.material.b), cone.material.extra));
            world.add(builder.getProduct());
    }
}

void rtx::Factory::createPlaneFromConfFile(rtx::Scene &world)
{
    rtx::PlaneBuilder builder;
    std::vector<rtx::Parsing::PlaneTriangleInfo> planes = rtx::Parsing::parsePlane(_conf);

    for (auto &plane : planes) {
        builder.setPosition(rtx::Point3D(plane.x, plane.y, plane.z));
        builder.setWidth(rtx::Vector3D(plane.size_x, plane.size_y, plane.size_z));
        builder.setHeight(rtx::Vector3D(plane.height_x, plane.height_y, plane.height_z));
        if (plane.material.material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(plane.material.extra));
        if (plane.material.material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(plane.material.r, plane.material.g, plane.material.b)));
        if (plane.material.material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(plane.material.r, plane.material.g, plane.material.b), plane.material.extra));
        world.add(builder.getProduct());
    }
}

void rtx::Factory::createTriangleFromConfFile(rtx::Scene &world)
{
    rtx::TriangleBuilder builder;
    std::vector<rtx::Parsing::PlaneTriangleInfo> triangles = rtx::Parsing::parseTriangles(_conf);

    for (auto &triangle : triangles) {
        builder.setPoint0(rtx::Point3D(triangle.x, triangle.y, triangle.z));
        builder.setPoint1(rtx::Point3D(triangle.size_x, triangle.size_y, triangle.size_z));
        builder.setPoint2(rtx::Point3D(triangle.height_x, triangle.height_y, triangle.height_z));
        builder.setPosition(rtx::Point3D());
        if (triangle.material.material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(triangle.material.extra));
        if (triangle.material.material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(triangle.material.r, triangle.material.g, triangle.material.b)));
        if (triangle.material.material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(triangle.material.r, triangle.material.g, triangle.material.b), triangle.material.extra));
        world.add(builder.getProduct());
    }
}

void rtx::Factory::createLightFromConfFile(rtx::Scene &world)
{
    std::vector<rtx::Parsing::LightInfo> lightPoints = rtx::Parsing::parsePointLight(_conf);

    for (auto &lightPoint : lightPoints) {
        auto light = std::make_shared<rtx::Light>(rtx::Color(lightPoint.r, lightPoint.g, lightPoint.b), rtx::Point3D(lightPoint.x, lightPoint.y, lightPoint.z), rtx::Vector3D(0.0, 0.0, 0.0));
        world.add(createShape<rtx::Sphere>(rtx::Point3D(lightPoint.x, lightPoint.y, lightPoint.z), lightPoint.size, light));
    }
}

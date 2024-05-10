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

void rtx::Factory::createSphereFromConfFile(rtx::Scene &world)
{
    rtx::SphereBuilder builder;
    std::vector<rtx::Parsing::SphereInfo> spheres = rtx::Parsing::parseSphere(_conf);

    for (int i = 0; i != spheres.size(); i++) {
        builder.setPosition(rtx::Point3D(spheres[i].x, spheres[i].y, spheres[i].z));
        builder.setRadius(spheres[i].radius);
        if (spheres[i].material.material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(spheres[i].material.extra));
        if (spheres[i].material.material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(spheres[i].material.r, spheres[i].material.g, spheres[i].material.b)));
        if (spheres[i].material.material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(spheres[i].material.r, spheres[i].material.g, spheres[i].material.b), spheres[i].material.extra));
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

        for (int i = 0; i != cones.size(); i++) {
            builder.setPosition(rtx::Point3D(cones[i].x, cones[i].y, cones[i].z));
            builder.setRadius(cones[i].radius);
            builder.setHeight(cones[i].height);
            if (cones[i].material.material == "Dielectric")
                builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(cones[i].material.extra));
            if (cones[i].material.material == "Matte")
                builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(cones[i].material.r, cones[i].material.g, cones[i].material.b)));
            if (cones[i].material.material == "Metal")
                builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(cones[i].material.r, cones[i].material.g, cones[i].material.b), cones[i].material.extra));
            world.add(builder.getProduct());
    }
}

void rtx::Factory::createPlaneFromConfFile(rtx::Scene &world)
{
    rtx::PlaneBuilder builder;
    std::vector<rtx::Parsing::PlaneTriangleInfo> planes = rtx::Parsing::parsePlane(_conf);

    for (int i = 0; i != planes.size(); i++) {
        builder.setPosition(rtx::Point3D(planes[i].x, planes[i].y, planes[i].z));
        builder.setWidth(rtx::Vector3D(planes[i].size_x, planes[i].size_y, planes[i].size_z));
        builder.setHeight(rtx::Vector3D(planes[i].height_x, planes[i].height_y, planes[i].height_z));
        if (planes[i].material.material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(planes[i].material.extra));
        if (planes[i].material.material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(planes[i].material.r, planes[i].material.g, planes[i].material.b)));
        if (planes[i].material.material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(planes[i].material.r, planes[i].material.g, planes[i].material.b), planes[i].material.extra));
        world.add(builder.getProduct());
    }
}

void rtx::Factory::createTriangleFromConfFile(rtx::Scene &world)
{
    rtx::TriangleBuilder builder;
    std::vector<rtx::Parsing::PlaneTriangleInfo> triangles = rtx::Parsing::parseTriangles(_conf);

    for (int i = 0; i != triangles.size(); i++) {
        builder.setPoint0(rtx::Point3D(triangles[i].x, triangles[i].y, triangles[i].z));
        builder.setPoint1(rtx::Point3D(triangles[i].size_x, triangles[i].size_y, triangles[i].size_z));
        builder.setPoint2(rtx::Point3D(triangles[i].height_x, triangles[i].height_y, triangles[i].height_z));
        builder.setPosition(rtx::Point3D());
        if (triangles[i].material.material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(triangles[i].material.extra));
        if (triangles[i].material.material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(triangles[i].material.r, triangles[i].material.g, triangles[i].material.b)));
        if (triangles[i].material.material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(triangles[i].material.r, triangles[i].material.g, triangles[i].material.b), triangles[i].material.extra));
        world.add(builder.getProduct());
    }
}

void rtx::Factory::createLightFromConfFile(rtx::Scene &world)
{
    std::vector<rtx::Parsing::LightInfo> lightPoint = rtx::Parsing::parsePointLight(_conf);

    for (int i = 0; i != lightPoint.size(); i++) {
        auto light = std::make_shared<rtx::Light>(rtx::Color(lightPoint[i].r, lightPoint[i].g, lightPoint[i].b), rtx::Point3D(lightPoint[i].x, lightPoint[i].y, lightPoint[i].z), rtx::Vector3D(0.0, 0.0, 0.0));
        world.add(createShape<rtx::Sphere>(rtx::Point3D(lightPoint[i].x, lightPoint[i].y, lightPoint[i].z), lightPoint[i].size, light));
    }
}

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
}

void rtx::Factory::createSphereFromConfFile(rtx::Scene &world)
{
    rtx::SphereBuilder builder;
    std::vector<rtx::Parsing::SphereInfo> spheres = rtx::Parsing::parseSphere(_conf);

    for (int i = 0; i != spheres.size(); i++) {
        builder.setPosition(rtx::Point3D(spheres[i].x, spheres[i].y, spheres[i].z));
        builder.setRadius(spheres[i].radius);
        if (spheres[i].material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(spheres[i].extra));
        if (spheres[i].material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(spheres[i].r, spheres[i].g, spheres[i].b)));
        if (spheres[i].material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(spheres[i].r, spheres[i].g, spheres[i].b), spheres[i].extra));
        if (spheres[i].material == "Light")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Light>(rtx::Color(spheres[i].r, spheres[i].g, spheres[i].b)));
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
        if (cylinders[i].material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(cylinders[i].extra));
        if (cylinders[i].material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(cylinders[i].r, cylinders[i].g, cylinders[i].b)));
        if (cylinders[i].material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(cylinders[i].r, cylinders[i].g, cylinders[i].b), cylinders[i].extra));
        if (cylinders[i].material == "Light")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Light>(rtx::Color(cylinders[i].r, cylinders[i].g, cylinders[i].b)));
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
        if (cones[i].material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(cones[i].extra));
        if (cones[i].material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(cones[i].r, cones[i].g, cones[i].b)));
        if (cones[i].material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(cones[i].r, cones[i].g, cones[i].b), cones[i].extra));
        if (cones[i].material == "Light")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Light>(rtx::Color(cones[i].r, cones[i].g, cones[i].b)));
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
        if (planes[i].material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(planes[i].extra));
        if (planes[i].material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(planes[i].r, planes[i].g, planes[i].b)));
        if (planes[i].material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(planes[i].r, planes[i].g, planes[i].b), planes[i].extra));
        if (planes[i].material == "Light")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Light>(rtx::Color(planes[i].r, planes[i].g, planes[i].b)));
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
        if (triangles[i].material == "Dielectric")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Dielectric>(triangles[i].extra));
        if (triangles[i].material == "Matte")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Matte>(rtx::Color(triangles[i].r, triangles[i].g, triangles[i].b)));
        if (triangles[i].material == "Metal")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Metal>(rtx::Color(triangles[i].r, triangles[i].g, triangles[i].b), triangles[i].extra));
        if (triangles[i].material == "Light")
            builder.setMaterial(rtx::Factory::createMaterial<rtx::Light>(rtx::Color(triangles[i].r, triangles[i].g, triangles[i].b)));
        world.add(builder.getProduct());
    }
}

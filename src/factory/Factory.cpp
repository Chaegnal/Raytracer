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
#include <vector>
#include <libconfig.h++>

rtx::Factory::Factory(libconfig::Config &conf) : _conf(conf)
{
}

void rtx::Factory::createWorldFromConfFile(rtx::Scene &world)
{
    createSphereFromConfFile(world);
    createConeFromConfFile(world);
    createCylinderFromConfFile(world);
    createPlaneFromConfFile(world);
}

void rtx::Factory::createSphereFromConfFile(rtx::Scene &world)
{
    Parsing parser;
    std::vector<Parsing::SphereInfo> spheres = parser.parseSphere(_conf);

    for (int i = 0; i != spheres.size(); i++) {
        auto material1 = std::make_shared<rtx::Dielectric>(spheres[i].extra);
        auto material2 = std::make_shared<rtx::Matte>(rtx::Color(spheres[i].r, spheres[i].g, spheres[i].b));
        auto material3 = std::make_shared<rtx::Metal>(rtx::Color(spheres[i].r, spheres[i].g, spheres[i].b), spheres[i].extra);
        if (spheres[i].material == "Dielectric")
            world.add(createShape<rtx::Sphere>(rtx::Point3D(spheres[i].x, spheres[i].y, spheres[i].z), spheres[i].radius, material1));
        if (spheres[i].material == "Matte")
            world.add(createShape<rtx::Sphere>(rtx::Point3D(spheres[i].x, spheres[i].y, spheres[i].z), spheres[i].radius, material2));
        if (spheres[i].material == "Metal")
            world.add(createShape<rtx::Sphere>(rtx::Point3D(spheres[i].x, spheres[i].y, spheres[i].z), spheres[i].radius, material3));
    }
}

void rtx::Factory::createCylinderFromConfFile(rtx::Scene &world)
{
    Parsing parser;
    std::vector<Parsing::CylinderConeInfo> cylinder = parser.parseCylinder(_conf);

        for (int i = 0; i != cylinder.size(); i++) {
        auto material1 = std::make_shared<rtx::Dielectric>(cylinder[i].extra);
        auto material2 = std::make_shared<rtx::Matte>(rtx::Color(cylinder[i].r, cylinder[i].g, cylinder[i].b));
        auto material3 = std::make_shared<rtx::Metal>(rtx::Color(cylinder[i].r, cylinder[i].g, cylinder[i].b), cylinder[i].extra);
        if (cylinder[i].material == "Dielectric")
            world.add(createShape<rtx::Cylinder>(rtx::Point3D(cylinder[i].x, cylinder[i].y, cylinder[i].z), cylinder[i].radius, cylinder[i].height, material1));
        if (cylinder[i].material == "Matte")
            world.add(createShape<rtx::Cylinder>(rtx::Point3D(cylinder[i].x, cylinder[i].y, cylinder[i].z), cylinder[i].radius, cylinder[i].height, material2));
        if (cylinder[i].material == "Metal")
            world.add(createShape<rtx::Cylinder>(rtx::Point3D(cylinder[i].x, cylinder[i].y, cylinder[i].z), cylinder[i].radius, cylinder[i].height, material3));
    }
}

void rtx::Factory::createConeFromConfFile(rtx::Scene &world)
{
    Parsing parser;
    std::vector<Parsing::CylinderConeInfo> cone = parser.parseCone(_conf);

        for (int i = 0; i != cone.size(); i++) {
        auto material1 = std::make_shared<rtx::Dielectric>(cone[i].extra);
        auto material2 = std::make_shared<rtx::Matte>(rtx::Color(cone[i].r, cone[i].g, cone[i].b));
        auto material3 = std::make_shared<rtx::Metal>(rtx::Color(cone[i].r, cone[i].g, cone[i].b), cone[i].extra);
        if (cone[i].material == "Dielectric")
            world.add(createShape<rtx::Cone>(rtx::Point3D(cone[i].x, cone[i].y, cone[i].z), cone[i].radius, cone[i].height, material1));
        if (cone[i].material == "Matte")
            world.add(createShape<rtx::Cone>(rtx::Point3D(cone[i].x, cone[i].y, cone[i].z), cone[i].radius, cone[i].height, material2));
        if (cone[i].material == "Metal")
            world.add(createShape<rtx::Cone>(rtx::Point3D(cone[i].x, cone[i].y, cone[i].z), cone[i].radius, cone[i].height, material3));
    }
}

void rtx::Factory::createPlaneFromConfFile(rtx::Scene &world)
{
    Parsing parser;
    std::vector<Parsing::PlaneInfo> plane = parser.parsePlane(_conf);

    for (int i = 0; i != plane.size(); i++) {
        auto material1 = std::make_shared<rtx::Dielectric>(plane[i].extra);
        auto material2 = std::make_shared<rtx::Matte>(rtx::Color(plane[i].r, plane[i].g, plane[i].b));
        auto material3 = std::make_shared<rtx::Metal>(rtx::Color(plane[i].r, plane[i].g, plane[i].b), plane[i].extra);
        if (plane[i].material == "Dielectric")
            world.add(createShape<rtx::Plane>(rtx::Point3D(plane[i].x, plane[i].y, plane[i].z), rtx::Vector3D(plane[i].size_x, plane[i].size_y, plane[i].size_z), rtx::Vector3D(plane[i].height_x, plane[i].height_y, plane[i].height_z),material1));
        if (plane[i].material == "Matte")
            world.add(createShape<rtx::Plane>(rtx::Point3D(plane[i].x, plane[i].y, plane[i].z), rtx::Vector3D(plane[i].size_x, plane[i].size_y, plane[i].size_z), rtx::Vector3D(plane[i].height_x, plane[i].height_y, plane[i].height_z),material2));
        if (plane[i].material == "Metal")
            world.add(createShape<rtx::Plane>(rtx::Point3D(plane[i].x, plane[i].y, plane[i].z), rtx::Vector3D(plane[i].size_x, plane[i].size_y, plane[i].size_z), rtx::Vector3D(plane[i].height_x, plane[i].height_y, plane[i].height_z),material3));
    }
}

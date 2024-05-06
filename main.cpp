/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main
*/

#include <memory>
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include "Camera.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "memes.hpp"
#include "macros.hpp"
#include "Metal.hpp"
#include "Matte.hpp"
#include "Dielectric.hpp"
#include "Factory.hpp"
#include "Plan.hpp"
#include "Parsing.hpp"

static void displayUsage()
{
    static const std::string memes[NB_MEMES] = {SHRUG_MEME, FORGOT_BRAIN_MEME, SPONGEBOB_MEME, DOOT_DOOT_MEME, RICK_ROLL_MEME, DERP_MEME, NERD_MEME, RTX_ON_MEME};
    std::size_t randValue = randomValue(0, NB_MEMES);

    std::cout << memes[randValue];
    std::cout << "\033[1mUSAGE\033[m:\t./raytracer [-g]\n"
              << "\t\033[1m-g\033[m\tdisplays in real time the pixels drawing (slows the process)\n";
}

static rtx::Scene getSphere(libconfig::Config &conf, rtx::Scene world)
{
    Parsing parser;
    rtx::Factory factory;
    std::vector<Parsing::SphereInfo> spheres = parser.parseSphere(conf);

    for (int i = 0; i != spheres.size(); i++) {
        auto material1 = std::make_shared<rtx::Dielectric>(spheres[i].extra);
        auto material2 = std::make_shared<rtx::Matte>(rtx::Color(spheres[i].r, spheres[i].g, spheres[i].b));
        auto material3 = std::make_shared<rtx::Metal>(rtx::Color(spheres[i].r, spheres[i].g, spheres[i].b), spheres[i].extra);
        if (spheres[i].material == "Dielectric")
            world.add(factory.createShape<rtx::Sphere>(rtx::Point3D(spheres[i].x, spheres[i].y, spheres[i].z), spheres[i].radius, material1));
        if (spheres[i].material == "Matte")
            world.add(factory.createShape<rtx::Sphere>(rtx::Point3D(spheres[i].x, spheres[i].y, spheres[i].z), spheres[i].radius, material2));
        if (spheres[i].material == "Metal")
            world.add(factory.createShape<rtx::Sphere>(rtx::Point3D(spheres[i].x, spheres[i].y, spheres[i].z), spheres[i].radius, material3));
    }
    return world;
}

static rtx::Scene getCylinder(libconfig::Config &conf, rtx::Scene world)
{
    Parsing parser;
    rtx::Factory factory;
    std::vector<Parsing::CylinderConeInfo> cylinder = parser.parseCylinder(conf);

        for (int i = 0; i != cylinder.size(); i++) {
        auto material1 = std::make_shared<rtx::Dielectric>(cylinder[i].extra);
        auto material2 = std::make_shared<rtx::Matte>(rtx::Color(cylinder[i].r, cylinder[i].g, cylinder[i].b));
        auto material3 = std::make_shared<rtx::Metal>(rtx::Color(cylinder[i].r, cylinder[i].g, cylinder[i].b), cylinder[i].extra);
        if (cylinder[i].material == "Dielectric")
            world.add(factory.createShape<rtx::Cylinder>(rtx::Point3D(cylinder[i].x, cylinder[i].y, cylinder[i].z), cylinder[i].radius, cylinder[i].height, material1));
        if (cylinder[i].material == "Matte")
            world.add(factory.createShape<rtx::Cylinder>(rtx::Point3D(cylinder[i].x, cylinder[i].y, cylinder[i].z), cylinder[i].radius, cylinder[i].height, material2));
        if (cylinder[i].material == "Metal")
            world.add(factory.createShape<rtx::Cylinder>(rtx::Point3D(cylinder[i].x, cylinder[i].y, cylinder[i].z), cylinder[i].radius, cylinder[i].height, material3));
    }
    return world;
}

static rtx::Scene getCones(libconfig::Config &conf, rtx::Scene world)
{
    Parsing parser;
    rtx::Factory factory;
    std::vector<Parsing::CylinderConeInfo> cone = parser.parseCone(conf);

        for (int i = 0; i != cone.size(); i++) {
        auto material1 = std::make_shared<rtx::Dielectric>(cone[i].extra);
        auto material2 = std::make_shared<rtx::Matte>(rtx::Color(cone[i].r, cone[i].g, cone[i].b));
        auto material3 = std::make_shared<rtx::Metal>(rtx::Color(cone[i].r, cone[i].g, cone[i].b), cone[i].extra);
        if (cone[i].material == "Dielectric")
            world.add(factory.createShape<rtx::Cone>(rtx::Point3D(cone[i].x, cone[i].y, cone[i].z), cone[i].radius, cone[i].height, material1));
        if (cone[i].material == "Matte")
            world.add(factory.createShape<rtx::Cone>(rtx::Point3D(cone[i].x, cone[i].y, cone[i].z), cone[i].radius, cone[i].height, material2));
        if (cone[i].material == "Metal")
            world.add(factory.createShape<rtx::Cone>(rtx::Point3D(cone[i].x, cone[i].y, cone[i].z), cone[i].radius, cone[i].height, material3));
    }
    return world;
}

static rtx::Scene getPlane(libconfig::Config &conf, rtx::Scene world)
{
    Parsing parser;
    rtx::Factory factory;
    std::vector<Parsing::PlaneInfo> plane = parser.parsePlane(conf);

    for (int i = 0; i != plane.size(); i++) {
        auto material1 = std::make_shared<rtx::Dielectric>(plane[i].extra);
        auto material2 = std::make_shared<rtx::Matte>(rtx::Color(plane[i].r, plane[i].g, plane[i].b));
        auto material3 = std::make_shared<rtx::Metal>(rtx::Color(plane[i].r, plane[i].g, plane[i].b), plane[i].extra);
        if (plane[i].material == "Dielectric")
            world.add(factory.createShape<rtx::Plan>(rtx::Point3D(plane[i].x, plane[i].y, plane[i].z), rtx::Vector3D(plane[i].size_x, plane[i].size_y, plane[i].size_z), rtx::Vector3D(plane[i].height_x, plane[i].height_y, plane[i].height_z),material1));
        if (plane[i].material == "Matte")
            world.add(factory.createShape<rtx::Plan>(rtx::Point3D(plane[i].x, plane[i].y, plane[i].z), rtx::Vector3D(plane[i].size_x, plane[i].size_y, plane[i].size_z), rtx::Vector3D(plane[i].height_x, plane[i].height_y, plane[i].height_z),material2));
        if (plane[i].material == "Metal")
            world.add(factory.createShape<rtx::Plan>(rtx::Point3D(plane[i].x, plane[i].y, plane[i].z), rtx::Vector3D(plane[i].size_x, plane[i].size_y, plane[i].size_z), rtx::Vector3D(plane[i].height_x, plane[i].height_y, plane[i].height_z),material3));
    }
    return world;
}

static rtx::Scene getScene(libconfig::Config &conf)
{
    rtx::Scene world;
    rtx::Factory factory;
    Parsing parser;

    world = getSphere(conf, world);
    world = getCylinder(conf, world);
    world = getCones(conf, world);
    world = getPlane(conf, world);

    return world;
}

static rtx::Camera getCam(libconfig::Config &conf)
{
    Parsing parser;
    rtx::Camera cam(200, 200);
    std::tuple<int, int, int> pos = parser.parseCamPosition(conf);
    std::tuple<int, int, int> lookAt = parser.parseCamLookAt(conf);
    std::tuple<int, int, int> angle = parser.parseCamAngle(conf);

    cam.samplesPerPixel = parser.parseCamSample(conf);
    cam.maxDepth = parser.parseCamDepth(conf);
    cam._fov = parser.parseCamFOV(conf);
    cam._cameraPosition = rtx::Point3D(std::get<0>(pos),std::get<1>(pos),std::get<2>(pos));
    cam._lookAt = rtx::Point3D(std::get<0>(lookAt),std::get<1>(lookAt),std::get<2>(lookAt));
    cam._cameraAngle = rtx::Vector3D(std::get<0>(angle),std::get<1>(angle),std::get<2>(angle));
    cam._defocusAngle = parser.parseCamDefocus(conf);
    cam._focusDist = parser.parseCamFocus(conf);
    return cam;
}

int main(int ac, const char *av[])
{
    srand(time(NULL));

    libconfig::Config conf;

    try {
        conf.readFile(av[ac - 1]);
    } catch (const libconfig::FileIOException &) {
        std::cerr << "Could not open the file" << std::endl;
        return 84;
    }
    catch(const libconfig::ParseException &err) {
        std::cerr << "Parse error at " << err.getFile() << ":" << err.getLine()
            << " - " << err.getError() << std::endl;
        return 84;
    }

    rtx::Scene scene = getScene(conf);
    rtx::Camera cam = getCam(conf);
    Parsing parser;

    if (ac == 2 && std::string(av[1]) == "--help") {
        displayUsage();
        return 0;
    }
    if (ac == 3 && std::string(av[1]) == "-g")
        return cam.renderGraphical(scene, av[2]);
    else if (ac == 2)
        return cam.render(scene, av[1]);
    else {
        displayUsage();
        return 84;
    }
    return 0;
}

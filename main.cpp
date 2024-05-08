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
#include "Plane.hpp"
#include "Parsing.hpp"
#include "Triangle.hpp"

static void displayUsage()
{
    static const std::string memes[NB_MEMES] = {SHRUG_MEME, FORGOT_BRAIN_MEME, SPONGEBOB_MEME, DOOT_DOOT_MEME, RICK_ROLL_MEME, DERP_MEME, NERD_MEME, RTX_ON_MEME};
    std::size_t randValue = randomValue(0, NB_MEMES);

    std::cout << memes[randValue];
    std::cout << "\033[1mUSAGE\033[m:\t./raytracer [-g]\n"
              << "\t\033[1m-g\033[m\tdisplays in real time the pixels drawing (slows the process)\n";
}

static rtx::Scene getScene(libconfig::Config &conf)
{
    rtx::Scene world;
    rtx::Scene tmp;
    rtx::Factory factory(conf);

    tmp.add(factory.createShape<rtx::Cone>(rtx::Point3D(-10, 0.0, 1), 2.0, 2.0, factory.createMaterial<rtx::Matte>(rtx::Color(1, 0, 0))));
    factory.createWorldFromConfFile(world);
    world.add(tmp);
    return world;
}

static rtx::Camera getCam(libconfig::Config &conf)
{
    Parsing parser;
    rtx::Camera cam(1920/7, 1080/7);
    //cam.backgroundColor = rtx::Color(0.70, 0.80, 1.00);
    cam.backgroundColor = rtx::Color(0.01, 0.01, 0.01);
    std::tuple<double, double, double> pos = parser.parseCamPosition(conf);
    std::tuple<double, double, double> lookAt = parser.parseCamLookAt(conf);
    std::tuple<double, double, double> angle = parser.parseCamAngle(conf);

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

    if (ac == 2 && std::string(av[1]) == "--help") {
        displayUsage();
        return 0;
    } else if (ac != 2 && !(ac == 3 && std::string(av[1]) == "-g")) {
        displayUsage();
        return 84;
    }

    libconfig::Config conf;

    try {
        conf.readFile(av[ac - 1]);
    } catch (const libconfig::FileIOException &) {
        std::cerr << "Could not open the file" << std::endl;
        return 84;
    } catch(const libconfig::ParseException &err) {
        std::cerr << "Parse error at " << err.getFile() << ":" << err.getLine()
            << " - " << err.getError() << std::endl;
        return 84;
    }

    rtx::Scene scene = getScene(conf);
    rtx::Camera cam = getCam(conf);

    if (ac == 3 && std::string(av[1]) == "-g")
        return cam.renderGraphical(scene, av[2]);
    return cam.render(scene, av[1]);
}

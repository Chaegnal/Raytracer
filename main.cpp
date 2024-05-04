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
#include "Plan.hpp"
#include "memes.hpp"
#include "macros.hpp"
#include "Metal.hpp"
#include "Matte.hpp"
#include "Dielectric.hpp"
#include "Factory.hpp"

static void displayUsage()
{
    static const std::string memes[NB_MEMES] = {SHRUG_MEME, FORGOT_BRAIN_MEME, SPONGEBOB_MEME, DOOT_DOOT_MEME, RICK_ROLL_MEME, DERP_MEME, NERD_MEME, RTX_ON_MEME};
    std::size_t randValue = randomValue(0, NB_MEMES);

    std::cout << memes[randValue];
    std::cout << "\033[1mUSAGE\033[m:\t./raytracer [-g]\n"
              << "\t\033[1m-g\033[m\tdisplays in real time the pixels drawing (slows the process)\n";
}

static rtx::Scene getScene()
{
    rtx::Scene world;
    rtx::Factory factory;

    auto ground_material = std::make_shared<rtx::Matte>(rtx::Color(0.5, 0.5, 0.5));
    world.add(factory.createShape<rtx::Sphere>(rtx::Point3D(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomValue();
            rtx::Point3D center(a + 0.9*randomValue(), 0.2, b + 0.9*randomValue());

            if ((center - rtx::Point3D(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<rtx::IMaterial> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = rtx::Color::random() * rtx::Color::random();
                    sphere_material = std::make_shared<rtx::Matte>(albedo);
                    world.add(factory.createShape<rtx::Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = rtx::Color::random(0.5, 1);
                    auto fuzz = randomValue(0, 0.5);
                    sphere_material = std::make_shared<rtx::Metal>(albedo, fuzz);
                    world.add(factory.createShape<rtx::Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<rtx::Dielectric>(1.5);
                    world.add(factory.createShape<rtx::Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<rtx::Dielectric>(1.5);
    world.add(factory.createShape<rtx::Sphere>(rtx::Point3D(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<rtx::Matte>(rtx::Color(0.4, 0.2, 0.1));
    world.add(factory.createShape<rtx::Sphere>(rtx::Point3D(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<rtx::Metal>(rtx::Color(0.7, 0.6, 0.5), 0.0);
    world.add(factory.createShape<rtx::Sphere>(rtx::Point3D(4, 1, 0), 1.0, material3));

    auto matteRed = std::make_shared<rtx::Matte>(rtx::Color(1.0, 0.2, 0.2));
    auto matteRed2 = std::make_shared<rtx::Metal>(rtx::Color(1, 0.078, 0.576), 0.1);
    world.add(factory.createShape<rtx::Plan>(rtx::Point3D(2.5, 0, 2), rtx::Vector3D(1.5, 0, 0), rtx::Vector3D(0, 2, 0), matteRed));
    world.add(factory.createShape<rtx::Plan>(rtx::Point3D(1, 0, 1), rtx::Vector3D(0, 0, 1), rtx::Vector3D(0, 1, 0), matteRed2));

    return world;
}

static rtx::Camera getCam()
{
    rtx::Camera cam(200, 200);

    cam.samplesPerPixel = 50;
    cam.maxDepth         = 50;
    cam._fov     = 20;
    cam._cameraPosition = rtx::Point3D(13,2,3);
    cam._lookAt   = rtx::Point3D(0,0,0);
    cam._cameraAngle      = rtx::Vector3D(0,1,0);
    cam._defocusAngle = 0.6;
    cam._focusDist    = 10.0;
    return cam;
}

int main(int ac, const char *av[])
{
    srand(time(NULL));

    rtx::Scene scene = getScene();
    rtx::Camera cam = getCam();

    if (ac == 2 && std::string(av[1]) == "--help") {
        displayUsage();
        return 0;
    }
    if (ac == 3 && std::string(av[1]) == "-g")
        cam.renderGraphical(scene, av[2]);
    else if (ac == 2)
        cam.render(scene, av[1]);
    else {
        displayUsage();
        return 84;
    }
    return 0;
}

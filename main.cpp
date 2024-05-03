/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main
*/

#include "Camera.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "memes.hpp"
#include "macros.hpp"
#include "Metal.hpp"
#include "Matte.hpp"
#include <memory>
#include <string>
#include <iostream>
#include <random>
#include <ctime>

static void displayUsage()
{
    static const std::string memes[NB_MEMES] = {SHRUG_MEME, FORGOT_BRAIN_MEME, SPONGEBOB_MEME, DOOT_DOOT_MEME, RICK_ROLL_MEME, DERP_MEME, NERD_MEME, RTX_ON_MEME};
    std::size_t randValue = randomValue(0, NB_MEMES);

    std::cout << memes[randValue];
    std::cout << "\033[1mUSAGE\033[m:\t./raytracer [-g]\n"
              << "\t\033[1m-g\033[m\tdisplays in real time the pixels drawing (slows the process)\n";
}

int main(int ac, const char *av[])
{
    rtx::Scene scene;
    rtx::Camera cam(300, 255);

    srand(time(NULL));

    auto ground_material = std::make_shared<rtx::Matte>(rtx::Color(0.5, 0.5, 0.5));
    scene.add(std::make_shared<rtx::Sphere>(rtx::Point3D(0,-1000,0), 1000, ground_material));


    auto material1 = std::make_shared<rtx::Matte>(rtx::Color(0.4, 0.2, 0.1));
    scene.add(std::make_shared<rtx::Sphere>(rtx::Point3D(-4, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<rtx::Matte>(rtx::Color(0.4, 0.2, 0.1));
    scene.add(std::make_shared<rtx::Sphere>(rtx::Point3D(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<rtx::Metal>(rtx::Color(0.7, 0.6, 0.5), 0.0);
    scene.add(std::make_shared<rtx::Sphere>(rtx::Point3D(4, 1, 0), 1.0, material3));

    cam.vfov = 20;

    cam.lookfrom = rtx::Point3D(13, 2,3);
    cam.lookat   = rtx::Point3D(0, 0, 0);
    cam.vup      = rtx::Vector3D(0,1,0);

    cam.samplesPerPixel = 500;
    cam.maxDepth = 50;

    cam.defocus_angle = 0.8;
    cam.focus_dist = 15;

    if (ac == 2 && std::string(av[1]) == "--help") {
        displayUsage();
        return 0;
    }
    if (ac == 2 && std::string(av[1]) == "-g")
        cam.renderGraphical(scene);
    else if (ac == 1)
        cam.render(scene);
    else {
        displayUsage();
        return 84;
    }
    return 0;
}

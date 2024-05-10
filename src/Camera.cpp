/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** camera class
*/

#include "Camera.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"
#include "macros.hpp"
#include "IShape.hpp"
#include "IPC.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iomanip>
#include <thread>
#include "Light.hpp"

rtx::Camera::Camera(int imageWidth, int imageHeight)
    : imageSize(std::make_pair(imageWidth, imageHeight))
    , _intensity(rtx::Interval(0.0, 0.9))
{
    initialize();
}

rtx::Camera::Camera() : _intensity(rtx::Interval(0.0, 0.9))
{
    initialize();
}

double rtx::Camera::toGamma(double linear)
{
    if (linear > 0.0)
        return sqrt(linear);
    return 0.0;
}

void rtx::Camera::smoothenPixels(rtx::Color &color)
{
    color.x = short(256.0 * _intensity.clamp(color.x));
    color.y = short(256.0 * _intensity.clamp(color.y));
    color.z = short(256.0 * _intensity.clamp(color.z));
}

void rtx::Camera::addGamma(rtx::Color &color)
{
    color.x = toGamma(color.x);
    color.y = toGamma(color.y);
    color.z = toGamma(color.z);
}

void rtx::Camera::writeColor(const rtx::Color &color, std::ofstream &ppmFile) const
{
    ppmFile << short(color.x) << ' ' << short(color.y) << ' ' << short(color.z) << '\n';
}

rtx::Color rtx::Camera::getRayColor(const rtx::Ray &ray, int depth, const rtx::IShape &shape) const
{
    if (depth <= 0)
        return rtx::Color();

    rtx::HitRecord rec;

    if (!shape.hits(ray, rtx::Interval(0.001, infinity), rec)) {
        return _backgroundColor;
    }

    rtx::Ray reflected;
    rtx::Color attenuation;
    rtx::Light light;
    rtx::Color color_from_emission = rec.material->lightEmition(rec.u, rec.v, rec.point);

    if (rec.material->reflect(ray, rec, attenuation, reflected)) {
        rtx::Color finalColor = attenuation * getRayColor(reflected, depth - 1, shape);
        light.ambientLight(ambientLight, finalColor, attenuation);
        return finalColor;
    }

    return color_from_emission;
}

rtx::Ray rtx::Camera::getRay(double u, double v) const
{
    auto offset = getSampleSquare();
    rtx::Point3D pixelSample = _pixelOrigin + (_pixelU * (offset.x + u)) + (_pixelV * (offset.y + v));
    rtx::Point3D rayOrigin = (_defocusAngle <= 0.0) ? _origin : defocusDiskSample();
    rtx::Vector3D rayDirection = pixelSample - _origin;

    return rtx::Ray(rayOrigin, rayDirection);
}

rtx::Point3D rtx::Camera::defocusDiskSample() const
{
    rtx::Vector3D vect = rtx::Vector3D::randomInUnitDisk();
    return _origin + (_defocusX * vect.x) + (_defocusY * vect.y);
}

void rtx::Camera::processPixels(std::stringstream &str, std::size_t yMin, std::size_t yMax, const rtx::IShape &shape)
{
    for (std::size_t y = yMin; y < yMax; ++y) {
        for (std::size_t x = 0; x < imageSize.first; ++x) {
            rtx::Color pixelColor;
            for (std::size_t sample = 0; sample < samplesPerPixel; ++sample) {
                rtx::Ray ray = getRay(x, y);
                pixelColor += getRayColor(ray, maxDepth, shape);
            }
            pixelColor *= _pixelSampleScale;
            addGamma(pixelColor);
            smoothenPixels(pixelColor);
            str << std::to_string(short(pixelColor.x)) + ' ' + std::to_string(short(pixelColor.y)) + ' ' + std::to_string(short(pixelColor.z)) + '\n';
        }
    }
}

void rtx::Camera::render(const rtx::IShape &shape, const std::string &sceneFileName)
{
    initialize();

    std::size_t firstExtensionChar = sceneFileName.find(".cfg");
    std::string configFileName = sceneFileName;
    std::ofstream ppmFile;
    rtx::IPC process(std::thread::hardware_concurrency() * 3);

    if (firstExtensionChar == std::string::npos)
        throw rtx::Camera::InvalidFileExtension();
    configFileName.erase(firstExtensionChar, configFileName.length());
    process.launch<rtx::Camera>(&rtx::Camera::processPixels, *this, shape, imageSize.second);
    ppmFile.open(configFileName + ".ppm", std::ios::trunc);
    ppmFile << "P3\n" << imageSize.first << ' ' << imageSize.second << "\n255\n";
    ppmFile << process.recoverValues(BUFSIZ).str();
    ppmFile.close();
}

void rtx::Camera::renderGraphical(const rtx::IShape &shape, const std::string& sceneFileName)
{
    initialize();

    std::size_t firstExtensionChar = sceneFileName.find(".cfg");
    std::string configFileName = sceneFileName;
    std::ofstream ppmFile;

    if (firstExtensionChar == std::string::npos)
        throw rtx::Camera::InvalidFileExtension();
    configFileName.erase(firstExtensionChar, configFileName.length());
    sf::RenderWindow win(sf::VideoMode(imageSize.first, imageSize.second), "Raytracer", sf::Style::Titlebar | sf::Style::Close);
    sf::VertexArray pixels(sf::Points, imageSize.first * imageSize.second);
    ppmFile.open(configFileName + ".ppm", std::ios::trunc);
    ppmFile << "P3\n" << imageSize.first << ' ' << imageSize.second << "\n255\n";
    while (win.isOpen()) {
        for (std::size_t y = 0; y < imageSize.second; ++y) {
            for (std::size_t x = 0; x < imageSize.first; ++x) {
                rtx::Color pixelColor;
                sf::Event evt;
                while (win.pollEvent(evt)) {
                    if (evt.type == sf::Event::Closed) {
                        win.close();
                        ppmFile.close();
                        return;
                    }
                }
                for (std::size_t sample = 0; sample < samplesPerPixel; ++sample) {
                    rtx::Ray ray = getRay(x, y);
                    pixelColor += getRayColor(ray, maxDepth, shape);
                }
                pixelColor *= _pixelSampleScale;
                smoothenPixels(pixelColor);
                writeColor(pixelColor, ppmFile);
                pixels[y * imageSize.first + x].position = sf::Vector2f(x, y);
                pixels[y * imageSize.first + x].color = sf::Color(pixelColor.x, pixelColor.y, pixelColor.z, 255);
            }
            win.clear();
            win.draw(pixels);
            win.display();
        }
        while (true) {
            sf::Event evt;
            while (win.pollEvent(evt)) {
                if (evt.type == sf::Event::Closed ||
                    evt.type == sf::Event::KeyPressed) {
                    win.close();
                    ppmFile.close();
                    return;
                }
            }
        }
    }
}

void rtx::Camera::initialize()
{
    _pixelSampleScale = 1.0 / double(samplesPerPixel);
    _origin = _cameraPosition;

    double theta = degToRad(_fov);
    double h = tan(theta/2);
    double viewHeight = 2 * h * _focusDist;
    double viewWidth = viewHeight * (double(imageSize.first) / imageSize.second);

    rtx::Vector3D w = (_cameraPosition - _lookAt).unitVector();
    rtx::Vector3D u = (_cameraAngle).cross(w).unitVector();
    rtx::Vector3D v = w.cross(u);

    rtx::Vector3D viewU = u * viewWidth;
    _pixelU = viewU / double(imageSize.first);
    rtx::Vector3D viewV = -v * viewHeight;
    _pixelV = viewV / double(imageSize.second);
    rtx::Point3D viewportOrigin = _origin - (w * (_focusDist)) - (viewU / 2.0) - (viewV / 2.0);
    _pixelOrigin = viewportOrigin + ((_pixelU + _pixelV) * 0.5);
    double defocusRad = _focusDist * tan(degToRad(_defocusAngle / 2.0));
    _defocusX = u * defocusRad;
    _defocusY = v * defocusRad;
}

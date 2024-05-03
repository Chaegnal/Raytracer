/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** camera class
*/

#include "Camera.hpp"
#include "Rectangle3D.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"
#include "macros.hpp"
#include "IShape.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

rtx::Camera::Camera(std::size_t imageWidth, std::size_t imageHeight)
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

void rtx::Camera::writeColor(const rtx::Color &color) const
{
    std::cout << short(color.x) << ' ' << short(color.y) << ' ' << short(color.z) << '\n';
}

rtx::Color rtx::Camera::getRayColor(const rtx::Ray &ray, int depth, const rtx::IShape &shape) const
{
    if (depth <= 0)
        return rtx::Color();

    rtx::HitRecord rec;
    if (shape.hits(ray, rtx::Interval(0.001, infinity), rec)) {
        rtx::Vector3D dir = rec.normal + rtx::Vector3D::randomUnitVector();
        return getRayColor(rtx::Ray(rec.point, dir), depth - 1, shape) * 0.5;
        //return (rec.normal + rtx::Vector3D(1.0, 1.0, 1.0)) * 0.5;
    }

    rtx::Vector3D dir = ray.direction.unitVector();
    double a = 0.5 * (dir.y + 1.0);
    return rtx::Vector3D(1.0, 1.0, 1.0) * (1.0 - a) + rtx::Vector3D(0.5, 0.7, 1.0) * a;
}

rtx::Ray rtx::Camera::getRay(double u, double v) const
{
    auto offset = getSampleSquare();
    rtx::Point3D pixelSample = _pixelOrigin + (_pixelU * (offset.x + u)) + (_pixelV * (offset.y + v));
    rtx::Vector3D rayDirection = pixelSample - _origin;

    return rtx::Ray(_origin, rayDirection);
}

void rtx::Camera::render(const rtx::IShape &shape)
{
    std::cout << "P3\n" << imageSize.first << ' ' << imageSize.second << "\n255\n";
    for (std::size_t y = 0; y < imageSize.second; ++y) {
        for (std::size_t x = 0; x < imageSize.first; ++x) {
            rtx::Color pixelColor;
            for (std::size_t sample = 0; sample < samplesPerPixel; ++sample) {
                rtx::Ray ray = getRay(x, y);
                pixelColor += getRayColor(ray, maxDepth, shape);
            }
            pixelColor *= _pixelSampleScale;
            addGamma(pixelColor);
            smoothenPixels(pixelColor);
            writeColor(pixelColor);
        }
    }
}

void rtx::Camera::renderGraphical(const rtx::IShape &shape)
{
    sf::RenderWindow win(sf::VideoMode(imageSize.first, imageSize.second), "Raytracer", sf::Style::Titlebar | sf::Style::Close);
    sf::VertexArray pixels(sf::Points, imageSize.first * imageSize.second);

    std::cout << "P3\n" << imageSize.first << ' ' << imageSize.second << "\n255\n";
    while (win.isOpen()) {
        for (std::size_t y = 0; y < imageSize.second; ++y) {
            for (std::size_t x = 0; x < imageSize.first; ++x) {
                rtx::Color pixelColor;
                sf::Event evt;
                while (win.pollEvent(evt)) {
                    if (evt.type == sf::Event::Closed) {
                        win.close();
                        return;
                    }
                }
                for (std::size_t sample = 0; sample < samplesPerPixel; ++sample) {
                    rtx::Ray ray = getRay(x, y);
                    pixelColor += getRayColor(ray, maxDepth, shape);
                }
                pixelColor *= _pixelSampleScale;
                smoothenPixels(pixelColor);
                writeColor(pixelColor);
                pixels[y * imageSize.second + x].position = sf::Vector2f(x, y);
                pixels[y * imageSize.second + x].color = sf::Color(pixelColor.x, pixelColor.y, pixelColor.z, 255);
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
                    return;
                }
            }
        }
    }
}

void rtx::Camera::initialize()
{
    _pixelSampleScale = 1.0 / double(samplesPerPixel);
    _origin = rtx::Point3D();
    double viewHeight = 2.0;
    double viewWidth = viewHeight * (double(imageSize.first) / imageSize.second);
    rtx::Vector3D u = rtx::Vector3D(viewWidth, 0.0, 0.0);
    _pixelU = u / double(imageSize.first);
    rtx::Vector3D v = rtx::Vector3D(0.0, -viewHeight, 0.0);
    _pixelV = v / double(imageSize.second);
    rtx::Point3D viewportOrigin = _origin - rtx::Vector3D(0.0, 0.0, 1.0) - (u / 2.0) - (v / 2.0);
    _pixelOrigin = viewportOrigin + ((_pixelU + _pixelV) * 0.5);
}

/*
** EPITECH PROJECT, 2024
** Camera.hpp
** File description:
** camera class
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "Ray.hpp"
    #include "Vector3D.hpp"
    #include "IShape.hpp"
    #include "macros.hpp"
    #include <vector>
    #include <mutex>

namespace rtx
{
    class Camera
    {
    private:
        const rtx::Interval _intensity;
        rtx::Point3D _pixelOrigin;
        rtx::Vector3D _pixelU;
        rtx::Vector3D _pixelV;
        rtx::Point3D _origin;
        double _pixelSampleScale;
        rtx::Vector3D u, v, w;
        rtx::Vector3D defocus_disk_u;
        rtx::Vector3D defocus_disk_v;

        void initialize();
        double toGamma(double linear);
        void addGamma(rtx::Color &color);
        void smoothenPixels(rtx::Color &color);
        void writeColor(const rtx::Color &color) const;
        rtx::Color getRayColor(const rtx::Ray &ray, int depth, const rtx::IShape &shape) const;
        rtx::Vector3D getSampleSquare() const {return rtx::Vector3D(randomValue() - 0.5, randomValue() - 0.5, 0.0);}
        rtx::Point3D defocus_disk_sample() const;

    public:
        Camera();
        Camera(std::size_t imageWidth, std::size_t imageHeight);
        ~Camera() = default;

        std::size_t samplesPerPixel = 250;
        std::size_t maxDepth = 50;
        std::pair<std::size_t, std::size_t> imageSize = std::make_pair(256, 256);
        double vfov = 90;
        rtx::Point3D lookfrom = rtx::Point3D(0,0,0);
        rtx::Point3D lookat = rtx::Point3D(0,0,-1);
        rtx::Vector3D vup = rtx::Vector3D(0,1,0); 
        double defocus_angle = 0;
        double focus_dist = 10;

        rtx::Ray getRay(double u, double v) const;
        void render(const rtx::IShape &shape);
        void renderGraphical(const rtx::IShape &shape);
    };
}

#endif

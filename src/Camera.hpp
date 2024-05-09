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
    #include <fstream>

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
        rtx::Vector3D _defocusX;
        rtx::Vector3D _defocusY;

        void initialize();
        double toGamma(double linear);
        void addGamma(rtx::Color &color);
        void smoothenPixels(rtx::Color &color);
        void writeColor(const rtx::Color &color, std::ofstream &ppmFile) const;
        rtx::Color getRayColor(const rtx::Ray &ray, int depth, const rtx::IShape &shape) const;
        rtx::Vector3D getSampleSquare() const {return rtx::Vector3D(randomValue() - 0.5, randomValue() - 0.5, 0.0);}
        rtx::Point3D defocusDiskSample() const;

    public:
        Camera();
        Camera(int imageWidth, int imageHeight);
        ~Camera() = default;

        std::size_t samplesPerPixel = 250;
        std::size_t maxDepth = 50;
        std::pair<std::size_t, std::size_t> imageSize = std::make_pair(256, 256);
        double _fov = 90.0;
        rtx::Point3D _cameraPosition = rtx::Point3D();
        rtx::Point3D _lookAt = rtx::Point3D(0.0, 0.0, -1.0);
        rtx::Vector3D _cameraAngle = rtx::Vector3D(0.0, 1.0, 0.0);
        double _defocusAngle = 0.0;
        double _focusDist = 10.0;
        rtx::Color _backgroundColor;

        void processPixels(std::stringstream &str, std::size_t yMin, std::size_t yMax, const rtx::IShape &shape);
        rtx::Ray getRay(double u, double v) const;
        int render(const rtx::IShape &shape, const std::string& sceneFileName);
        int renderGraphical(const rtx::IShape &shape, const std::string& sceneFileName);
    };
}

#endif

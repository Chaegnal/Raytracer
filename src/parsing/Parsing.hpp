/*
** EPITECH PROJECT, 2024
** rtx
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <libconfig.h++>
#include <iostream>
#include <vector>
#include <tuple>

class Parsing {

    private:
    public:
        Parsing();
        ~Parsing();

        struct SphereInfo {
            double x, y, z;
            double radius;
            double extra;
            double r, g, b;
            std::string material;
        };

        struct CylinderConeInfo {
            double x, y, z;
            double height;
            double radius;
            double extra;
            double r, g, b;
            std::string material;
        };

        struct PlaneInfo {
            double x, y, z;
            double size_x, size_y, size_z;
            double height_x, height_y, height_z;
            double r, g, b;
            double extra;
            std::string material;
        };

        double parseCamFOV(libconfig::Config &conf);
        std::tuple<double, double, double> parseCamPosition(libconfig::Config &conf);
        int parseCamSample(libconfig::Config &conf);
        int parseCamDepth(libconfig::Config &conf);
        std::tuple<double, double, double> parseCamLookAt(libconfig::Config &conf);
        std::tuple<double, double, double> parseCamAngle(libconfig::Config &conf);
        float parseCamFocus(libconfig::Config &conf);
        float parseCamDefocus(libconfig::Config &conf);

        std::vector<SphereInfo> parseSphere(libconfig::Config &conf);

        std::vector<CylinderConeInfo> parseCylinder(libconfig::Config &conf);
        std::vector<CylinderConeInfo> parseCone(libconfig::Config &conf);

        std::vector<PlaneInfo> parsePlane(libconfig::Config &conf);

        void parseAmbientDiffuse(libconfig::Config &conf);
        void parsePointLight(libconfig::Config &conf);
        void parseLights(libconfig::Config &conf);

    protected:

};

#endif /* !PARSING_HPP_ */

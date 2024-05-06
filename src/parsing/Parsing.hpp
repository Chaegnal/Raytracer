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

class Parsing {

    private:
    public:
        Parsing();
        ~Parsing();

        struct SphereInfo {
            int x, y, z;
            float radius;
            float extra;
            float r, g, b;
            std::string material;
        };

        struct CylinderInfo {
            int x, y, z;
            double height;
            float radius;
            float extra;
            float r, g, b;
            std::string material;
        };

        struct PlaneInfo {
            double x, y, z;
            double size_x, size_y, size_z;
            double height_x, height_y, height_z;
            float r, g, b;
            float extra;
            std::string material;
        };

        double parseCamFOV(libconfig::Config &conf);
        std::tuple<int, int, int> parseCamPosition(libconfig::Config &conf);
        int parseCamSample(libconfig::Config &conf);
        int parseCamDepth(libconfig::Config &conf);
        std::tuple<int, int, int> parseCamLookAt(libconfig::Config &conf);
        std::tuple<int, int, int> parseCamAngle(libconfig::Config &conf);
        float parseCamFocus(libconfig::Config &conf);
        float parseCamDefocus(libconfig::Config &conf);

        std::vector<SphereInfo> parseSphere(libconfig::Config &conf);

        std::vector<CylinderInfo> parseCylinder(libconfig::Config &conf);

        std::vector<PlaneInfo> parsePlane(libconfig::Config &conf);

        void parseAmbientDiffuse(libconfig::Config &conf);
        void parsePointLight(libconfig::Config &conf);
        void parseLights(libconfig::Config &conf);

    protected:

};

#endif /* !PARSING_HPP_ */

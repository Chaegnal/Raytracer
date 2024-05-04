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

class Parsing {
    public:
        Parsing();
        ~Parsing();

        void parseCamFOV(libconfig::Config &conf);
        void parseCamRotation(libconfig::Config &conf);
        void parseCamResolution(libconfig::Config &conf);
        void parseCamPosition(libconfig::Config &conf);
        void parseCamera(libconfig::Config &conf);
        void parseSphere(libconfig::Config &conf);
        void parsePlane(libconfig::Config &conf);
        void parsePrimitive(libconfig::Config &conf);
        void parseAmbientDiffuse(libconfig::Config &conf);
        void parsePointLight(libconfig::Config &conf);
        void parseLights(libconfig::Config &conf);
        int parsingFile(int ac, char **av);

    protected:
    private:
};

#endif /* !PARSING_HPP_ */

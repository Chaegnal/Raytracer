/*
** EPITECH PROJECT, 2024
** rtx
** File description:
** Parsing
*/

#include "Parsing.hpp"

Parsing::Parsing()
{
}

Parsing::~Parsing()
{
}

void Parsing::parseCamFOV(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];
    float fov = 0;

    try {
        fov = camera.lookup("fieldOfView");
        std::cout << "FieldofView: " << "fov = " << fov << std::endl;
    } catch (const libconfig::SettingNotFoundException &) {
    }
}

void Parsing::parseCamRotation(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    int x = 0;
    int y = 0;
    int z = 0;

    try {
        const libconfig::Setting &camera = root["camera"]["rotation"];

        if(!(camera.lookupValue("x", x)
               && camera.lookupValue("y", y)
               && camera.lookupValue("z", z)))
            return;

          std::cout << "Camera Rotation: " << "x = " << x << " y = " << y << " z = " << z << std::endl;
    } catch (const libconfig::SettingNotFoundException &) {
    }
}

void Parsing::parseCamResolution(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    int width;
    int height;

    try {
        const libconfig::Setting &camera = root["camera"]["resolution"];

        if(!(camera.lookupValue("width", width)
               && camera.lookupValue("height", height)))
            return;

          std::cout << "Camera Res: " << "width = " << width << " height =  " << height << std::endl;
    } catch (const libconfig::SettingNotFoundException &) {
    }
}

void Parsing::parseCamPosition(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    int x = 0;
    int y = 0;
    int z = 0;

    try {
        const libconfig::Setting &camera = root["camera"]["position"];

        if(!(camera.lookupValue("x", x)
               && camera.lookupValue("y", y)
               && camera.lookupValue("z", z)))
            return;

          std::cout << "Camera Pos: " << "x = " << x << " y = " << y << " z = " << z << std::endl;
    } catch (const libconfig::SettingNotFoundException &) {
    }
}

void Parsing::parseCamera(libconfig::Config &conf)
{
    parseCamResolution(conf);
    parseCamPosition(conf);
    parseCamRotation(conf);
    parseCamFOV(conf);
}

void Parsing::parseSphere(libconfig::Config &conf)
{
    int x, y, z, radius, r, g, b;
    float grain;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &sphere = root["primitives"]["spheres"];
        int count = sphere.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &oneSphere = sphere[i];
            const libconfig::Setting &color = oneSphere["color"];

            if(!(oneSphere.lookupValue("x", x)
                && oneSphere.lookupValue("y", y)
                && oneSphere.lookupValue("z", z)
                && oneSphere.lookupValue("r", radius)
                && color.lookupValue("r", r)
                && color.lookupValue("g", g)
                && color.lookupValue("b", b)
                && oneSphere.lookupValue("grain", grain)))
                continue;


            std::cout << "Sphere " << i << ": " << "x = " << x << " y =  " << y << "  "
                << "z = " << z << "  "
                << "radius = " << radius << " {color: r = " << r << " g = " << g << " b = " << b << "}" << " grain = " << grain << std::endl;
        }

    } catch(const libconfig::SettingNotFoundException &) {
    }
}

void Parsing::parsePlane(libconfig::Config &conf)
{
    std::string axis;
    int position, r, g, b;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &planes = root["primitives"]["planes"];
        int count = planes.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &onePlane = planes[i];
            const libconfig::Setting &color = onePlane["color"];

            if(!(onePlane.lookupValue("axis", axis)
                && onePlane.lookupValue("position", position)
                && color.lookupValue("r", r)
                && color.lookupValue("g", g)
                && color.lookupValue("b", b)))
                continue;

            std::cout << "Plane " << i << ": " << "x = " << axis << " y =  " << position << " {color: r = " << r << " g = " << g << " b = " << b << "}" << std::endl;
        }

    } catch(const libconfig::SettingNotFoundException &) {
    }
}

void Parsing::parsePrimitive(libconfig::Config &conf)
{
    parseSphere(conf);
    parsePlane(conf);
}

void Parsing::parseAmbientDiffuse(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &lights = root["lights"];
    float ambient = 0;
    float diffuse = 0;

    try {
        ambient = lights.lookup("ambient");
        diffuse = lights.lookup("diffuse");
        std::cout << "Ligths: " << "ambient = " << ambient << " diffuse =" << diffuse << std::endl;
    } catch (const libconfig::SettingNotFoundException &) {
    }
}

void Parsing::parsePointLight(libconfig::Config &conf)
{
    int x, y, z;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &point = root["lights"]["point"];
        int count = point.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &oneLight = point[i];
            if(!(oneLight.lookupValue("x", x)
                && oneLight.lookupValue("y", y)
                && oneLight.lookupValue("z", z)))
                continue;
            std::cout << "Point Lights: x = " << x << " y = " << y << " z = " << z << std::endl;
        }

    } catch(const libconfig::SettingNotFoundException &) {
    }
}

void Parsing::parseLights(libconfig::Config &conf)
{
    parseAmbientDiffuse(conf);
    parsePointLight(conf);
}

int Parsing::parsingFile(int ac, char **av)
{
    libconfig::Config conf;

    if (av[1] == NULL)
        return 84;
    try {
        conf.readFile(av[1]);
    } catch (const libconfig::FileIOException &) {
        std::cerr << "Could not open the file" << std::endl;
        return (EXIT_FAILURE);
    }
    catch(const libconfig::ParseException &err) {
        std::cerr << "Parse error at " << err.getFile() << ":" << err.getLine()
              << " - " << err.getError() << std::endl;
        return(EXIT_FAILURE);
    }
    parseCamera(conf);
    parsePrimitive(conf);
    parseLights(conf);
    return(EXIT_SUCCESS);
}


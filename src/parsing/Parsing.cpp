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

//cam

double Parsing::parseCamFOV(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("fieldOfView");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

int Parsing::parseCamSample(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("sample");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

int Parsing::parseCamDepth(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("maxDepth");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

float Parsing::parseCamDefocus(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("defocusAngle");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

float Parsing::parseCamFocus(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("focusDist");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

std::tuple<double, double, double> Parsing::parseCamPosition(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    std::tuple<double, double, double> pos;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    try {
        const libconfig::Setting &camera = root["camera"]["position"];

        if(!(camera.lookupValue("x", x)
            && camera.lookupValue("y", y)
            && camera.lookupValue("z", z)))
                return std::make_tuple(0, 0, 0);
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return std::make_tuple(x, y, z);
}

std::tuple<double, double, double> Parsing::parseCamLookAt(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    std::tuple<double, double, double> pos;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    try {
        const libconfig::Setting &camera = root["camera"]["lookAt"];

        if(!(camera.lookupValue("x", x)
            && camera.lookupValue("y", y)
            && camera.lookupValue("z", z)))
                return std::make_tuple(0, 0, 0);
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return std::make_tuple(x, y, z);
}

std::tuple<double, double, double> Parsing::parseCamAngle(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    std::tuple<double, double, double> pos;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    try {
        const libconfig::Setting &camera = root["camera"]["angle"];

        if(!(camera.lookupValue("x", x)
            && camera.lookupValue("y", y)
            && camera.lookupValue("z", z)))
                return std::make_tuple(0, 0, 0);
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return std::make_tuple(x, y, z);
}


//sphere

std::vector<Parsing::SphereInfo> Parsing::parseSphere(libconfig::Config &conf)
{
    std::vector<SphereInfo> sphereParsed;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &sphere = root["primitives"]["spheres"];
        int count = sphere.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &oneSphere = sphere[i];
            const libconfig::Setting &color = oneSphere["color"];
            SphereInfo infoSphere;

            if(!(oneSphere.lookupValue("x", infoSphere.x)
                && oneSphere.lookupValue("y", infoSphere.y)
                && oneSphere.lookupValue("z", infoSphere.z)
                && color.lookupValue("r", infoSphere.r)
                && color.lookupValue("g", infoSphere.g)
                && color.lookupValue("b", infoSphere.b)
                && oneSphere.lookupValue("radius", infoSphere.radius)
                && oneSphere.lookupValue("material", infoSphere.material)
                && oneSphere.lookupValue("extra", infoSphere.extra)))
                continue;

            sphereParsed.push_back(infoSphere);
        }
    } catch(const libconfig::SettingNotFoundException &) {
    }

    return sphereParsed;
}

std::vector<Parsing::CylinderConeInfo> Parsing::parseCylinder(libconfig::Config &conf)
{
    std::vector<CylinderConeInfo> cylinderParsed;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &cylinder = root["primitives"]["cylinder"];
        int count = cylinder.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &oneCylinder = cylinder[i];
            const libconfig::Setting &color = oneCylinder["color"];
            CylinderConeInfo infoCylinder;

            if(!(oneCylinder.lookupValue("x", infoCylinder.x)
                && oneCylinder.lookupValue("y", infoCylinder.y)
                && oneCylinder.lookupValue("z", infoCylinder.z)
                && color.lookupValue("r", infoCylinder.r)
                && color.lookupValue("g", infoCylinder.g)
                && color.lookupValue("b", infoCylinder.b)
                && oneCylinder.lookupValue("radius", infoCylinder.radius)
                && oneCylinder.lookupValue("material", infoCylinder.material)
                && oneCylinder.lookupValue("extra", infoCylinder.extra)
                && oneCylinder.lookupValue("heigt", infoCylinder.height)))
                continue;

            cylinderParsed.push_back(infoCylinder);
        }
    } catch(const libconfig::SettingNotFoundException &) {
    }

    return cylinderParsed;
}

std::vector<Parsing::CylinderConeInfo> Parsing::parseCone(libconfig::Config &conf)
{
    std::vector<CylinderConeInfo> cylinderParsed;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &cylinder = root["primitives"]["cones"];
        int count = cylinder.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &oneCylinder = cylinder[i];
            const libconfig::Setting &color = oneCylinder["color"];
            CylinderConeInfo infoCylinder;

            if(!(oneCylinder.lookupValue("x", infoCylinder.x)
                && oneCylinder.lookupValue("y", infoCylinder.y)
                && oneCylinder.lookupValue("z", infoCylinder.z)
                && color.lookupValue("r", infoCylinder.r)
                && color.lookupValue("g", infoCylinder.g)
                && color.lookupValue("b", infoCylinder.b)
                && oneCylinder.lookupValue("radius", infoCylinder.radius)
                && oneCylinder.lookupValue("material", infoCylinder.material)
                && oneCylinder.lookupValue("extra", infoCylinder.extra)
                && oneCylinder.lookupValue("heigt", infoCylinder.height)))
                continue;

            cylinderParsed.push_back(infoCylinder);
        }
    } catch(const libconfig::SettingNotFoundException &) {
    }

    return cylinderParsed;
}

std::vector<Parsing::PlaneInfo> Parsing::parsePlane(libconfig::Config &conf)
{
    std::vector<PlaneInfo> planeParsed;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &planes = root["primitives"]["planes"];

        int count = planes.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &onePlane = planes[i];
            const libconfig::Setting &sizePlane = onePlane["size"];
            const libconfig::Setting &anglePlane = onePlane["angle"];
            const libconfig::Setting &colorPlane = onePlane["color"];
            PlaneInfo infoPlane;

            if(!(onePlane.lookupValue("x", infoPlane.x)
                && onePlane.lookupValue("y", infoPlane.y)
                && onePlane.lookupValue("z", infoPlane.z)
                && onePlane.lookupValue("extra", infoPlane.extra)
                && onePlane.lookupValue("material", infoPlane.material)
                && sizePlane.lookupValue("x", infoPlane.size_x)
                && sizePlane.lookupValue("y", infoPlane.size_y)
                && sizePlane.lookupValue("z", infoPlane.size_z)
                && anglePlane.lookupValue("x", infoPlane.height_x)
                && anglePlane.lookupValue("y", infoPlane.height_y)
                && anglePlane.lookupValue("z", infoPlane.height_z)
                && colorPlane.lookupValue("r", infoPlane.r)
                && colorPlane.lookupValue("g", infoPlane.g)
                && colorPlane.lookupValue("b", infoPlane.b)))
                continue;

            planeParsed.push_back(infoPlane);
        }
    } catch(const libconfig::SettingNotFoundException &) {
    }
    return planeParsed;
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
    double x, y, z;
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

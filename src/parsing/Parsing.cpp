/*
** EPITECH PROJECT, 2024
** rtx
** File description:
** Parsing
*/

#include "Parsing.hpp"

rtx::Parsing::Parsing()
{
}

rtx::Parsing::~Parsing()
{
}

double rtx::Parsing::parseCamFOV(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("fieldOfView");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

int rtx::Parsing::parseCamSample(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("sample");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

int rtx::Parsing::parseCamDepth(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("maxDepth");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

float rtx::Parsing::parseCamDefocus(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("defocusAngle");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

float rtx::Parsing::parseCamFocus(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    const libconfig::Setting &camera = root["camera"];

    try {
        return camera.lookup("focusDist");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return 0;
}

std::tuple<double, double, double> rtx::Parsing::parseCamPosition(libconfig::Config &conf)
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

std::tuple<double, double, double> rtx::Parsing::parseCamLookAt(libconfig::Config &conf)
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

std::tuple<double, double, double> rtx::Parsing::parseCamAngle(libconfig::Config &conf)
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

std::tuple<double, double, double> rtx::Parsing::parseCamColor(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    std::tuple<double, double, double> col;
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    try {
        const libconfig::Setting &camera = root["camera"]["color"];

        if(!(camera.lookupValue("r", r)
            && camera.lookupValue("g", g)
            && camera.lookupValue("b", b)))
            return std::make_tuple(0, 0, 0);
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return std::make_tuple(r, g, b);
}

std::tuple<int, int> rtx::Parsing::parseCamRatio(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    std::tuple<int, int> ratio;
    int x = 0.0;
    int y = 0.0;

    try {
        const libconfig::Setting &camera = root["camera"]["ratio"];

        if(!(camera.lookupValue("x", x)
            && camera.lookupValue("y", y)))
            return std::make_tuple(0, 0);
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return std::make_tuple(x, y);
}


std::vector<rtx::Parsing::SphereInfo> rtx::Parsing::parseSphere(libconfig::Config &conf)
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
            const libconfig::Setting &transfo = oneSphere["transformation"];
            const libconfig::Setting &axis = transfo["axis"];
            SphereInfo infoSphere;

            if(!(oneSphere.lookupValue("x", infoSphere.x)
                && oneSphere.lookupValue("y", infoSphere.y)
                && oneSphere.lookupValue("z", infoSphere.z)
                && oneSphere.lookupValue("radius", infoSphere.radius)
                && color.lookupValue("r", infoSphere.material.r)
                && color.lookupValue("g", infoSphere.material.g)
                && color.lookupValue("b", infoSphere.material.b)
                && oneSphere.lookupValue("material", infoSphere.material.material)
                && oneSphere.lookupValue("extra", infoSphere.material.extra)
                && transfo.lookupValue("type", infoSphere.material.transformation)
                && transfo.lookupValue("angle", infoSphere.material.angle)
                && axis.lookupValue("x", infoSphere.material.x)
                && axis.lookupValue("y", infoSphere.material.y)
                && axis.lookupValue("z", infoSphere.material.z)))
                continue;

            sphereParsed.push_back(infoSphere);
        }
    } catch(const libconfig::SettingNotFoundException &) {
    }

    return sphereParsed;
}

std::vector<rtx::Parsing::CylinderConeInfo> rtx::Parsing::parseCylinder(libconfig::Config &conf)
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
            const libconfig::Setting &transfo = oneCylinder["transformation"];
            const libconfig::Setting &axis = transfo["axis"];
            CylinderConeInfo infoCylinder;

            if(!(oneCylinder.lookupValue("x", infoCylinder.x)
                && oneCylinder.lookupValue("y", infoCylinder.y)
                && oneCylinder.lookupValue("z", infoCylinder.z)
                && oneCylinder.lookupValue("heigt", infoCylinder.height)
                && oneCylinder.lookupValue("radius", infoCylinder.radius)
                && color.lookupValue("r", infoCylinder.material.r)
                && color.lookupValue("g", infoCylinder.material.g)
                && color.lookupValue("b", infoCylinder.material.b)
                && oneCylinder.lookupValue("material", infoCylinder.material.material)
                && oneCylinder.lookupValue("extra", infoCylinder.material.extra)
                && transfo.lookupValue("type", infoCylinder.material.transformation)
                && transfo.lookupValue("angle", infoCylinder.material.angle)
                && axis.lookupValue("x", infoCylinder.material.x)
                && axis.lookupValue("y", infoCylinder.material.y)
                && axis.lookupValue("z", infoCylinder.material.z)))
                continue;

            cylinderParsed.push_back(infoCylinder);
        }
    } catch(const libconfig::SettingNotFoundException &) {
    }

    return cylinderParsed;
}

std::vector<rtx::Parsing::CylinderConeInfo> rtx::Parsing::parseCone(libconfig::Config &conf)
{
    std::vector<CylinderConeInfo> coneParsed;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &Cone = root["primitives"]["cones"];
        int count = Cone.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &oneCone = Cone[i];
            const libconfig::Setting &color = oneCone["color"];
            const libconfig::Setting &transfo = oneCone["transformation"];
            const libconfig::Setting &axis = transfo["axis"];
            CylinderConeInfo infoCone;

            if(!(oneCone.lookupValue("x", infoCone.x)
                && oneCone.lookupValue("y", infoCone.y)
                && oneCone.lookupValue("z", infoCone.z)
                && oneCone.lookupValue("radius", infoCone.radius)
                && oneCone.lookupValue("heigt", infoCone.height)
                && color.lookupValue("r", infoCone.material.r)
                && color.lookupValue("g", infoCone.material.g)
                && color.lookupValue("b", infoCone.material.b)
                && oneCone.lookupValue("material", infoCone.material.material)
                && oneCone.lookupValue("extra", infoCone.material.extra)
                && transfo.lookupValue("type", infoCone.material.transformation)
                && transfo.lookupValue("angle", infoCone.material.angle)
                && axis.lookupValue("x", infoCone.material.x)
                && axis.lookupValue("y", infoCone.material.y)
                && axis.lookupValue("z", infoCone.material.z)))
                continue;

            coneParsed.push_back(infoCone);
        }
    } catch(const libconfig::SettingNotFoundException &) {
    }

    return coneParsed;
}

std::vector<rtx::Parsing::PlaneTriangleInfo> rtx::Parsing::parsePlane(libconfig::Config &conf)
{
    std::vector<PlaneTriangleInfo> planeParsed;
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
            const libconfig::Setting &transfo = onePlane["transformation"];
            const libconfig::Setting &axis = transfo["axis"];
            PlaneTriangleInfo infoPlane;

            if(!(onePlane.lookupValue("x", infoPlane.x)
                && onePlane.lookupValue("y", infoPlane.y)
                && onePlane.lookupValue("z", infoPlane.z)
                && sizePlane.lookupValue("x", infoPlane.size_x)
                && sizePlane.lookupValue("y", infoPlane.size_y)
                && sizePlane.lookupValue("z", infoPlane.size_z)
                && anglePlane.lookupValue("x", infoPlane.height_x)
                && anglePlane.lookupValue("y", infoPlane.height_y)
                && anglePlane.lookupValue("z", infoPlane.height_z)
                && onePlane.lookupValue("extra", infoPlane.material.extra)
                && onePlane.lookupValue("material", infoPlane.material.material)
                && colorPlane.lookupValue("r", infoPlane.material.r)
                && colorPlane.lookupValue("g", infoPlane.material.g)
                && colorPlane.lookupValue("b", infoPlane.material.b)
                && transfo.lookupValue("type", infoPlane.material.transformation)
                && transfo.lookupValue("angle", infoPlane.material.angle)
                && axis.lookupValue("x", infoPlane.material.x)
                && axis.lookupValue("y", infoPlane.material.y)
                && axis.lookupValue("z", infoPlane.material.z)))
                continue;

            planeParsed.push_back(infoPlane);
        }
    } catch(const libconfig::SettingNotFoundException &) {
    }
    return planeParsed;
}

std::vector<rtx::Parsing::PlaneTriangleInfo> rtx::Parsing::parseTriangles(libconfig::Config &conf)
{
    std::vector<PlaneTriangleInfo> triangleParsed;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &triangles = root["primitives"]["triangles"];

        int count = triangles.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &oneTriangle = triangles[i];
            const libconfig::Setting &firstSummit = oneTriangle["first"];
            const libconfig::Setting &secondSummit = oneTriangle["second"];
            const libconfig::Setting &thirdSummit = oneTriangle["third"];
            const libconfig::Setting &color = oneTriangle["color"];
            const libconfig::Setting &transfo = oneTriangle["transformation"];
            const libconfig::Setting &axis = transfo["axis"];
            PlaneTriangleInfo infoTriangle;

            if(!(oneTriangle.lookupValue("extra", infoTriangle.material.extra)
                && oneTriangle.lookupValue("material", infoTriangle.material.material)
                && firstSummit.lookupValue("x", infoTriangle.x)
                && firstSummit.lookupValue("y", infoTriangle.y)
                && firstSummit.lookupValue("z", infoTriangle.z)
                && secondSummit.lookupValue("x", infoTriangle.size_x)
                && secondSummit.lookupValue("y", infoTriangle.size_y)
                && secondSummit.lookupValue("z", infoTriangle.size_z)
                && thirdSummit.lookupValue("x", infoTriangle.height_x)
                && thirdSummit.lookupValue("y", infoTriangle.height_y)
                && thirdSummit.lookupValue("z", infoTriangle.height_z)
                && color.lookupValue("r", infoTriangle.material.r)
                && color.lookupValue("g", infoTriangle.material.g)
                && color.lookupValue("b", infoTriangle.material.b)
                && transfo.lookupValue("type", infoTriangle.material.transformation)
                && transfo.lookupValue("angle", infoTriangle.material.angle)
                && axis.lookupValue("x", infoTriangle.material.x)
                && axis.lookupValue("y", infoTriangle.material.y)
                && axis.lookupValue("z", infoTriangle.material.z)))
                continue;

            triangleParsed.push_back(infoTriangle);
        }
    } catch(const libconfig::SettingNotFoundException &) {
    }
    return triangleParsed;
}

std::pair<double, double> rtx::Parsing::parseAmbientDiffuse(libconfig::Config &conf)
{
    const libconfig::Setting &root = conf.getRoot();
    std::pair<double, double> lightInfo;

    try {
        const libconfig::Setting &lights = root["lights"];

        lightInfo.first = lights.lookup("ambient");
        lightInfo.second = lights.lookup("diffuse");
    } catch (const libconfig::SettingNotFoundException &) {
    }
    return lightInfo;
}

std::vector<rtx::Parsing::LightInfo> rtx::Parsing::parsePointLight(libconfig::Config &conf)
{
    std::vector<LightInfo> lightInfo;
    const libconfig::Setting &root = conf.getRoot();

    try {
        const libconfig::Setting &point = root["lights"]["point"];
        int count = point.getLength();

        for(int i = 0; i < count; ++i)
        {
            const libconfig::Setting &oneLight = point[i];
            const libconfig::Setting &colorLight = oneLight["color"];
            LightInfo light;
            if(!(oneLight.lookupValue("x", light.x)
                && oneLight.lookupValue("y", light.y)
                && oneLight.lookupValue("z", light.z)
                && colorLight.lookupValue("r", light.r)
                && colorLight.lookupValue("g", light.g)
                && colorLight.lookupValue("b", light.b)
                && oneLight.lookupValue("size", light.size)))
                continue;

            lightInfo.push_back(light);
        }

    } catch(const libconfig::SettingNotFoundException &) {
    }
    return lightInfo;
}

std::pair<std::pair<double, double>, std::vector<rtx::Parsing::LightInfo>> rtx::Parsing::parseLights(libconfig::Config &conf)
{
    std::pair<std::pair<double, double>, std::vector<rtx::Parsing::LightInfo>> allLightInfo;
    allLightInfo.first = parseAmbientDiffuse(conf);
    allLightInfo.second = parsePointLight(conf);
    return allLightInfo;
}

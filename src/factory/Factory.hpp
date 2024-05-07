/*
** EPITECH PROJECT, 2024
** rtx
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <iostream>
#include <memory>
#include <libconfig.h++>
#include <map>
#include "IMaterial.hpp"
#include "IShape.hpp"
#include "Scene.hpp"

namespace rtx {
    class Factory {
        public:
            enum class MaterialTypes {
                Metal,
                Matte,
                Dielectric
            };

            enum class ShapeTypes {
                Sphere,
                Cone,
                Cylinder,
                Plane
            };

        private:
            libconfig::Config &_conf;

        public:
            Factory(libconfig::Config &conf);
            ~Factory() = default;

            template<typename Shape, typename ...Argument>
            std::shared_ptr<rtx::IShape> createShape(Argument... args) {
                return std::make_shared<Shape>(std::forward<Argument>(args)...);
            }

            void createWorldFromConfFile(rtx::Scene &world);
            void createSphereFromConfFile(rtx::Scene &world);
            void createPlaneFromConfFile(rtx::Scene &world);
            void createConeFromConfFile(rtx::Scene &world);
            void createCylinderFromConfFile(rtx::Scene &world);
    };
}

#endif /* !FACTORY_HPP_ */

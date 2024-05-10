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
#include "Metal.hpp"
#include "Matte.hpp"
#include "Dielectric.hpp"
#include "IShape.hpp"
#include "Scene.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "Triangle.hpp"
#include "Error.hpp"
#include "Light.hpp"

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

            class UnknownShapeType : public virtual rtx::Error
            {
            public:
                UnknownShapeType() noexcept
                {
                    _message = "unknown shape given";
                }

                const char *what() const noexcept override {return _message.c_str();}
            };

            class UnknownMaterialType : public virtual rtx::Error
            {
            public:
                UnknownMaterialType() noexcept
                {
                    _message = "unknown material given";
                }

                const char *what() const noexcept override {return _message.c_str();}
            };

        private:
            libconfig::Config &_conf;

        public:
            Factory(libconfig::Config &conf);
            ~Factory() = default;

            template<typename Shape, typename... Argument>
            static std::shared_ptr<rtx::IShape> createShape(Argument... args) {
                return std::make_shared<Shape>(std::forward<Argument>(args)...);
            }
            template<typename Material, typename ...Argument>
            static std::shared_ptr<rtx::IMaterial> createMaterial(Argument... args) {
                return std::make_shared<Material>(std::forward<Argument>(args)...);
            }

            void createWorldFromConfFile(rtx::Scene &world);
            void createSphereFromConfFile(rtx::Scene &world);
            void createPlaneFromConfFile(rtx::Scene &world);
            void createTriangleFromConfFile(rtx::Scene &world);
            void createConeFromConfFile(rtx::Scene &world);
            void createCylinderFromConfFile(rtx::Scene &world);
    };
}

#endif /* !FACTORY_HPP_ */

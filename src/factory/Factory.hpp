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
#include "IShape.hpp"

namespace rtx {
    class Factory {
        public:
            Factory();
            ~Factory();

            template<typename Shape, typename ...Argument>
            std::shared_ptr<rtx::IShape>createShape(Argument... args) {
                return std::make_shared<Shape>(std::forward<Argument>(args)...);
            }

        protected:
        private:
    };
}

#endif /* !FACTORY_HPP_ */

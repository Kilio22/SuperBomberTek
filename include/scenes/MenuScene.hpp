/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuScene
*/

#ifndef MENUSCENE_HPP_
#define MENUSCENE_HPP_

#include "IScene.hpp"
#include "Parallax.hpp"
#include "ContextManager.hpp"
#include <vector>

namespace Indie {
    class MenuScene : public IScene {
        public:
            MenuScene() = default;
            ~MenuScene() = default;

            bool init(ContextManager &context);
            bool reset(ContextManager &context);
            void update(irr::f32 deltaTime);
            void renderPre3D();
            void renderPost3D();

        private:
            ContextManager *context;
            static const irr::core::vector2df velocities[5];
            std::vector<Parallax> parallax;
    };
}

#endif /* !MENUSCENE_HPP_ */
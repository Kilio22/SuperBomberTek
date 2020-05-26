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
            MenuScene(ContextManager &context);
            ~MenuScene();

            void init();
            void reset();
            void update(irr::f32 deltaTime);
            void renderPre3D();
            void renderPost3D();
            void setColor(irr::video::SColor color);

        private:
            static const irr::core::vector2df velocities[5];
            static const std::string filepaths[5];

            ContextManager &context;
            std::vector<std::unique_ptr<Parallax>> parallax;
    };
}

#endif /* !MENUSCENE_HPP_ */
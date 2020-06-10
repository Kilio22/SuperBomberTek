/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CreditScene
*/

#ifndef CREDITSCENE_HPP_
#define CREDITSCENE_HPP_

#include "ContextManager.hpp"
#include "IScene.hpp"
#include "irrlicht.h"
#include <memory>
#include <string>
#include <vector>
#include <utility>

namespace Indie
{
    class CreditScene : public IScene
    {
        public:
            CreditScene(ContextManager &context);
            ~CreditScene() = default;

            void init() final;
            void reset() final;
            void update(irr::f32 deltaTime) final;
            void renderPre3D() final;
            void renderPost3D() final;

        private:
            enum class TEXT_SIZE
            {
                SMALL=0,
                MEDIUM=1,
                BIG=2
            };

            ContextManager &context;
            const float speed;
            float pos;
            irr::gui::IGUIFont *fonts[3];
            static const std::vector<std::pair<irr::core::stringw, TEXT_SIZE>> lines;
            std::vector<std::pair<irr::gui::IGUIStaticText *, float>> texts;
    };
}


#endif /* !CREDITSCENE_HPP_ */
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuScene
*/

#ifndef MENUSCENE_HPP_
#define MENUSCENE_HPP_

#include "ContextManager.hpp"
#include "IScene.hpp"
#include "Parallax.hpp"
#include "MasterInfo.hpp"
#include <memory>
#include <vector>

namespace Indie
{
    class MenuScene : public IScene
    {
        public:
        MenuScene(ContextManager &context);
        ~MenuScene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void setColor(irr::video::SColor color);

        Indie::MasterInfo *getMasterInfo(void) const;
        void setMasterInfo(const Indie::MasterInfo &masterInfo);

        private:
        static const irr::core::vector2df velocities[5];
        static const std::string filepaths[5];

        ContextManager &context;
        std::vector<std::unique_ptr<Parallax>> parallax;
        std::unique_ptr<Indie::MasterInfo> masterInfo;
    };
}

#endif /* !MENUSCENE_HPP_ */
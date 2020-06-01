/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
#define GAMESCENE_HPP_

#include "ContextManager.hpp"
#include "IScene.hpp"
#include "SystemManager.hpp"
#include "Systems.h"

namespace Indie
{
    struct InitGame;

    class GameScene : public IScene
    {
    public:
        enum class MODE { SOLO, MULTI };

        GameScene(ContextManager &context);
        ~GameScene() = default;

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;

        Indie::InitGame *getInitGame(void) const;
        void setInitGame(const Indie::InitGame &initGame);

    private:
        static const std::vector<std::pair<irr::core::vector3df, Indie::Components::PlayerComponent::PLAYER_START_POSITION>> defaultPositions;
        static const std::vector<std::pair<std::string, Components::PlayerComponent::PLAYER_COLOR>> skins;

        ContextManager &context;

        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        irr::scene::ISceneManager *sceneManager;
        irr::gui::IGUIFont *font;

        Indie::EntityManager &entityManager;
        Indie::SystemManager &systemManager;
        std::unique_ptr<Indie::InitGame> initGame;
    };
}

#endif /* !GAMESCENE_HPP_ */

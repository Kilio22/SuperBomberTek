/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
#define GAMESCENE_HPP_

#include "IScene.hpp"
#include "PlayerComponent.hpp"
#include "SystemManager.hpp"

namespace Indie
{
    struct InitGame;

    class GameScene : public IScene
    {
    public:
        enum class MODE
        {
            SOLO,
            MULTI
        };

        GameScene(ContextManager &context);
        ~GameScene() = default;

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;

        InitGame *getInitGame(void) const;
        void setInitGame(const InitGame &initGame);

    private:
        enum class SKYBOX_TYPE
        {
            TOP,
            BOTTOM,
            LEFT,
            RIGHT,
            FRONT,
            BACK
        };

        static const std::vector<std::pair<irr::core::vector3df, Components::PlayerComponent::PLAYER_START_POSITION>> defaultPositions;
        static const std::vector<std::pair<std::string, Components::PlayerComponent::PLAYER_COLOR>> skins;
        static const std::unordered_map<SKYBOX_TYPE, std::string> skyboxTexturesPath;

        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        irr::scene::ISceneManager *sceneManager;
        irr::gui::IGUIFont *font;

        ContextManager &context;
        EntityManager &entityManager;
        SystemManager &systemManager;
        std::unique_ptr<InitGame> initGame;
    };
}

#endif /* !GAMESCENE_HPP_ */

/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "GameScene.hpp"
#include "Components.h"
#include "EntityBuilder.hpp"
#include "MapGenerator.hpp"
#include "Parallax.hpp"
#include "PauseScene.hpp"
#include "ServiceLocator.hpp"

using namespace Indie::Systems;

Indie::GameScene::GameScene(ContextManager &context)
    : context(context), entityManager(ServiceLocator::getInstance().get<EntityManager>()), systemManager(SystemManager::getInstance())
{
    std::srand((unsigned int)time(NULL));
    this->device = this->context.getDevice();
    this->driver = this->context.getDriver();
    this->sceneManager = this->context.getSceneManager();
    this->systemManager.addSystem<AISystem>();
    this->systemManager.addSystem<BombDropSystem>();
    this->systemManager.addSystem<BombExplosionSystem>();
    this->systemManager.addSystem<CollisionSystem>();
    this->systemManager.addSystem<InputSystem>();
    this->systemManager.addSystem<LavaSystem>();
    this->systemManager.addSystem<MeshSystem>();
    this->systemManager.addSystem<MoveSystem>();
    this->systemManager.addSystem<RenderSystem>();
    this->systemManager.addSystem<RotationSystem>();
    this->systemManager.addSystem<TimerStopSystem>();
    this->systemManager.addSystem<TimerTickSystem>();
    this->systemManager.addSystem<VelocitySystem>();
}

// return false si un load merde.
void Indie::GameScene::init()
{
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(1);
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();
    irr::scene::ICameraSceneNode *camera = sceneManager->addCameraSceneNodeFPS();
    Indie::MapGenerator mapGenerator(entityBuilder, irr::core::vector2di(15, 15), MAP_TYPE::DEFAULT, THEME::STONE);

    camera->setPosition(irr::core::vector3df(irr::f32(138.577), irr::f32(230.299), irr::f32(47.7832)));
    camera->setRotation(irr::core::vector3df(irr::f32(41.553), irr::f32(359.176), irr::f32(-90)));
    camera->setTarget(irr::core::vector3df(irr::f32(138.593), irr::f32(-33.5216), irr::f32(130.061)));

    driver->setFog(irr::video::SColor(10, 255, 255, 255), irr::video::EFT_FOG_LINEAR, 200.0f, 2000.0f, 0.005f, false, false);
    sceneManager->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.1f, 0.1f, 0.1f, 0.0f), 700.0f);
    sceneManager->addLightSceneNode(0, irr::core::vector3df(150, 100, 150), irr::video::SColorf(1.0f, 1.0f, 1.0f, 0.5f), 700.0f);
    sceneManager->addSkyBoxSceneNode(driver->getTexture("../ressources/skybox/skybox_top.png"),
        driver->getTexture("../ressources/skybox/skybox_bottom.png"), driver->getTexture("../ressources/skybox/skybox_left.png"),
        driver->getTexture("../ressources/skybox/skybox_right.png"), driver->getTexture("../ressources/skybox/skybox_front.png"),
        driver->getTexture("../ressources/skybox/skybox_back.png"));

    mapGenerator.generate(entityManager, entityBuilder);
    entityBuilder.createPlayer(irr::core::vector3df(20, 20, 20), "../ressources/animated_mesh/character/character_idle.b3d",
        "../ressources/textures/character/blue1.png",
        { { irr::KEY_UP, Indie::Components::KEY_TYPE::UP }, { irr::KEY_DOWN, Indie::Components::KEY_TYPE::DOWN },
            { irr::KEY_RIGHT, Indie::Components::KEY_TYPE::RIGHT }, { irr::KEY_LEFT, Indie::Components::KEY_TYPE::LEFT },
            { irr::KEY_SPACE, Indie::Components::KEY_TYPE::DROP } },
        "1");
    entityBuilder.createAi(irr::core::vector3df(260, 20, 260), "../ressources/animated_mesh/character/character_idle.b3d",
        "../ressources/textures/character/yellow1.png", "2");
    entityBuilder.createAi(irr::core::vector3df(260, 20, 20), "../ressources/animated_mesh/character/character_idle.b3d",
        "../ressources/textures/character/green1.png", "3");
    entityBuilder.createAi(irr::core::vector3df(20, 20, 260), "../ressources/animated_mesh/character/character_idle.b3d",
        "../ressources/textures/character/red1.png", "4");

    device->getCursorControl()->setVisible(false);
}

// return false si un load merde.
void Indie::GameScene::reset()
{
    ServiceLocator::getInstance().get<EntityManager>().reset();
    // vos reset de valeurs et les free etc.
    this->init();
}

// LOOP ORDER:
// beginScene -> events -> update -> renderPre3D -> render3D -> renderPost3D -> endScene
void Indie::GameScene::update(irr::f32 deltaTime)
{
    this->entityManager.cleanup();
    this->systemManager.getSystem<TimerTickSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<InputSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<MoveSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<AISystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<VelocitySystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<BombDropSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<BombExplosionSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<LavaSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<TimerStopSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<RotationSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<CollisionSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<MeshSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<RenderSystem>()->onUpdate(deltaTime, entityManager);
    if (EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::PauseScene>();
    }
}

void Indie::GameScene::renderPre3D() {}

void Indie::GameScene::renderPost3D() {}

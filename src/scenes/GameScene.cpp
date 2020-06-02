/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "GameScene.hpp"
#include "Components.h"
#include "EntityBuilder.hpp"
#include "InitGame.hpp"
#include "MapGenerator.hpp"
#include "Parallax.hpp"
#include "PauseScene.hpp"
#include "ServiceLocator.hpp"
#include <sstream>

using namespace Indie::Systems;

const std::vector<std::pair<irr::core::vector3df, Indie::Components::PlayerComponent::PLAYER_START_POSITION>> Indie::GameScene::defaultPositions
    = { { { 20, 20, 20 }, Indie::Components::PlayerComponent::PLAYER_START_POSITION::DOWN_LEFT },
          { { 220, 20, 20 }, Indie::Components::PlayerComponent::PLAYER_START_POSITION::DOWN_RIGHT },
          { { 220, 20, 220 }, Indie::Components::PlayerComponent::PLAYER_START_POSITION::TOP_RIGHT },
          { { 20, 20, 220 }, Indie::Components::PlayerComponent::PLAYER_START_POSITION::TOP_LEFT } };

const std::vector<std::pair<std::string, Indie::Components::PlayerComponent::PLAYER_COLOR>> Indie::GameScene::skins
    = { { "../ressources/textures/character/blue1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE },
          { "../ressources/textures/character/blue3.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE },
          { "../ressources/textures/character/generic1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC },
          { "../ressources/textures/character/generic3.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC },
          { "../ressources/textures/character/green1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN },
          { "../ressources/textures/character/green3.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN },
          { "../ressources/textures/character/red1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED },
          { "../ressources/textures/character/red3.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED },
          { "../ressources/textures/character/yellow1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW },
          { "../ressources/textures/character/yellow3.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW },
          { "../ressources/textures/character/purple1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE },
          { "../ressources/textures/character/purple3.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE } };

Indie::GameScene::GameScene(ContextManager &context)
    : context(context)
    , animator(nullptr)
    , entityManager(ServiceLocator::getInstance().get<EntityManager>())
    , systemManager(SystemManager::getInstance())
    , initGame(std::make_unique<InitGame>())
// , target(138.0f, 224.0f, 379.f)
// , rotation(10.f, 0, 0.f)
{
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
    this->systemManager.addSystem<PathFinderSystem>();
    this->systemManager.addSystem<PlayerSystem>();
    this->systemManager.addSystem<RenderSystem>();
    this->systemManager.addSystem<RotationSystem>();
    this->systemManager.addSystem<TimerStopSystem>();
    this->systemManager.addSystem<TimerTickSystem>();
    this->systemManager.addSystem<VelocitySystem>();
    this->systemManager.addSystem<ShakeSystem>();
}

void Indie::GameScene::init()
{
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(1);
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();
    irr::scene::ICameraSceneNode *camera = sceneManager->addCameraSceneNode();
    Indie::MapGenerator mapGenerator(
        entityBuilder, irr::core::vector2di(15, 13), this->initGame->mapType, this->initGame->mapTheme, this->initGame->mapPath);
    int idx = 1;

    this->animator = nullptr;
    // camera->getTargetAndRotationBinding()
    camera->bindTargetAndRotation(true);
    camera->setPosition(irr::core::vector3df(138.577f, 280.f, 65.f));
    camera->setTarget(irr::core::vector3df(138.593f, 280.f, 121.f));
    camera->setFOV(1000);
    this->camera = camera;

    driver->setFog(irr::video::SColor(10, 255, 255, 255), irr::video::EFT_FOG_LINEAR, 200.0f, 2000.0f, 0.005f, false, false);
    sceneManager->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.1f, 0.1f, 0.1f, 0.0f), 700.0f);
    sceneManager->addLightSceneNode(0, irr::core::vector3df(150, 100, 130), irr::video::SColorf(1.0f, 1.0f, 1.0f, 0.5f), 700.0f);
    sceneManager->addSkyBoxSceneNode(driver->getTexture("../ressources/skybox/skybox_top.png"),
        driver->getTexture("../ressources/skybox/skybox_bottom.png"), driver->getTexture("../ressources/skybox/skybox_left.png"),
        driver->getTexture("../ressources/skybox/skybox_right.png"), driver->getTexture("../ressources/skybox/skybox_front.png"),
        driver->getTexture("../ressources/skybox/skybox_back.png"));

    this->font = this->context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    for (auto player : this->initGame->playersParams) {
        entityBuilder.createPlayer(this->defaultPositions.at(idx - 1).first, "../ressources/animated_mesh/character/character_idle.b3d",
            player.playerTexture, player.playerKeys, std::to_string(idx), player.playerColor, this->defaultPositions.at(idx - 1).second);
        idx++;
    }
    for (int i = 0; i < this->initGame->nbAi && i < 2; i++) {
        int randomSkinIdx = std::rand() % this->skins.size();

        entityBuilder.createAi(this->defaultPositions.at(idx - 1).first, "../ressources/animated_mesh/character/character_idle.b3d",
            this->skins.at(randomSkinIdx).first, std::to_string(idx), this->skins.at(randomSkinIdx).second,
            this->defaultPositions.at(idx - 1).second);
        idx++;
    }
    mapGenerator.generate(entityManager, entityBuilder);

    // faudra virer toussa quand les menu seront fonctionnels
    entityBuilder.createPlayer(this->defaultPositions[0].first, "../ressources/animated_mesh/character/character_idle.b3d",
        "../ressources/textures/character/blue1.png",
        { { irr::KEY_UP, Indie::Components::KEY_TYPE::UP }, { irr::KEY_DOWN, Indie::Components::KEY_TYPE::DOWN },
            { irr::KEY_RIGHT, Indie::Components::KEY_TYPE::RIGHT }, { irr::KEY_LEFT, Indie::Components::KEY_TYPE::LEFT },
            { irr::KEY_SPACE, Indie::Components::KEY_TYPE::DROP } },
        "1", Components::PlayerComponent::PLAYER_COLOR::BLUE, this->defaultPositions[0].second);
    entityBuilder.createAi(this->defaultPositions[1].first, "../ressources/animated_mesh/character/character_idle.b3d",
        "../ressources/textures/character/yellow1.png", "2", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW,
        this->defaultPositions[1].second);
    entityBuilder.createAi(this->defaultPositions[2].first, "../ressources/animated_mesh/character/character_idle.b3d",
        "../ressources/textures/character/green1.png", "3", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN,
        this->defaultPositions[2].second);
    entityBuilder.createAi(this->defaultPositions[3].first, "../ressources/animated_mesh/character/character_idle.b3d",
        "../ressources/textures/character/red1.png", "4", Indie::Components::PlayerComponent::PLAYER_COLOR::RED, this->defaultPositions[3].second);

    entityBuilder.createShake();

    device->getCursorControl()->setVisible(false);
}

void Indie::GameScene::reset()
{
    this->init();
}

// LOOP ORDER:
// beginScene -> events -> update -> renderPre3D -> render3D -> renderPost3D -> endScene
void Indie::GameScene::update(irr::f32 deltaTime)
{
    irr::core::array<irr::core::vector3df> pointList = {};
    this->entityManager.cleanup();
    this->systemManager.getSystem<TimerTickSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<LavaSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<InputSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<MoveSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<AISystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<PathFinderSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<VelocitySystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<BombDropSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<BombExplosionSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<RotationSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<CollisionSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<PlayerSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<TimerStopSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<MeshSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<ShakeSystem>()->onUpdate(deltaTime, entityManager);
    this->systemManager.getSystem<RenderSystem>()->onUpdate(deltaTime, entityManager);
    if (EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        for (auto entity : this->entityManager.each<RenderComponent>()) {
            entity->getComponent<RenderComponent>()->getMesh()->setAnimationSpeed(0.f);
        }
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::PauseScene>();
    }
}

void Indie::GameScene::renderPre3D() {}

void Indie::GameScene::renderPost3D()
{
    std::stringstream ss;
    int i = 20;
    int n = 0;
    std::vector<irr::video::SColor> colors = { { 200, 255, 0, 0 }, { 200, 0, 255, 0 }, { 200, 0, 0, 255 }, { 200, 255, 255, 0 }, { 200, 255, 0, 255 },
        { 200, 192, 192, 192 } }; ///< Codé en dur mdr mais il faudrait une couleur dans les personnages.

    for (auto entity : entityManager.each<PlayerComponent>()) {
        auto player = entity->getComponent<PlayerComponent>();

        ss << player->getName() << std::endl;
        ss << "  Bombs: " << player->getCurrentBombNb() << " / " << player->getMaxBombNb() << std::endl;
        ss << "  Bomb range: " << player->getBombsRange() << std::endl;
        ss << "  Speed: " << std::string(player->getVelocityLevel(), '>') << std::endl;
        ss << "  Xp: " << player->getXpCount() << " (lvl " << player->getLevelCount() << ")" << std::endl;
        n = (int)player->getPlayerColor();
        if (player->isDead() == true)
            n = (int)PlayerComponent::PLAYER_COLOR::GENERIC;
        font->draw(irr::core::stringw(ss.str().c_str()), irr::core::rect<irr::s32>(20, i, 0, 0), colors[n]);
        ss.str("");
        i += 160;
    }
}

Indie::InitGame *Indie::GameScene::getInitGame(void) const
{
    return this->initGame.get();
}

void Indie::GameScene::setInitGame(const Indie::InitGame &initGame)
{
    this->initGame = std::make_unique<Indie::InitGame>(initGame);
}
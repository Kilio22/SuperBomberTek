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
          { { 260, 20, 20 }, Indie::Components::PlayerComponent::PLAYER_START_POSITION::DOWN_RIGHT },
          { { 260, 20, 220 }, Indie::Components::PlayerComponent::PLAYER_START_POSITION::TOP_RIGHT },
          { { 20, 20, 220 }, Indie::Components::PlayerComponent::PLAYER_START_POSITION::TOP_LEFT } };

const std::vector<std::pair<std::string, Indie::Components::PlayerComponent::PLAYER_COLOR>> Indie::GameScene::skins
    = { { "../ressources/textures/character/blue1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE },
          { "../ressources/textures/character/blue2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE },
          { "../ressources/textures/character/generic1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC },
          { "../ressources/textures/character/generic2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC },
          { "../ressources/textures/character/green1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN },
          { "../ressources/textures/character/green2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN },
          { "../ressources/textures/character/red1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED },
          { "../ressources/textures/character/red2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED },
          { "../ressources/textures/character/yellow1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW },
          { "../ressources/textures/character/yellow2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW },
          { "../ressources/textures/character/purple1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE },
          { "../ressources/textures/character/purple2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE } };

Indie::GameScene::GameScene(ContextManager &context)
    : context(context)
    , entityManager(ServiceLocator::getInstance().get<EntityManager>())
    , systemManager(SystemManager::getInstance())
    , initGame(std::make_unique<InitGame>())
{
    this->device = this->context.getDevice();
    this->driver = this->context.getDriver();
    this->sceneManager = this->context.getSceneManager();
    this->systemManager.addSystem<AISystem>();
    this->systemManager.addSystem<BombDropSystem>();
    this->systemManager.addSystem<BombExplosionSystem>();
    this->systemManager.addSystem<CollisionSystem>();
    this->systemManager.addSystem<GameSystem>();
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
    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();
    irr::scene::ICameraSceneNode *camera = sceneManager->addCameraSceneNode();
    MapGenerator mapGenerator(entityBuilder, { 15, 13 }, this->initGame->mapType, this->initGame->mapTheme, this->initGame->mapPath);
    std::vector<std::string> usedTextures;
    int idx = 0;
    int n = 0;

    ServiceLocator::getInstance().get<MusicManager>().setMusic(1);
    camera->bindTargetAndRotation(true);
    camera->setPosition(irr::core::vector3df(138.577f, 280.f, 65.f));
    camera->setTarget(irr::core::vector3df(138.593f, 280.f, 121.f));
    camera->setFOV(1000);

    driver->setFog(irr::video::SColor(10, 255, 255, 255), irr::video::EFT_FOG_LINEAR, 200.0f, 2000.0f, 0.005f, false, false);
    sceneManager->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.1f, 0.1f, 0.1f, 0.0f), 700.0f);
    sceneManager->addLightSceneNode(0, irr::core::vector3df(150, 100, 130), irr::video::SColorf(1.0f, 1.0f, 1.0f, 0.5f), 700.0f);
    sceneManager->addSkyBoxSceneNode(driver->getTexture("../ressources/skybox/skybox_top.png"),
        driver->getTexture("../ressources/skybox/skybox_bottom.png"), driver->getTexture("../ressources/skybox/skybox_left.png"),
        driver->getTexture("../ressources/skybox/skybox_right.png"), driver->getTexture("../ressources/skybox/skybox_front.png"),
        driver->getTexture("../ressources/skybox/skybox_back.png"));

    this->font = this->context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");

    for (auto player : this->initGame->playersParams) {
        entityBuilder.createPlayer(this->defaultPositions.at(idx).first, "../ressources/animated_mesh/character/character_idle.b3d",
            player.playerTexture, player.playerKeys, "Player " + std::to_string(++n), player.playerColor, this->defaultPositions.at(idx).second);
        usedTextures.push_back(player.playerTexture);
        idx++;
    }
    n = 0;
    for (int i = 0; i < this->initGame->nbAi; i++) {
        int randomSkinIdx = std::rand() % this->skins.size();

        if (std::find(usedTextures.begin(), usedTextures.end(), this->skins.at(randomSkinIdx).first) != usedTextures.end()) {
            i--;
            continue;
        }
        entityBuilder.createAi(this->defaultPositions.at(idx).first, "../ressources/animated_mesh/character/character_idle.b3d",
            this->skins.at(randomSkinIdx).first, "IA " + std::to_string(++n), this->skins.at(randomSkinIdx).second,
            this->defaultPositions.at(idx).second);
        usedTextures.push_back(this->skins.at(randomSkinIdx).first);
        idx++;
    }
    mapGenerator.generate(entityManager, entityBuilder);

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
    this->systemManager.getSystem<GameSystem>()->onUpdate(deltaTime, entityManager);
}

void Indie::GameScene::renderPre3D() {}

void Indie::GameScene::renderPost3D()
{
    const std::vector<irr::video::SColor> colors
        = { { 200, 255, 0, 0 }, { 200, 0, 255, 0 }, { 200, 0, 0, 255 }, { 200, 255, 255, 0 }, { 200, 255, 0, 255 }, { 200, 192, 192, 192 } };
    const std::vector<irr::core::vector2di> positions = { { 20, 20 }, { 1050, 20 }, { 20, 550 }, { 1050, 550 } };
    std::stringstream ss;
    int n = 0;

    for (auto entity : entityManager.each<PlayerComponent>()) {
        auto player = entity->getComponent<PlayerComponent>();

        ss << player->getName();
        if (player->getWallPass() == true)
            ss << "  (WP)";
        ss << std::endl;
        ss << "  Bombs: " << player->getCurrentBombNb() << " / " << player->getMaxBombNb() << std::endl;
        ss << "  Bomb range: " << player->getBombsRange() << std::endl;
        ss << "  Speed: " << std::string(player->getVelocityLevel(), '>') << std::endl;
        ss << "  Score: " << player->getScore() << std::endl;
        n = (int)player->getPlayerColor();
        if (player->isDead() == true)
            n = (int)PlayerComponent::PLAYER_COLOR::GENERIC;
        auto [x, y] = positions[(int)player->getStartPosition()];
        font->draw(irr::core::stringw(ss.str().c_str()), irr::core::rect<irr::s32>(x, y, 0, 0), colors[n]);
        ss.str("");
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
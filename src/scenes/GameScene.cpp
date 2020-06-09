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
#include "MusicManager.hpp"
#include "Parallax.hpp"
#include "PauseScene.hpp"
#include "ServiceLocator.hpp"
#include "SoloScene.hpp"
#include "EndScene.hpp"
#include "Systems.h"
#include <sstream>

using namespace Indie::Systems;
using namespace Indie::Components;

const std::vector<std::pair<irr::core::vector3df, PlayerComponent::PLAYER_START_POSITION>> Indie::GameScene::defaultPositions = {
    { { 20, 20, 20 }, PlayerComponent::PLAYER_START_POSITION::DOWN_LEFT }, { { 260, 20, 20 }, PlayerComponent::PLAYER_START_POSITION::DOWN_RIGHT },
    { { 260, 20, 220 }, PlayerComponent::PLAYER_START_POSITION::TOP_RIGHT }, { { 20, 20, 220 }, PlayerComponent::PLAYER_START_POSITION::TOP_LEFT }
};

const std::vector<std::pair<std::string, PlayerComponent::PLAYER_COLOR>> Indie::GameScene::skins
    = { { "../ressources/textures/character/Gris.png", PlayerComponent::PLAYER_COLOR::GENERIC },
          { "../ressources/textures/character/Bleu.png", PlayerComponent::PLAYER_COLOR::BLUE },
          { "../ressources/textures/character/Rouge.png", PlayerComponent::PLAYER_COLOR::RED },
          { "../ressources/textures/character/Vert.png", PlayerComponent::PLAYER_COLOR::GREEN },
          { "../ressources/textures/character/Violet.png", PlayerComponent::PLAYER_COLOR::PURPLE },
          { "../ressources/textures/character/Jaune.png", PlayerComponent::PLAYER_COLOR::YELLOW },
          { "../ressources/textures/character/Gris+.png", PlayerComponent::PLAYER_COLOR::GENERIC },
          { "../ressources/textures/character/Bleu+.png", PlayerComponent::PLAYER_COLOR::BLUE },
          { "../ressources/textures/character/Rouge+.png", PlayerComponent::PLAYER_COLOR::RED },
          { "../ressources/textures/character/Vert+.png", PlayerComponent::PLAYER_COLOR::GREEN },
          { "../ressources/textures/character/Violet+.png", PlayerComponent::PLAYER_COLOR::PURPLE },
          { "../ressources/textures/character/Jaune+.png", PlayerComponent::PLAYER_COLOR::YELLOW } };

const std::unordered_map<Indie::GameScene::SKYBOX_TYPE, std::string> Indie::GameScene::skyboxTexturesPath
    = { { Indie::GameScene::SKYBOX_TYPE::TOP, "../ressources/skybox/skybox_top.png" },
          { Indie::GameScene::SKYBOX_TYPE::BOTTOM, "../ressources/skybox/skybox_bottom.png" },
          { Indie::GameScene::SKYBOX_TYPE::LEFT, "../ressources/skybox/skybox_left.png" },
          { Indie::GameScene::SKYBOX_TYPE::RIGHT, "../ressources/skybox/skybox_right.png" },
          { Indie::GameScene::SKYBOX_TYPE::FRONT, "../ressources/skybox/skybox_front.png" },
          { Indie::GameScene::SKYBOX_TYPE::BACK, "../ressources/skybox/skybox_back.png" } };

Indie::GameScene::GameScene(ContextManager &context)
    : context(context)
    , entityManager(ServiceLocator::getInstance().get<EntityManager>())
    , systemManager(SystemManager::getInstance())
    , initGame(std::make_unique<InitGame>())
{
    this->device = this->context.getDevice();
    this->driver = this->context.getDriver();
    this->sceneManager = this->context.getSceneManager();
    this->font = this->context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    if (this->font == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/Banschrift.xml\"");
    }
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
    if (camera == nullptr) {
        throw Indie::Exceptions::SceneManagerException(ERROR_STR, "Cannot add camera scene node.");
    }
    camera->bindTargetAndRotation(true);
    camera->setPosition(irr::core::vector3df(138.577f, 280.f, 65.f));
    camera->setTarget(irr::core::vector3df(138.593f, 280.f, 121.f));
    camera->setFOV(1000);

    driver->setFog(irr::video::SColor(10, 255, 255, 255), irr::video::EFT_FOG_LINEAR, 200.0f, 2000.0f, 0.005f, false, false);
    sceneManager->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.1f, 0.1f, 0.1f, 0.0f), 700.0f);
    sceneManager->addLightSceneNode(0, irr::core::vector3df(150, 100, 130), irr::video::SColorf(1.0f, 1.0f, 1.0f, 0.5f), 700.0f);
    std::unordered_map<Indie::GameScene::SKYBOX_TYPE, irr::video::ITexture *> skyboxTextures;

    for (const auto &value : this->skyboxTexturesPath) {
        irr::video::ITexture *newTexture = driver->getTexture(value.second.c_str());

        if (newTexture == nullptr) {
            throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot found file: " + value.second);
        }
        skyboxTextures.insert({ value.first, newTexture });
    }
    sceneManager->addSkyBoxSceneNode(skyboxTextures.at(Indie::GameScene::SKYBOX_TYPE::TOP), skyboxTextures.at(Indie::GameScene::SKYBOX_TYPE::BOTTOM),
        skyboxTextures.at(Indie::GameScene::SKYBOX_TYPE::LEFT), skyboxTextures.at(Indie::GameScene::SKYBOX_TYPE::RIGHT),
        skyboxTextures.at(Indie::GameScene::SKYBOX_TYPE::FRONT), skyboxTextures.at(Indie::GameScene::SKYBOX_TYPE::BACK));

    for (auto player : this->initGame->playersParams) {
        entityBuilder.createPlayer(this->defaultPositions.at(idx).first, "../ressources/animated_mesh/character/character_idle.b3d",
            player.playerTexture, player.playerKeys, "Joueur " + std::to_string(++n), player.playerColor, this->defaultPositions.at(idx).second);
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
    entityManager.createUniqueEntity<GameComponent>((irr::f32)this->initGame->timeLimit);
}

void Indie::GameScene::reset()
{
    this->init();
}

// LOOP ORDER:
// beginScene -> events -> update -> renderPre3D -> render3D -> renderPost3D -> endScene
void Indie::GameScene::update(irr::f32 deltaTime)
{
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
    auto gameComponent = this->entityManager.getUniqueEntity<GameComponent>()->getComponent<GameComponent>();
    int timer = (int)gameComponent->getTimeToEnd();
    std::string timeAmmount = std::to_string(timer / 60) + ":";

    if (timer % 60 < 10)
        timeAmmount += "0";
    timeAmmount += std::to_string(timer % 60);
    this->font->draw(timeAmmount.c_str(), irr::core::rect<irr::s32>(1280 / 2, 1, 0, 0), irr::video::SColor(255, 255, 255, 255));
}

Indie::InitGame *Indie::GameScene::getInitGame(void) const
{
    return this->initGame.get();
}

void Indie::GameScene::setInitGame(const Indie::InitGame &initGame)
{
    std::vector<std::string> names;

    this->initGame = std::make_unique<Indie::InitGame>(initGame);
    for (const auto &it : this->initGame->playersParams)
        names.push_back(ServiceLocator::getInstance().get<SceneManager>().getScene<SoloScene>()->getFileName(it.playerTexture));
    ServiceLocator::getInstance().get<SceneManager>().getScene<EndScene>()->setPlayerNames(names);
}
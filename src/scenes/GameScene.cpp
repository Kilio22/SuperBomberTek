/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#define MAP_SIZE 15

#include "GameScene.hpp"
#include "ServiceLocator.hpp"

// return false si un load merde.
bool Indie::GameScene::init(ContextManager &_context)
{
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(1);
    device = _context.getDevice();
    driver = _context.getDriver();
    sceneManager = _context.getSceneManager();

    device->setEventReceiver(&EventHandler::getInstance());

    irr::scene::ICameraSceneNode *camera = sceneManager->addCameraSceneNodeFPS();
    camera->setPosition(irr::core::vector3df(irr::f32(139.371), irr::f32(170.129), irr::f32(-24.6459)));
	camera->setRotation(irr::core::vector3df(irr::f32(41.553), irr::f32(359.176), irr::f32(-90)));
    camera->setTarget(irr::core::vector3df(irr::f32(0), irr::f32(0), irr::f32(0)));

    // Lumière et brouillard quand on s'éloigne
    driver->setFog(irr::video::SColor(10, 255, 255, 255), irr::video::EFT_FOG_LINEAR, 200.0f, 2000.0f, 0.005f, false, false);
    //sceneManager->setAmbientLight(irr::video::SColorf(0.2,0.2,0.2,1));
    //J'ai foutu la camera en parent, du coup ça éclaire autours de la cam.
    sceneManager->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.1f, 0.1f, 0.1f, 0.0f), 700.0f);
    sceneManager->addLightSceneNode(0, irr::core::vector3df(150, 100, 150), irr::video::SColorf(1.0f, 1.0f, 1.0f, 0.5f), 700.0f);

    irr::scene::ISceneNode *skybox = sceneManager->addSkyBoxSceneNode(
        driver->getTexture("../ressources/skybox/skybox_top.png"),
        driver->getTexture("../ressources/skybox/skybox_bottom.png"),
        driver->getTexture("../ressources/skybox/skybox_left.png"),
        driver->getTexture("../ressources/skybox/skybox_right.png"),
        driver->getTexture("../ressources/skybox/skybox_front.png"),
        driver->getTexture("../ressources/skybox/skybox_back.png"));

    auto &mapGenerator = ServiceLocator::getInstance().get<Indie::MapGenerator>();
    mapGenerator.generate();

    auto &entityBuilder = ServiceLocator::getInstance().get<EntityBuilder>();
    entityBuilder.createPlayer(irr::core::vector3df(20, 20, 20), "../ressources/static_mesh/character/red.obj", "../ressources/textures/character/red.png", {{irr::KEY_UP, Indie::Components::KEY_TYPE::UP}, {irr::KEY_DOWN, Indie::Components::KEY_TYPE::DOWN}, {irr::KEY_RIGHT, Indie::Components::KEY_TYPE::RIGHT}, {irr::KEY_LEFT, Indie::Components::KEY_TYPE::LEFT}, {irr::KEY_SPACE, Indie::Components::KEY_TYPE::DROP}});

    entityBuilder.createAi(irr::core::vector3df(260, 20, 20), "../ressources/static_mesh/character/red.obj", "../ressources/textures/character/red.png");

    device->getCursorControl()->setVisible(false);

    this->context = &_context;
    return (true);
}

// return false si un load merde.
bool Indie::GameScene::reset(ContextManager &_context)
{
    // vos reset de valeurs et les free etc.
    return (init(_context));
}

// LOOP ORDER:
// beginScene -> events -> update -> renderPre3D -> render3D -> renderPost3D -> endScene
void Indie::GameScene::update(irr::f32 deltaTime)
{
    inputSystem.onUpdate(deltaTime, entityManager);
    moveSystem.onUpdate(deltaTime, entityManager);
    velocitySystem.onUpdate(deltaTime, entityManager);
    rotationSystem.onUpdate(deltaTime, entityManager);
    bombSystem.onUpdate(deltaTime, entityManager);
    collisionSystem.onUpdate(deltaTime, entityManager);
    meshSystem.onUpdate(deltaTime, entityManager);
    renderSystem.onUpdate(deltaTime, entityManager);
}

void Indie::GameScene::renderPre3D() {}

void Indie::GameScene::renderPost3D() {}
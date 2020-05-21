/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "Scenes/GameScene.hpp"

// return false si un load merde.
bool GameScene::init(ContextManager &_context)
{
    MusicManager::setMusic(1);
    device = _context.getDevice();
    driver = _context.getDriver();
    sceneManager = _context.getSceneManager();

    device->setEventReceiver(&Indie::EventHandler::getInstance());
    irr::SKeyMap keyMap[4];                             // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_Z;
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_Q;
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;

    irr::scene::ICameraSceneNode *camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.1f, -1, keyMap, 4);
    camera->setPosition(irr::core::vector3df(irr::f32(139.371), irr::f32(170.129), irr::f32(-24.6459)));
	camera->setRotation(irr::core::vector3df(irr::f32(41.553), irr::f32(359.176), irr::f32(-90)));
    camera->setTarget(irr::core::vector3df(irr::f32(0), irr::f32(0), irr::f32(0)));

    irr::f32 x = 0;
    irr::f32 y = 0;

    // Lumière et brouillard quand on s'éloigne
    driver->setFog(irr::video::SColor(10, 255, 255, 255), irr::video::EFT_FOG_LINEAR, 200.0f, 2000.0f, 0.005f, false, false);
    //sceneManager->setAmbientLight(irr::video::SColorf(0.2,0.2,0.2,1));
    //J'ai foutu la camera en parent, du coup ça éclaire autours de la cam.
    sceneManager->addLightSceneNode (camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.1f, 0.1f, 0.1f, 0.0f), 700.0f);
    sceneManager->addLightSceneNode (0, irr::core::vector3df(150, 100, 150), irr::video::SColorf(1.0f, 1.0f, 1.0f, 0.5f), 700.0f);

    irr::scene::ISceneNode* skybox = sceneManager->addSkyBoxSceneNode(
        driver->getTexture("../ressources/skybox/skybox_top.png"),
        driver->getTexture("../ressources/skybox/skybox_bottom.png"),
        driver->getTexture("../ressources/skybox/skybox_left.png"),
        driver->getTexture("../ressources/skybox/skybox_right.png"),
        driver->getTexture("../ressources/skybox/skybox_front.png"),
        driver->getTexture("../ressources/skybox/skybox_back.png"));

    for (size_t i = 0; i < 15; i++) {
        for (size_t j = 0; j < 15; j++) {
            Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(x, 0, y), "../ressources/static_mesh/map_dirt/ground.obj", "../ressources/static_mesh/map_dirt/ground.png", _context);
            x += 20;
        }
        x = 0;
        y += 20;
    }

    Indie::MapGenerator generator(Indie::MapGenerator::DEFAULT);

    std::vector<std::vector<int>> map = generator.getMap();
    for (size_t i = 0; i < 15; i++) {
        for (size_t j = 0; j < 15; j++) {
            if (map[i][j] == -1)
                Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(20 * i, 20, 20 * j), "../ressources/static_mesh/map_dirt/wall_side.obj", "../ressources/static_mesh/map_dirt/wall_side.png", _context);
            else if (map[i][j] == 1)
                Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(20 * i, 20, 20 * j), "../ressources/static_mesh/map_dirt/box.obj", "../ressources/static_mesh/map_dirt/box.png", _context);
            else if (map[i][j] == 2)
                Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(20 * i, 20, 20 * j), "../ressources/static_mesh/map_dirt/wall_middle.obj", "../ressources/static_mesh/map_dirt/wall_middle.png", _context);
            else if (map[i][j] == 3)
                Indie::EntityBuilder::createGround(entityManager, irr::core::vector3df(20 * i, 20, 20 * j), "../ressources/static_mesh/map_stone/ground.obj", "../ressources/static_mesh/map_stone/ground.png", _context);
        }
    }
    Indie::EntityBuilder::createPlayer(entityManager, irr::core::vector3df(20, 20, 20), "../ressources/static_mesh/character/red.obj", "../ressources/textures/character/red.png", _context, {{irr::KEY_UP, Indie::Components::UP}, {irr::KEY_DOWN, Indie::Components::DOWN}, {irr::KEY_RIGHT, Indie::Components::RIGHT}, {irr::KEY_LEFT, Indie::Components::LEFT}});
    device->getCursorControl()->setVisible(false);

    this->context = &_context;
    return (true);
}

// return false si un load merde.
bool GameScene::reset(ContextManager &_context)
{
    // vos reset de valeurs et les free etc.
    return (init(_context));
}


// LOOP ORDER:
// beginScene -> events -> update -> renderPre3D -> render3D -> renderPost3D -> endScene
void GameScene::update()
{
    // FAUT QU'ON VOIT POUR LES TICKS AVANT QUE CE SOIT LE BORDEL A AJOUTER.
    inputSystem.onUpdate(0, entityManager);
    moveSystem.onUpdate(0, entityManager);
    velocitySystem.onUpdate(0, entityManager);
    rotationSystem.onUpdate(0, entityManager);
    meshSystem.onUpdate(0, entityManager);
    renderSystem.onUpdate(0, entityManager);
}

void GameScene::renderPre3D() {}

void GameScene::renderPost3D() {}
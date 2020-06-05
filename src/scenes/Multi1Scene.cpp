
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Multi1Scene
*/

#include "Multi1Scene.hpp"
#include "ServiceLocator.hpp"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "InitGame.hpp"
#include "PauseScene.hpp"
#include "IntroScene.hpp"
#include "Multi2Scene.hpp"
#include <filesystem>

static std::string getFileName(std::string const &filepath)
{
    std::string filename(filepath.c_str());
    const size_t last_slash_id = filename.find_last_of("\\/");

    if (std::string::npos != last_slash_id)
        filename.erase(0, last_slash_id + 1);
    const size_t period_id = filename.rfind('.');
    if (std::string::npos != period_id)
        filename.erase(period_id);
    return (filename);
}

void Indie::Multi1Scene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

// Il faut changer les valeurs ici dans les constructeurs des selecteurs quand on aura le nombre de map max etc
Indie::Multi1Scene::Multi1Scene(Indie::ContextManager &context)
    : context(context)
    , selector(2, 6, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , themeSelector(2, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , mapSelector(1, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , iaSelector(3, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , timeSelector(61, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{
    pUpsEnabled = true;
    modelRotation = 0;
    nbAi = 0;
    timeLimit = 18 * 5;
    timeSelector.setPos(18, 0);
    mapPaths.push_back("Default");
    mapPaths.push_back("Random");
    for (const auto & entry : std::filesystem::directory_iterator("../ressources/maps/"))
        mapPaths.push_back(entry.path().u8string());
    mapSelector.setSize(int(mapPaths.size()), 1);
}

Indie::Multi1Scene::~Multi1Scene()
{}

void Indie::Multi1Scene::init() // Check all paths & init values
{
    // TODO : XP BAR
    // TODO : SCORE
    /* ================================================================== */
    // 3D INIT
    /* ================================================================== */
    camera = context.getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0, 0, -75), irr::core::vector3df(0, 0, 0), -1, true);
    camera->setTarget(irr::core::vector3df(-52, 0, 0));
    context.getSceneManager()->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.2f, 0.2f, 0.3f, 0.0f), 400.0f);
    theme1 = context.getSceneManager()->addAnimatedMeshSceneNode(context.getSceneManager()->getMesh("../ressources/static_mesh/map1model.mc.ply"));
    theme1->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    theme1->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
    theme1->setVisible(false);
    theme1->setScale(irr::core::vector3df(1.4f, 1.4f, 1.4f));
    theme2 = context.getSceneManager()->addAnimatedMeshSceneNode(context.getSceneManager()->getMesh("../ressources/static_mesh/map2model.mc.ply"));
    theme2->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    theme2->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
    theme2->setVisible(false);
    theme2->setScale(irr::core::vector3df(1.4f, 1.4f, 1.4f));
    /* ================================================================== */
    // IMAGES GET
    /* ================================================================== */
    title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi1/title.png");
    layout = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi1/Layout.png");
    whiteBg = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi1/WhiteBG.png");
    /* ================================================================== */
    // FONT GET
    /* ================================================================== */
    font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    /* ================================================================== */
    // BUTTONS CREATE
    /* ================================================================== */
    play.reset(new Button(context));
    back.reset(new Button(context));
    themeButton.reset(new Button(context));
    mapButton.reset(new Button(context));
    iaButton.reset(new Button(context));
    timeButton.reset(new Button(context));
    /* ================================================================== */
    // BUTTONS INIT
    /* ================================================================== */
    play->init(context, "../ressources/images/multi1/Suivant.png", 1, 4, POS(0,0));
    back->init(context, "../ressources/images/multi1/Retour.png", 1, 5, POS(0,0));
    mapButton->init(context, "../ressources/images/multi1/Niveau.png", 0, 0, POS(0,0));
    themeButton->init(context, "../ressources/images/multi1/Theme.png", 0, 1, POS(0,0));
    timeButton->init(context, "../ressources/images/multi1/Temps.png", 0, 2, POS(0,0));
    iaButton->init(context, "../ressources/images/multi1/IA.png", 0, 3, POS(0,0));
    /* ================================================================== */
    // CHECKBOXES CREATE
    /* ================================================================== */
    pUps.reset(new Checkbox(context));
    pUps->setStatus(pUpsEnabled);
    /* ================================================================== */
    // CHECKBOXES INIT
    /* ================================================================== */
    pUps->init("../ressources/images/multi1/Check.png", 0, 4, POS(0, 0));
    pUps->setStatus(pUpsEnabled);
    mapPath = mapPaths[mapSelector.getPos().first];
    mapTheme = (themeSelector.getPos().first == 0) ? Components::THEME::DIRT : Components::THEME::STONE;
}

void Indie::Multi1Scene::reset()
{
    context.getSceneManager()->clear();
    selector.setPos(0, 0);
    init();
}

void Indie::Multi1Scene::update(irr::f32 ticks)
{
    /* ================================================================== */
    // 3D UPDATE
    /* ================================================================== */
    theme1->setVisible(mapTheme == Components::THEME::DIRT);
    theme2->setVisible(mapTheme == Components::THEME::STONE);
    theme1->setRotation(irr::core::vector3df(0, modelRotation, 0));
    theme2->setRotation(irr::core::vector3df(0, modelRotation, 0));
    modelRotation += float(10 * ticks);
    /* ================================================================== */
    // LAYOUTS SKIP
    /* ================================================================== */
    selector.update(); // We update the main selector
    if (selector.getPos().second < 4) {
        selector.setPos(0, selector.getPos().second); // Can't move right in the first 4 selectors
    }
    if (selector.getPos().second == 5) {
        selector.setPos(1, 5); // Can't move left from the last button
    }
    /* ================================================================== */
    // UPDATE BUTTONS
    /* ================================================================== */
    themeButton->update(selector.getPos());
    mapButton->update(selector.getPos());
    iaButton->update(selector.getPos());
    timeButton->update(selector.getPos());
    play->update(selector.getPos());
    back->update(selector.getPos());
    /* ================================================================== */
    // UPDATE CHECKBOXES
    /* ================================================================== */
    pUps->update(selector.getPos());
    pUpsEnabled = pUps->getStatus();
    /* ================================================================== */
    // UPDATE SELECTORS
    /* ================================================================== */
    if (selector.getPos().first == 0 && selector.getPos().second == 0) {
        mapSelector.update();
        mapPath = mapPaths[mapSelector.getPos().first];
    }
    if (selector.getPos().first == 0 && selector.getPos().second == 1) {
        themeSelector.update();
        mapTheme = (themeSelector.getPos().first == 0) ? Components::THEME::DIRT : Components::THEME::STONE;
    }
    if (selector.getPos().first == 0 && selector.getPos().second == 2) {
        timeSelector.update();
        timeLimit = time_t(timeSelector.getPos().first * 5);
    }
    if (selector.getPos().first == 0 && selector.getPos().second == 3) {
        iaSelector.update();
        nbAi = iaSelector.getPos().first;
    }
    /* ================================================================== */
    // CLICK BUTTONS
    /* ================================================================== */
    if (play->getStatus() == Button::Status::Pressed || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_KEY_P) == true) {
        // Do stuff then go to Multi2 
        context.getSceneManager()->clear();
        mapType = (mapSelector.getPos().first == 0)
            ? Components::MAP_TYPE::DEFAULT
            : ((mapSelector.getPos().first == 1) ? Components::MAP_TYPE::RANDOM : Components::MAP_TYPE::SAVED);
        ServiceLocator::getInstance().get<SceneManager>().getScene<Multi2Scene>()->setData(nbAi, mapTheme, mapType, pUpsEnabled, mapPath, timeLimit);
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<Multi2Scene>();
        skipScene(true, true, true, true);
    }
    if (back->getStatus() == Button::Status::Pressed || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        context.getSceneManager()->clear();
        skipScene(true, true, true, true);
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<MainMenuScene>();
    }
    EventHandler::getInstance().resetKeys();
}

void Indie::Multi1Scene::renderPre3D()
{
    /* ================================================================== */
    // DISPLAY IMAGES
    /* ================================================================== */
    context.displayImage(title);
    context.displayImage(layout);
    context.displayImage(whiteBg);
}

void Indie::Multi1Scene::renderPost3D()
{
    /* ================================================================== */
    // DISPLAY BUTONS
    /* ================================================================== */
    mapButton->draw();
    themeButton->draw();
    timeButton->draw();
    iaButton->draw();
    play->draw();
    back->draw();
    /* ================================================================== */
    // DISPLAY CHECKBOXES
    /* ================================================================== */
    pUps->draw();
    /* ================================================================== */
    // DISPLAY TEXTS
    /* ================================================================== */
    std::string mPath = getFileName(mapPath);
    std::string tName = (mapTheme == Components::THEME::DIRT) ? "Garden" : "Cobblestone";
    std::string aiAmmount = std::to_string(nbAi);
    std::string timeAmmount = std::to_string((timeLimit) / 60) + ":";
    if (timeLimit % 60 < 10)
        timeAmmount += "0";
    timeAmmount += std::to_string((timeLimit) % 60);
    font->draw(mPath.c_str(), RECT(410 - (5 * int(mPath.size())), 139, 0, 0), {255, 255, 255, 255});
    font->draw(tName.c_str(), RECT(410 - (5 * int(tName.size())), 218, 0, 0), {255, 255, 255, 255});
    font->draw(timeAmmount.c_str(), RECT(410 - (5 * int(timeAmmount.size())), 300, 0, 0), {255, 255, 255, 255});
    font->draw(aiAmmount.c_str(), RECT(410 - (5 * int(aiAmmount.size())), 384, 0, 0), {255, 255, 255, 255});
}
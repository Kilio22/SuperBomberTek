
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MultiScene
*/

#include "MultiScene.hpp"
#include "GameScene.hpp"
#include "InitGame.hpp"
#include "IntroScene.hpp"
#include "MainMenuScene.hpp"
#include "MenuScene.hpp"
#include "MultiKeybindsScene.hpp"
#include "PauseScene.hpp"
#include "ServiceLocator.hpp"
#include <filesystem>

void Indie::MultiScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

const std::unordered_map<Indie::MultiScene::UI_SELECTOR_TYPE, irr::core::vector2di> Indie::MultiScene::uiSelectorsSize
    = { { Indie::MultiScene::UI_SELECTOR_TYPE::DEFAULT, { 2, 6 } }, { Indie::MultiScene::UI_SELECTOR_TYPE::THEME, { 2, 1 } },
          { Indie::MultiScene::UI_SELECTOR_TYPE::MAP, { 1, 1 } }, { Indie::MultiScene::UI_SELECTOR_TYPE::AI, { 3, 1 } },
          { Indie::MultiScene::UI_SELECTOR_TYPE::TIME, { 61, 1 } } };

// Il faut changer les valeurs ici dans les constructeurs des selecteurs quand on aura le nombre de map max etc
Indie::MultiScene::MultiScene(Indie::ContextManager &context)
    : context(context)
    , pUps(std::make_unique<Checkbox>(context))
    , initGame(std::make_unique<InitGame>())
{
    for (size_t uiSelectorType = (size_t)UI_SELECTOR_TYPE::DEFAULT; uiSelectorType < (size_t)UI_SELECTOR_TYPE::NONE; uiSelectorType++) {
        int x = this->uiSelectorsSize.at((UI_SELECTOR_TYPE)uiSelectorType).X;
        int y = this->uiSelectorsSize.at((UI_SELECTOR_TYPE)uiSelectorType).Y;

        this->uiSelectors.insert({ (UI_SELECTOR_TYPE)uiSelectorType,
            std::make_unique<UiSelector>(
                x, y, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT) });
    }
    this->modelRotation = 0;
    this->initGame->powerUp = true;
    this->initGame->nbAi = 0;
    this->initGame->timeLimit = 18 * 5;
    this->pUps->setStatus(this->initGame->powerUp);
    this->uiSelectors.at(UI_SELECTOR_TYPE::TIME)->setPos(18, 0);
    mapPaths.push_back("Default");
    mapPaths.push_back("Random");
    for (const auto &entry : std::filesystem::directory_iterator("../ressources/maps/"))
        mapPaths.push_back(entry.path().u8string());
    this->uiSelectors.at(UI_SELECTOR_TYPE::MAP)->setSize(int(mapPaths.size()), 1);
    for (size_t buttonType = (size_t)BUTTON_TYPE::THEME; buttonType < (size_t)BUTTON_TYPE::NONE; buttonType++) {
        this->buttons.insert({ (BUTTON_TYPE)buttonType, std::make_unique<Button>(context) });
    }
}

Indie::MultiScene::~MultiScene() {}

void Indie::MultiScene::init() // Check all paths & init values
{
    // TODO : XP BAR
    // 3D INIT
    irr::scene::ICameraSceneNode *camera
        = context.getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0, 0, -75), irr::core::vector3df(0, 0, 0), -1, true);
    camera->setTarget(irr::core::vector3df(-52, 0, 0));
    context.getSceneManager()->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.2f, 0.2f, 0.3f, 0.0f), 400.0f);

    this->theme1 = this->createTheme("../ressources/static_mesh/map1model.mc.ply");
    this->theme2 = this->createTheme("../ressources/static_mesh/map2model.mc.ply");
    // IMAGES GET
    this->title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi1/title.png");
    this->layout = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi1/Layout.png");
    this->whiteBg = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi1/WhiteBG.png");
    // FONT GET
    this->font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    // BUTTONS INIT
    this->buttons.at(BUTTON_TYPE::PLAY)->init(context, "../ressources/images/multi1/Suivant.png", 1, 4, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::BACK)->init(context, "../ressources/images/multi1/Retour.png", 1, 5, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::MAP)->init(context, "../ressources/images/multi1/Niveau.png", 0, 0, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::THEME)->init(context, "../ressources/images/multi1/Theme.png", 0, 1, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::TIME)->init(context, "../ressources/images/multi1/Temps.png", 0, 2, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::AI)->init(context, "../ressources/images/multi1/IA.png", 0, 3, POS(0, 0));
    // CHECKBOXES INIT
    this->pUps->init("../ressources/images/multi1/Check.png", 0, 4, POS(0, 0));
    this->pUps->setStatus(this->initGame->powerUp);
    this->initGame->mapPath = mapPaths.at(this->uiSelectors.at(UI_SELECTOR_TYPE::MAP)->getPos().first);
    this->initGame->mapTheme
        = (this->uiSelectors.at(UI_SELECTOR_TYPE::THEME)->getPos().first == 0) ? Components::THEME::DIRT : Components::THEME::STONE;
}

irr::scene::IAnimatedMeshSceneNode *Indie::MultiScene::createTheme(const std::string &filepath)
{
    irr::scene::IAnimatedMeshSceneNode *newTheme
        = context.getSceneManager()->addAnimatedMeshSceneNode(context.getSceneManager()->getMesh(filepath.c_str()));

    if (newTheme == nullptr) {
        throw Indie::Exceptions::AnimationException(ERROR_STR, "Cannot create new theme.");
    }
    newTheme->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    newTheme->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
    newTheme->setVisible(false);
    newTheme->setScale(irr::core::vector3df(1.4f, 1.4f, 1.4f));
    return newTheme;
}

void Indie::MultiScene::reset()
{
    context.getSceneManager()->clear();
    this->uiSelectors.at(UI_SELECTOR_TYPE::DEFAULT)->setPos(0, 0);
    init();
}

void Indie::MultiScene::update(irr::f32 ticks)
{
    /* ================================================================== */
    // 3D UPDATE
    /* ================================================================== */
    this->theme1->setVisible(this->initGame->mapTheme == Components::THEME::DIRT);
    this->theme2->setVisible(this->initGame->mapTheme == Components::THEME::STONE);
    this->theme1->setRotation(irr::core::vector3df(0, modelRotation, 0));
    this->theme2->setRotation(irr::core::vector3df(0, modelRotation, 0));
    this->modelRotation += float(10 * ticks);
    /* ================================================================== */
    // LAYOUTS SKIP
    /* ================================================================== */
    this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->update(); // We update the main selector
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second < 4) {
        this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(
            0, this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second); // Can't move right in the first 4 selectors
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 5) {
        this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(1, 5); // Can't move left from the last button
    }
    /* ================================================================== */
    // UPDATE BUTTONS
    /* ================================================================== */
    for (const auto &button : this->buttons) {
        button.second->update(this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos());
    }
    /* ================================================================== */
    // UPDATE CHECKBOXES
    /* ================================================================== */
    pUps->update(this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos());
    this->initGame->powerUp = pUps->getStatus();
    /* ================================================================== */
    // UPDATE SELECTORS
    /* ================================================================== */
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 0 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 0) {
        this->uiSelectors[UI_SELECTOR_TYPE::MAP]->update();
        this->initGame->mapPath = mapPaths.at(this->uiSelectors[UI_SELECTOR_TYPE::MAP]->getPos().first);
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 0 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 1) {
        this->uiSelectors[UI_SELECTOR_TYPE::THEME]->update();
        this->initGame->mapTheme
            = (this->uiSelectors[UI_SELECTOR_TYPE::THEME]->getPos().first == 0) ? Components::THEME::DIRT : Components::THEME::STONE;
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 0 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 2) {
        this->uiSelectors[UI_SELECTOR_TYPE::TIME]->update();
        this->initGame->timeLimit = (time_t)(this->uiSelectors[UI_SELECTOR_TYPE::TIME]->getPos().first * 5);
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 0 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 3) {
        this->uiSelectors[UI_SELECTOR_TYPE::AI]->update();
        this->initGame->nbAi = this->uiSelectors[UI_SELECTOR_TYPE::AI]->getPos().first;
    }
    /* ================================================================== */
    // CLICK BUTTONS
    /* ================================================================== */
    if (this->buttons[BUTTON_TYPE::PLAY]->getStatus() == Button::Status::Pressed
        || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_KEY_P) == true) {
        // Do stuff then go to Multi2
        context.getSceneManager()->clear();
        this->initGame->mapType = (this->uiSelectors[UI_SELECTOR_TYPE::MAP]->getPos().first == 0)
            ? Components::MAP_TYPE::DEFAULT
            : ((this->uiSelectors[UI_SELECTOR_TYPE::MAP]->getPos().first == 1) ? Components::MAP_TYPE::RANDOM : Components::MAP_TYPE::SAVED);
        std::cout << this->initGame->nbAi << std::endl;
        ServiceLocator::getInstance().get<SceneManager>().getScene<MultiKeybindsScene>()->setData(this->initGame.get());
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<MultiKeybindsScene>();
        skipScene(true, true, true, true);
        EventHandler::getInstance().resetKeys();
    }
    if (this->buttons.at(BUTTON_TYPE::BACK)->getStatus() == Button::Status::Pressed
        || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        context.getSceneManager()->clear();
        skipScene(true, true, true, true);
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<MainMenuScene>();
        EventHandler::getInstance().resetKeys();
    }
}

void Indie::MultiScene::renderPre3D()
{
    /* ================================================================== */
    // DISPLAY IMAGES
    /* ================================================================== */
    context.displayImage(title);
    context.displayImage(layout);
    context.displayImage(whiteBg);
}

void Indie::MultiScene::renderPost3D()
{
    // DISPLAY BUTONS
    for (const auto &button : this->buttons) {
        button.second->draw();
    }

    // DISPLAY CHECKBOXES
    pUps->draw();

    // DISPLAY TEXTS
    std::string mPath = getFileName(this->initGame->mapPath);
    std::string tName = (this->initGame->mapTheme == Components::THEME::DIRT) ? "Garden" : "Cobblestone";
    std::string aiAmmount = std::to_string(this->initGame->nbAi);
    std::string timeAmmount = std::to_string((this->initGame->timeLimit) / 60) + ":";
    std::map<std::string, int> scores_map
        = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo()->scores_map;
    int mapScore = 0;
    if (this->initGame->timeLimit % 60 < 10)
        timeAmmount += "0";
    timeAmmount += std::to_string((this->initGame->timeLimit) % 60);

    for (auto score : scores_map) {
        if (score.first == this->initGame->mapPath) {
            mapScore = score.second;
            break;
        }
    }
    font->draw(std::to_string(mapScore).c_str(), RECT(1000, 400, 0, 0), { 255, 255, 255, 255 });
    font->draw(mPath.c_str(), RECT(410 - (5 * int(mPath.size())), 139, 0, 0), { 255, 255, 255, 255 });
    font->draw(tName.c_str(), RECT(410 - (5 * int(tName.size())), 218, 0, 0), { 255, 255, 255, 255 });
    font->draw(timeAmmount.c_str(), RECT(410 - (5 * int(timeAmmount.size())), 300, 0, 0), { 255, 255, 255, 255 });
    font->draw(aiAmmount.c_str(), RECT(410 - (5 * int(aiAmmount.size())), 384, 0, 0), { 255, 255, 255, 255 });
}

std::string Indie::MultiScene::getFileName(std::string const &filepath)
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

/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MultiScene
*/

#include "MultiScene.hpp"
#include "GameScene.hpp"
#include "ImageLoader.hpp"
#include "InitGame.hpp"
#include "IntroScene.hpp"
#include "MainMenuScene.hpp"
#include "MenuScene.hpp"
#include "MultiKeybindsScene.hpp"
#include "PauseScene.hpp"
#include "SceneManager.hpp"
#include "ServiceLocator.hpp"
#include "SoloScene.hpp"
#include "SoundManager.hpp"
#include "PlayerMaps.hpp"
#include <filesystem>

const std::unordered_map<Indie::MultiScene::UI_SELECTOR_TYPE, irr::core::vector2di> Indie::MultiScene::uiSelectorsSize
    = { { Indie::MultiScene::UI_SELECTOR_TYPE::DEFAULT, { 3, 6 } }, { Indie::MultiScene::UI_SELECTOR_TYPE::THEME, { 3, 1 } },
          { Indie::MultiScene::UI_SELECTOR_TYPE::MAP, { 1, 1 } }, { Indie::MultiScene::UI_SELECTOR_TYPE::AI, { 3, 1 } },
          { Indie::MultiScene::UI_SELECTOR_TYPE::TIME, { 61, 1 } } };

// Il faut changer les valeurs ici dans les constructeurs des selecteurs quand on aura le nombre de map max etc
Indie::MultiScene::MultiScene(Indie::ContextManager &context)
    : context(context)
    , pUps(std::make_unique<Checkbox>(context))
    , xpBar(context)
    , initGame(std::make_unique<InitGame>())
{
    for (size_t uiSelectorType = (size_t)UI_SELECTOR_TYPE::DEFAULT; uiSelectorType < (size_t)UI_SELECTOR_TYPE::NONE; uiSelectorType++) {
        int x = this->uiSelectorsSize.at((UI_SELECTOR_TYPE)uiSelectorType).X;
        int y = this->uiSelectorsSize.at((UI_SELECTOR_TYPE)uiSelectorType).Y;
        std::unique_ptr<UiSelector> newUiSelector = std::make_unique<UiSelector>(
            x, y, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT);

        newUiSelector->setBLockSound(true, false);
        this->uiSelectors.insert({ (UI_SELECTOR_TYPE)uiSelectorType, std::move(newUiSelector) });
    }
    this->modelRotation = 0;
    this->initGame->powerUp = true;
    this->initGame->nbAi = 0;
    this->initGame->timeLimit = 18 * 5;
    this->pUps->setStatus(this->initGame->powerUp);
    this->uiSelectors.at(UI_SELECTOR_TYPE::DEFAULT)->setPos(1, 0);
    this->uiSelectors.at(UI_SELECTOR_TYPE::TIME)->setPos(18, 0);
    for (size_t buttonType = (size_t)BUTTON_TYPE::THEME; buttonType < (size_t)BUTTON_TYPE::NONE; buttonType++) {
        this->buttons.insert({ (BUTTON_TYPE)buttonType, std::make_unique<Button>(context) });
    }
}

void Indie::MultiScene::init() // Check all paths & init values
{
    // XPBAR INIT
    Indie::MasterInfo info = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo();
    xpBar.init("../ressources/images/Bar.png", 0, 100, 0);
    auto lvlCount = (unsigned int)MasterInfo::xp_level.size();
    if (info.lvl >= lvlCount) {
        xpBar.setSize(0, 1);
        xpBar.setValue(1);
        xpBar.setLevel(lvlCount);
    } else {
        xpBar.setSize(0, MasterInfo::xp_level[info.lvl]);
        xpBar.setValue(info.xp);
        xpBar.setLevel(info.lvl);
    }
    xpBar.update();
    // 3D INIT
    irr::scene::ICameraSceneNode *camera = context.getSceneManager()->addCameraSceneNode(0, { 0, 0, -75 }, { 0, 0, 0 }, -1, true);

    if (camera == nullptr) {
        throw Indie::Exceptions::SceneManagerException(ERROR_STR, "Cannot add camera scene node.");
    }
    camera->setTarget(irr::core::vector3df(-52, 0, 0));
    context.getSceneManager()->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.2f, 0.2f, 0.3f, 0.0f), 400.0f);

    this->theme1 = this->createTheme("../ressources/static_mesh/map1model.mc.ply");
    this->theme2 = this->createTheme("../ressources/static_mesh/map2model.mc.ply");
    this->theme3 = this->createTheme("../ressources/static_mesh/map3model.mc.ply");
    // IMAGES GET
    this->title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi1/title.png");
    this->layout = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi1/Layout.png");
    this->whiteBg = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi1/WhiteBG.png");
    // FONT GET
    this->font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    if (this->font == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/Banschrift.xml\"");
    }
    // BUTTONS INIT
    this->buttons.at(BUTTON_TYPE::PLAY)->init(context, "../ressources/images/multi1/Suivant.png", 2, 4, POS(0, 0), false);
    this->buttons.at(BUTTON_TYPE::BACK)->init(context, "../ressources/images/multi1/Retour.png", 2, 5, POS(0, 0), false);
    this->buttons.at(BUTTON_TYPE::MAP)->init(context, "../ressources/images/multi1/Niveau.png", 1, 0, POS(0, 0), false);
    this->buttons.at(BUTTON_TYPE::THEME)->init(context, "../ressources/images/multi1/Theme.png", 1, 1, POS(0, 0), false);
    this->buttons.at(BUTTON_TYPE::TIME)->init(context, "../ressources/images/multi1/Temps.png", 1, 2, POS(0, 0), false);
    this->buttons.at(BUTTON_TYPE::AI)->init(context, "../ressources/images/multi1/IA.png", 1, 3, POS(0, 0), false);
    // CHECKBOXES INIT
    this->pUps->init("../ressources/images/multi1/Check.png", 1, 4, POS(0, 0));
    this->pUps->setStatus(this->initGame->powerUp);
    this->availableMaps.clear();
    for (const auto &map : PlayerMaps::mapPaths)
        this->availableMaps.push_back(map.path);
    for (const auto &entry : std::filesystem::directory_iterator("../ressources/maps/")) {
        if (std::find(this->availableMaps.begin(), this->availableMaps.end(), entry.path().u8string()) != this->availableMaps.end())
            continue;
        if (entry.is_regular_file() == true && entry.path().extension() == ".supermap")
            availableMaps.push_back(entry.path().u8string());
    }
    this->uiSelectors.at(UI_SELECTOR_TYPE::MAP)->setSize((int)availableMaps.size(), 1);
    this->initGame->mapPath = availableMaps.at(this->uiSelectors.at(UI_SELECTOR_TYPE::MAP)->getPos().first);
    this->initGame->mapTheme = (Components::THEME)this->uiSelectors[UI_SELECTOR_TYPE::THEME]->getPos().first;
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
    this->uiSelectors.at(UI_SELECTOR_TYPE::DEFAULT)->setPos(1, 0);
    init();
}

void Indie::MultiScene::update(irr::f32 ticks)
{
    /* ================================================================== */
    // 3D UPDATE
    /* ================================================================== */
    this->theme1->setVisible(this->initGame->mapTheme == Components::THEME::DIRT);
    this->theme2->setVisible(this->initGame->mapTheme == Components::THEME::STONE);
    this->theme3->setVisible(this->initGame->mapTheme == Components::THEME::SNOW);
    this->theme1->setRotation(irr::core::vector3df(0, modelRotation, 0));
    this->theme2->setRotation(irr::core::vector3df(0, modelRotation, 0));
    this->theme3->setRotation(irr::core::vector3df(0, modelRotation, 0));
    this->modelRotation += float(10 * ticks);
    /* ================================================================== */
    // LAYOUTS SKIP
    /* ================================================================== */
    this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->update(); // We update the main selector
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 5) {
        if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first != 2) {
            this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(2, 4);
        }
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first != 1 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second < 4) {
        // ServiceLocator::getInstance().get<SoundManager>().playSound("menu_lock");
        this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(1, this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second); // First selectors
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 0 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 4) {
        ServiceLocator::getInstance().get<SoundManager>().playSound("menu_lock");
        this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(1, this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second); // Checkbox
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
    if (buttons.at(BUTTON_TYPE::MAP)->getStatus() == Button::Status::Selected) {
        this->uiSelectors[UI_SELECTOR_TYPE::MAP]->update();
        this->initGame->mapPath = availableMaps.at(this->uiSelectors[UI_SELECTOR_TYPE::MAP]->getPos().first);
    }
    if (buttons.at(BUTTON_TYPE::THEME)->getStatus() == Button::Status::Selected) {
        this->uiSelectors[UI_SELECTOR_TYPE::THEME]->update();
        this->initGame->mapTheme = (Components::THEME)this->uiSelectors[UI_SELECTOR_TYPE::THEME]->getPos().first;
    }
    if (buttons.at(BUTTON_TYPE::TIME)->getStatus() == Button::Status::Selected) {
        this->uiSelectors[UI_SELECTOR_TYPE::TIME]->update();
        std::pair<int, int> currentPos = this->uiSelectors[UI_SELECTOR_TYPE::TIME]->getPos();

        if (currentPos.first < 18) {
            currentPos.first = 18;
            this->uiSelectors[UI_SELECTOR_TYPE::TIME]->setPos(currentPos.first, currentPos.second);
        }
        this->initGame->timeLimit = (time_t)(currentPos.first * 5);
    }
    if (buttons.at(BUTTON_TYPE::AI)->getStatus() == Button::Status::Selected) {
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
        ServiceLocator::getInstance().get<SceneManager>().getScene<MultiKeybindsScene>()->setData(this->initGame.get());
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<MultiKeybindsScene>();
        skipScene(true, true, true, true);
        EventHandler::getInstance().resetKeys();
    }
    if (this->buttons.at(BUTTON_TYPE::BACK)->getStatus() == Button::Status::Pressed
        || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        ServiceLocator::getInstance().get<SoundManager>().playSound("menu_back");
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
    std::string mPath = ServiceLocator::getInstance().get<SceneManager>().getScene<Indie::SoloScene>()->getFileName(this->initGame->mapPath);
    std::string tName;
    std::string aiAmmount = std::to_string(this->initGame->nbAi);
    std::string timeAmmount = std::to_string((this->initGame->timeLimit) / 60) + ":";
    std::unordered_map<std::string, int> scores_map
        = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo().scores_map;
    int mapScore = 0;
    if (this->initGame->timeLimit % 60 < 10)
        timeAmmount += "0";
    timeAmmount += std::to_string((this->initGame->timeLimit) % 60);

    if (this->initGame->mapTheme == Components::THEME::DIRT)
        tName = "Jardin";
    else if (this->initGame->mapTheme == Components::THEME::STONE)
        tName = "Cobblestone";
    else
        tName = "Hiver";
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
    // DISPLAY XPBAR
    xpBar.draw(POS(760, 0));
}

void Indie::MultiScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

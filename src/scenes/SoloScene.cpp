
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoloScene
*/

#include "SoloScene.hpp"
#include "GameScene.hpp"
#include "InitGame.hpp"
#include "IntroScene.hpp"
#include "MainMenuScene.hpp"
#include "MenuScene.hpp"
#include "PauseScene.hpp"
#include "ServiceLocator.hpp"
#include <filesystem>
#include <fstream>

const std::vector<std::pair<std::string, Indie::Components::PlayerComponent::PLAYER_COLOR>> Indie::SoloScene::charaPaths {
    { "../ressources/textures/character/Gris.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC },
    { "../ressources/textures/character/Bleu.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE },
    { "../ressources/textures/character/Rouge.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED },
    { "../ressources/textures/character/Vert.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN },
    { "../ressources/textures/character/Violet.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE },
    { "../ressources/textures/character/Jaune.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW },
    { "../ressources/textures/character/Gris+.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC },
    { "../ressources/textures/character/Bleu+.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE },
    { "../ressources/textures/character/Rouge+.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED },
    { "../ressources/textures/character/Vert+.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN },
    { "../ressources/textures/character/Violet+.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE },
    { "../ressources/textures/character/Jaune+.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW }
};

const std::unordered_map<Indie::SoloScene::UI_SELECTOR_TYPE, irr::core::vector2di> Indie::SoloScene::uiSelectorsSize
    = { { Indie::SoloScene::UI_SELECTOR_TYPE::DEFAULT, { 5, 6 } }, { Indie::SoloScene::UI_SELECTOR_TYPE::SKIN, { 1, 1 } },
          { Indie::SoloScene::UI_SELECTOR_TYPE::THEME, { 2, 1 } }, { Indie::SoloScene::UI_SELECTOR_TYPE::MAP, { 1, 1 } } };

// Il faut changer les valeurs ici dans les constructeurs des selecteurs quand on aura le nombre de map max etc
Indie::SoloScene::SoloScene(Indie::ContextManager &context)
    : context(context)
    , pUps(std::make_unique<Checkbox>(context))
    , initGame(std::make_unique<InitGame>())
    , playerParams(std::make_unique<PlayerParams>())
{
    for (size_t uiSelectorType = (size_t)UI_SELECTOR_TYPE::DEFAULT; uiSelectorType < (size_t)UI_SELECTOR_TYPE::NONE; uiSelectorType++) {
        int x = this->uiSelectorsSize.at((UI_SELECTOR_TYPE)uiSelectorType).X;
        int y = this->uiSelectorsSize.at((UI_SELECTOR_TYPE)uiSelectorType).Y;

        this->uiSelectors.insert({ (UI_SELECTOR_TYPE)uiSelectorType,
            std::make_unique<UiSelector>(
                x, y, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT) });
    }
    uiSelectors.at(Indie::SoloScene::UI_SELECTOR_TYPE::SKIN)->setBLockSound(true, false);
    uiSelectors.at(Indie::SoloScene::UI_SELECTOR_TYPE::THEME)->setBLockSound(true, false);
    uiSelectors.at(Indie::SoloScene::UI_SELECTOR_TYPE::MAP)->setBLockSound(true, false);
    this->pUpsEnabled = true;
    this->pUps->setStatus(pUpsEnabled);
    this->uiSelectors[UI_SELECTOR_TYPE::SKIN]->setSize(int(charaPaths.size()), 1);
    this->modelRotation = 0;
    this->mapPaths.push_back("Default");
    this->mapPaths.push_back("Random");
    for (const auto &entry : std::filesystem::directory_iterator("../ressources/maps/"))
        this->mapPaths.push_back(entry.path().u8string());
    this->uiSelectors[UI_SELECTOR_TYPE::MAP]->setSize(int(mapPaths.size()), 1);
    for (size_t buttonType = (size_t)BUTTON_TYPE::SKIN; buttonType < (size_t)BUTTON_TYPE::NONE; buttonType++) {
        this->buttons.insert({ (BUTTON_TYPE)buttonType, std::make_unique<Button>(context) });
    }
}

Indie::SoloScene::~SoloScene()
{
}

irr::scene::IAnimatedMeshSceneNode *Indie::SoloScene::createTheme(const std::string &filepath)
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

void Indie::SoloScene::init()
{
    // TODO : XP BAR
    /* ================================================================== */
    // 3D INIT
    /* ================================================================== */
    irr::scene::ICameraSceneNode *camera
        = context.getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0, 0, -75), irr::core::vector3df(0, 0, 0), -1, true);

    camera->setTarget(irr::core::vector3df(-52, 0, 0));
    context.getSceneManager()->addLightSceneNode(camera, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.2f, 0.2f, 0.3f, 0.0f), 400.0f);
    /* ================================================================== */
    // IMAGES GET
    /* ================================================================== */
    title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/solo/title.png");
    layout = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/solo/Layout.png");
    kbLayout = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/solo/KB_Layout.png");
    /* ================================================================== */
    // FONT GET
    /* ================================================================== */
    font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    /* ================================================================== */
    // BUTTONS INIT
    /* ================================================================== */
    this->buttons.at(BUTTON_TYPE::PLAY)->init(context, "../ressources/images/solo/Play.png", 4, 4, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::BACK)->init(context, "../ressources/images/solo/Retour.png", 4, 5, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::SKIN)->init(context, "../ressources/images/solo/Perso.png", 1, 1, POS(0, 0), false);
    this->buttons.at(BUTTON_TYPE::THEME)->init(context, "../ressources/images/solo/Theme.png", 1, 2, POS(0, 0), false);
    this->buttons.at(BUTTON_TYPE::MAP)->init(context, "../ressources/images/solo/Niveau.png", 1, 0, POS(0, 0), false);
    /* ================================================================== */
    // CHECKBOXES INIT
    /* ================================================================== */
    pUps->init("../ressources/images/solo/Check.png", 1, 3, POS(0, 0));
    pUps->setStatus(pUpsEnabled);
    /* ================================================================== */
    // KEYBINDS INIT
    /* ================================================================== */
    std::find_if(keybinds.begin(), keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::UP);
    })->second->init("../ressources/images/solo/KB_Up.png", 1, 4, POS(183, 468));
    std::find_if(keybinds.begin(), keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::DOWN);
    })->second->init("../ressources/images/solo/KB_Down.png", 1, 5, POS(183, 547));
    std::find_if(keybinds.begin(), keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::LEFT);
    })->second->init("../ressources/images/solo/KB_Left.png", 0, 5, POS(108, 547));
    std::find_if(keybinds.begin(), keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::RIGHT);
    })->second->init("../ressources/images/solo/KB_Right.png", 2, 5, POS(261, 547));
    std::find_if(keybinds.begin(), keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::DROP);
    })->second->init("../ressources/images/solo/KB_Bar.png", 3, 5, POS(456, 547));
    // Some inits :
    this->playerParams->playerTexture = charaPaths[this->uiSelectors[UI_SELECTOR_TYPE::SKIN]->getPos().first].first;
    this->playerParams->playerColor = charaPaths[this->uiSelectors[UI_SELECTOR_TYPE::SKIN]->getPos().first].second;
    this->playerParams->playerKeys.clear();
    this->initGame->mapPath = mapPaths[this->uiSelectors[UI_SELECTOR_TYPE::MAP]->getPos().first];
    this->initGame->mapTheme = (this->uiSelectors[UI_SELECTOR_TYPE::THEME]->getPos().first == 0) ? Components::THEME::DIRT : Components::THEME::STONE;
    this->theme1 = this->createTheme("../ressources/static_mesh/map1model.mc.ply");
    this->theme2 = this->createTheme("../ressources/static_mesh/map2model.mc.ply");
}

void Indie::SoloScene::reset()
{
    context.getSceneManager()->clear();
    this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(0, 0);
    this->init();
}

void Indie::SoloScene::setKeybinds(const std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Indie::Keybind>>> &keybinds)
{
    this->keybinds.clear();
    for (auto &keybind : keybinds) {
        this->keybinds.push_back({keybind.first, std::make_unique<Indie::Keybind>(*keybind.second)});
    }
}

const std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Indie::Keybind>>> &Indie::SoloScene::getKeybinds(void) const
{
    return this->keybinds;
}

void Indie::SoloScene::update(irr::f32 ticks)
{
    // 3D UPDATE
    theme1->setVisible(this->initGame->mapTheme == Components::THEME::DIRT);
    theme2->setVisible(this->initGame->mapTheme == Components::THEME::STONE);
    theme1->setRotation(irr::core::vector3df(0, modelRotation, 0));
    theme2->setRotation(irr::core::vector3df(0, modelRotation, 0));
    modelRotation += float(10 * ticks);
    // KEYBINDS SET USED
    for (auto &keybind : this->keybinds) {
        keybind.second->setUsedKeys(this->keybinds);
    }
    // UPDATE KEYBINDS
    for (auto &keybind : this->keybinds) {
        keybind.second->update(this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos());
    }
    if (this->keybinds[0].second->getStatus() || this->keybinds[1].second->getStatus() || this->keybinds[2].second->getStatus()
        || this->keybinds[3].second->getStatus() || this->keybinds[4].second->getStatus())
        return; // We don't check anything else while the player is setting a key
    /* ================================================================== */
    // LAYOUTS SKIP (psk le layout est chelou on doit le faire en dur)
    // En gros on skip des cases vides dans le selecteur pour retrouver
    // les boutons qui sont plus loin (psk la taille est pas pareille partout)
    /* ================================================================== */
    this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->update(); // We update the main selector
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 3 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 2) {
        this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(4, 4); // PowerUps -> = Play
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second < 4) {
        this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(
            1, this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second); // Can't move right or left in the first 3 selectors
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 4) {
        if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 0) {
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_lock");
            this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(1, 4); // Up <- == Up
        }
        if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 2) {
            ServiceLocator::getInstance().get<SoundManager>().playSound("menu_lock");
            this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(1, 4); // Up -> == Up
        }
        if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 3)
            this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->setPos(1, 3); // Play <- == PowerUps
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
    this->pUps->update(this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos());
    this->pUpsEnabled = this->pUps->getStatus();
    /* ================================================================== */
    // UPDATE SELECTORS
    /* ================================================================== */
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 1 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 1) {
        this->uiSelectors[UI_SELECTOR_TYPE::SKIN]->update();
        this->playerParams->playerTexture = charaPaths[this->uiSelectors[UI_SELECTOR_TYPE::SKIN]->getPos().first].first;
        this->playerParams->playerColor = charaPaths[this->uiSelectors[UI_SELECTOR_TYPE::SKIN]->getPos().first].second;
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 1 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 0) {
        this->uiSelectors[UI_SELECTOR_TYPE::MAP]->update();
        this->initGame->mapPath = mapPaths[this->uiSelectors[UI_SELECTOR_TYPE::MAP]->getPos().first];
    }
    if (this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().first == 1 && this->uiSelectors[UI_SELECTOR_TYPE::DEFAULT]->getPos().second == 2) {
        this->uiSelectors[UI_SELECTOR_TYPE::THEME]->update();
        this->initGame->mapTheme
            = (this->uiSelectors[UI_SELECTOR_TYPE::THEME]->getPos().first == 0) ? Components::THEME::DIRT : Components::THEME::STONE;
    }
    /* ================================================================== */
    // CLICK BUTTONS
    /* ================================================================== */
    if (this->buttons.at(BUTTON_TYPE::PLAY)->getStatus() == Button::Status::Pressed
        || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_KEY_P) == true) {
        auto &sceneManager = ServiceLocator::getInstance().get<SceneManager>();

        this->initGameStruct(sceneManager);
        sceneManager.setScene<GameScene>(context);
        sceneManager.setSubScene<IntroScene>();
        skipScene(false, false, true, true);
        Indie::EventHandler::getInstance().resetKeys();
    }
    if (this->buttons.at(BUTTON_TYPE::BACK)->getStatus() == Button::Status::Pressed
        || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        context.getSceneManager()->clear();
        skipScene(true, true, true, true);
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<MainMenuScene>();
        Indie::EventHandler::getInstance().resetKeys();
    }
}

void Indie::SoloScene::initGameStruct(SceneManager &sceneManager)
{
    context.getSceneManager()->clear();
    this->initGame->mapPath = this->initGame->mapPath;
    this->initGame->mode = GameScene::MODE::SOLO;
    this->initGame->nbAi = 3;
    this->initGame->mapTheme = this->initGame->mapTheme;
    this->initGame->mapType = (this->uiSelectors[UI_SELECTOR_TYPE::MAP]->getPos().first == 0)
        ? Components::MAP_TYPE::DEFAULT
        : ((this->uiSelectors[UI_SELECTOR_TYPE::MAP]->getPos().first == 1) ? Components::MAP_TYPE::RANDOM : Components::MAP_TYPE::SAVED);
    this->initGame->powerUp = pUpsEnabled;
    this->initGame->timeLimit = 180;
    for (auto &it : keybinds) {
        this->playerParams->playerKeys.insert({ it.second->getKey(), it.first });
    }
    this->initGame->playersParams = { *this->playerParams };
    sceneManager.getScene<GameScene>()->setInitGame(*this->initGame);
}

void Indie::SoloScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    auto &sceneManager = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>();

    sceneManager.setSceneUpdateActive(update);
    sceneManager.setSceneRenderActive(render);
    sceneManager.setSubSceneUpdateActive(subUpdate);
    sceneManager.setSubSceneRenderActive(subRender);
}

void Indie::SoloScene::renderPre3D()
{
    /* ================================================================== */
    // DISPLAY IMAGES
    /* ================================================================== */
    context.displayImage(title);
    context.displayImage(layout);
    context.displayImage(kbLayout);
}

void Indie::SoloScene::renderPost3D()
{
    // DISPLAY BUTONS
    for (auto const &button : this->buttons) {
        button.second->draw();
    }

    // DISPLAY CHECKBOXES
    pUps->draw();

    // DISPLAY TEXTS
    std::string mPath = this->getFileName(this->initGame->mapPath);
    std::string pName = this->getFileName(this->playerParams->playerTexture);
    std::string tName = (this->initGame->mapTheme == Components::THEME::DIRT) ? "Garden" : "Cobblestone";
    std::map<std::string, int> scores_map
        = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo()->scores_map;
    int mapScore = 0;
    for (auto score : scores_map) {
        if (score.first == this->getFileName(this->initGame->mapPath)) {
            mapScore = score.second;
            break;
        }
    }
    font->draw(mPath.c_str(), RECT(410 - (5 * int(mPath.size())), 139, 0, 0), { 255, 255, 255, 255 });
    font->draw(pName.c_str(), RECT(410 - (5 * int(pName.size())), 218, 0, 0), { 255, 255, 255, 255 });
    font->draw(tName.c_str(), RECT(410 - (5 * int(tName.size())), 300, 0, 0), { 255, 255, 255, 255 });
    font->draw(std::to_string(mapScore).c_str(), RECT(1000, 400, 0, 0), { 255, 255, 255, 255 });

    /* ================================================================== */
    // DISPLAY KEYBINDS
    /* ================================================================== */
    for (auto const &keybind : this->keybinds) {
        keybind.second->draw();
    }
    if (this->keybinds[0].second->getStatus() || this->keybinds[1].second->getStatus() || this->keybinds[2].second->getStatus()
        || this->keybinds[3].second->getStatus() || this->keybinds[4].second->getStatus())
        context.displayImage(this->keybinds[0].second->tick);
}

void Indie::SoloScene::resetKeybinds(void)
{
    this->keybinds.clear();
    this->keybinds.push_back({ Indie::Components::KEY_TYPE::UP, std::make_unique<Keybind>(context, irr::EKEY_CODE::KEY_UP) });
    this->keybinds.push_back({ Indie::Components::KEY_TYPE::DOWN, std::make_unique<Keybind>(context, irr::EKEY_CODE::KEY_DOWN) });
    this->keybinds.push_back({ Indie::Components::KEY_TYPE::LEFT, std::make_unique<Keybind>(context, irr::EKEY_CODE::KEY_LEFT) });
    this->keybinds.push_back({ Indie::Components::KEY_TYPE::RIGHT, std::make_unique<Keybind>(context, irr::EKEY_CODE::KEY_RIGHT) });
    this->keybinds.push_back({ Indie::Components::KEY_TYPE::DROP, std::make_unique<Keybind>(context, irr::EKEY_CODE::KEY_SPACE) });
}

std::string Indie::SoloScene::getFileName(std::string const &filepath)
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
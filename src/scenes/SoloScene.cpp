
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoloScene
*/

#include "SoloScene.hpp"
#include "ServiceLocator.hpp"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "InitGame.hpp"
#include "PauseScene.hpp"
#include "IntroScene.hpp"

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

const std::vector<std::pair<std::string, Indie::Components::PlayerComponent::PLAYER_COLOR>> Indie::SoloScene::charaPaths
{
    {"../ressources/textures/character/blue1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE},
    {"../ressources/textures/character/blue2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE},
    {"../ressources/textures/character/red1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED},
    {"../ressources/textures/character/red2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED},
    {"../ressources/textures/character/generic1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC},
    {"../ressources/textures/character/generic2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC},
    {"../ressources/textures/character/green1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN},
    {"../ressources/textures/character/green2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN},
    {"../ressources/textures/character/purple1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE},
    {"../ressources/textures/character/purple2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE},
    {"../ressources/textures/character/yellow1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW},
    {"../ressources/textures/character/yellow2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW}
};

const std::vector<std::string> Indie::SoloScene::mapPaths {
    "../ressources/maps/default.txt"
};

void Indie::SoloScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

// Il faut changer les valeurs ici dans les constructeurs des selecteurs quand on aura le nombre de map max etc
Indie::SoloScene::SoloScene(Indie::ContextManager &context)
    : context(context)
    , selector(5, 6, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , charaSelector(1, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , themeSelector(2, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , mapSelector(1, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{
    charaSelector.setSize(int(charaPaths.size()), 1); // On set juste la size en plus petit pour pas qu'il ai accès à des perso mdr
    mapSelector.setSize(int(mapPaths.size()), 1);
    playerKeys.push_back({irr::KEY_LEFT, Indie::Components::KEY_TYPE::LEFT});
    playerKeys.push_back({irr::KEY_RIGHT, Indie::Components::KEY_TYPE::RIGHT});
    playerKeys.push_back({irr::KEY_UP, Indie::Components::KEY_TYPE::UP});
    playerKeys.push_back({irr::KEY_DOWN, Indie::Components::KEY_TYPE::DOWN});
    playerKeys.push_back({irr::KEY_SPACE, Indie::Components::KEY_TYPE::DROP});
}

Indie::SoloScene::~SoloScene()
{
    if (font)
        context.getGuiEnv()->removeFont(font);
}

void Indie::SoloScene::init()
{
    // TODO : XP BAR
    // TODO : SCORE
    // TODO : create camera && mesh
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
    // BUTTONS CREATE
    /* ================================================================== */
    play.reset(new Button(context));
    back.reset(new Button(context));
    charaButton.reset(new Button(context));
    themeButton.reset(new Button(context));
    mapButton.reset(new Button(context));
    /* ================================================================== */
    // BUTTONS INIT
    /* ================================================================== */
    play->init(context, "../ressources/images/solo/Play.png", 4, 4, POS(0,0));
    back->init(context, "../ressources/images/solo/Retour.png", 4, 5, POS(0,0));
    mapButton->init(context, "../ressources/images/solo/Niveau.png", 1, 0, POS(0,0));
    themeButton->init(context, "../ressources/images/solo/Theme.png", 1, 2, POS(0,0));
    charaButton->init(context, "../ressources/images/solo/Perso.png", 1, 1, POS(0,0));
    /* ================================================================== */
    // CHECKBOXES CREATE
    /* ================================================================== */
    pUps.reset(new Checkbox(context));
    /* ================================================================== */
    // CHECKBOXES INIT
    /* ================================================================== */
    pUps->init("../ressources/images/solo/Check.png", 1, 3, POS(0, 0));
    /* ================================================================== */
    // KEYBINDS CREATE
    /* ================================================================== */
    up.reset(new Keybind(context, irr::EKEY_CODE::KEY_UP));
    down.reset(new Keybind(context, irr::EKEY_CODE::KEY_DOWN));
    left.reset(new Keybind(context, irr::EKEY_CODE::KEY_LEFT));
    right.reset(new Keybind(context, irr::EKEY_CODE::KEY_RIGHT));
    bomb.reset(new Keybind(context, irr::EKEY_CODE::KEY_SPACE));
    /* ================================================================== */
    // KEYBINDS INIT
    /* ================================================================== */
    up->init("../ressources/images/solo/KB_Up.png", 1, 4, POS(183, 468));
    down->init("../ressources/images/solo/KB_Down.png", 1, 5, POS(183, 547));
    left->init("../ressources/images/solo/KB_Left.png", 0, 5, POS(108, 547));
    right->init("../ressources/images/solo/KB_Right.png", 2, 5, POS(261, 547));
    bomb->init("../ressources/images/solo/KB_Bar.png", 3, 5, POS(451, 547));
    // Some inits :
    playerTexture = charaPaths[charaSelector.getPos().first].first;
    playerColor = charaPaths[charaSelector.getPos().first].second;
    mapPath = mapPaths[mapSelector.getPos().first];
    mapTheme = (themeSelector.getPos().first == 0) ? Components::THEME::DIRT : Components::THEME::STONE;
}

void Indie::SoloScene::reset()
{
    selector.setPos(0, 0);
    init();
}

void Indie::SoloScene::update(irr::f32 ticks)
{
    playerKeyCodes.clear();
    playerKeyCodes.push_back(up->getKey());
    playerKeyCodes.push_back(down->getKey());
    playerKeyCodes.push_back(left->getKey());
    playerKeyCodes.push_back(right->getKey());
    playerKeyCodes.push_back(bomb->getKey());
    /* ================================================================== */
    // UPDATE KEYBINDS
    /* ================================================================== */
    up->setUsedKeys(playerKeyCodes);
    down->setUsedKeys(playerKeyCodes);
    left->setUsedKeys(playerKeyCodes);
    right->setUsedKeys(playerKeyCodes);
    bomb->setUsedKeys(playerKeyCodes);
    up->update(selector.getPos());
    down->update(selector.getPos());
    left->update(selector.getPos());
    right->update(selector.getPos());
    bomb->update(selector.getPos());
    if (up->getStatus() || down->getStatus() || left->getStatus() || right->getStatus() || bomb->getStatus())
        return; // We don't check anything else while the player is setting a key
    /* ================================================================== */
    // LAYOUTS SKIP (psk le layout est chelou on doit le faire en dur)
    // En gros on skip des cases vides dans le selecteur pour retrouver
    // les boutons qui sont plus loin (psk la taille est pas pareille partout)
    /* ================================================================== */
    selector.update(); // We update the main selector
    if (selector.getPos().second == 3 && selector.getPos().first == 2) {
        selector.setPos(4, 4); // PowerUps -> = Play
    }
    if (selector.getPos().second < 4) {
        selector.setPos(1, selector.getPos().second); // Can't move right or left in the first 3 selectors
    }
    if (selector.getPos().second == 4) {
        if (selector.getPos().first == 0)
            selector.setPos(1, 4); // Up <- == Up
        if (selector.getPos().first == 2)
            selector.setPos(1, 4); // Up -> == Up
        if (selector.getPos().first == 3)
            selector.setPos(1, 3); // Play <- == PowerUps
    }
    /* ================================================================== */
    // UPDATE BUTTONS
    /* ================================================================== */
    charaButton->update(selector.getPos());
    themeButton->update(selector.getPos());
    mapButton->update(selector.getPos());
    play->update(selector.getPos());
    back->update(selector.getPos());
    /* ================================================================== */
    // UPDATE CHECKBOXES
    /* ================================================================== */
    pUps->update(selector.getPos());
    /* ================================================================== */
    // UPDATE SELECTORS
    /* ================================================================== */
    if (selector.getPos().first == 1 && selector.getPos().second == 1) {
        charaSelector.update();
        playerTexture = charaPaths[charaSelector.getPos().first].first;
        playerColor = charaPaths[charaSelector.getPos().first].second;
    }
    if (selector.getPos().first == 1 && selector.getPos().second == 0) {
        mapSelector.update();
        mapPath = mapPaths[mapSelector.getPos().first];
    }
    if (selector.getPos().first == 1 && selector.getPos().second == 2) {
        themeSelector.update();
        mapTheme = (themeSelector.getPos().first == 0) ? Components::THEME::DIRT : Components::THEME::STONE;
    }
    EventHandler::getInstance().resetKeysStatusOnce();
    EventHandler::getInstance().resetKeysStatus();
    /* ================================================================== */
    // CLICK BUTTONS
    /* ================================================================== */
    if (play->getStatus() == Button::Status::Pressed) {
        InitGame init;
        PlayerParams initPlayer;

        init.mapPath = mapPath;
        init.mode = GameScene::MODE::SOLO;
        init.nbAi = 3;
        init.mapTheme = mapTheme;
        init.mapType = Components::MAP_TYPE::SAVED;
        init.powerUp = pUps->getStatus();
        init.timeLimit = 180;
        initPlayer.playerTexture = charaPaths[charaSelector.getPos().first].first;
        initPlayer.playerColor = charaPaths[charaSelector.getPos().first].second;
        initPlayer.playerKeys.insert({up->getKey(), Indie::Components::KEY_TYPE::UP});
        initPlayer.playerKeys.insert({down->getKey(), Indie::Components::KEY_TYPE::DOWN});
        initPlayer.playerKeys.insert({left->getKey(), Indie::Components::KEY_TYPE::LEFT});
        initPlayer.playerKeys.insert({right->getKey(), Indie::Components::KEY_TYPE::RIGHT});
        initPlayer.playerKeys.insert({bomb->getKey(), Indie::Components::KEY_TYPE::DROP});
        init.playersParams = {initPlayer};
        ServiceLocator::getInstance().get<SceneManager>().getScene<GameScene>()->setInitGame(init);
        ServiceLocator::getInstance().get<SceneManager>().setScene<GameScene>(context);
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<IntroScene>();
        skipScene(false, true, true, true);
        // TODO : Directory Iterator pour les maps.
    }
    if (back->getStatus() == Button::Status::Pressed) {
        skipScene(true, true, true, true);
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<MainMenuScene>();
    }
    //std::cout << "X : " << selector.getPos().first << ", Y : " << selector.getPos().second << std::endl;
}

void Indie::SoloScene::renderPre3D()
{}

void Indie::SoloScene::renderPost3D()
{
    /* ================================================================== */
    // DISPLAY IMAGES
    /* ================================================================== */
    context.displayImage(title);
    context.displayImage(layout);
    context.displayImage(kbLayout);
    /* ================================================================== */
    // DISPLAY BUTONS
    /* ================================================================== */
    charaButton->draw();
    themeButton->draw();
    mapButton->draw();
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
    std::string pName = getFileName(playerTexture);
    std::string tName = (mapTheme == Components::THEME::DIRT) ? "Garden" : "Cobblestone";
    font->draw(mPath.c_str(), RECT(410 - (5 * int(mPath.size())), 139, 0, 0), {255, 255, 255, 255});
    font->draw(pName.c_str(), RECT(410 - (5 * int(pName.size())), 218, 0, 0), {255, 255, 255, 255});
    font->draw(tName.c_str(), RECT(410 - (5 * int(tName.size())), 300, 0, 0), {255, 255, 255, 255});
    /* ================================================================== */
    // DISPLAY KEYBINDS
    /* ================================================================== */
    up->draw();
    down->draw();
    left->draw();
    right->draw();
    bomb->draw();
    if (up->getStatus() || down->getStatus() || left->getStatus() || right->getStatus() || bomb->getStatus())
        context.displayImage(up->tick);
}
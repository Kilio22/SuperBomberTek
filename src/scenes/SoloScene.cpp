
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoloScene
*/

#include "SoloScene.hpp"
<<<<<<< Updated upstream
#include "CSVParser.hpp"
=======
#include "ServiceLocator.hpp"
#include "MainMenuScene.hpp"
#include "MenuScene.hpp"
>>>>>>> Stashed changes
#include "GameScene.hpp"
#include "InitGame.hpp"
#include "IntroScene.hpp"
#include "MainMenuScene.hpp"
#include "PauseScene.hpp"
#include "ServiceLocator.hpp"
#include <filesystem>
#include <fstream>

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

const std::vector<std::pair<std::string, Indie::Components::PlayerComponent::PLAYER_COLOR>> Indie::SoloScene::charaPaths {
    { "../ressources/textures/character/blue1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE },
    { "../ressources/textures/character/red1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED },
    { "../ressources/textures/character/generic1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC },
    { "../ressources/textures/character/green1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN },
    { "../ressources/textures/character/purple1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE },
    { "../ressources/textures/character/yellow1.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW },
    { "../ressources/textures/character/blue2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::BLUE },
    { "../ressources/textures/character/red2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::RED },
    { "../ressources/textures/character/generic2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GENERIC },
    { "../ressources/textures/character/green2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::GREEN },
    { "../ressources/textures/character/purple2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::PURPLE },
    { "../ressources/textures/character/yellow2.png", Indie::Components::PlayerComponent::PLAYER_COLOR::YELLOW }
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
    pUpsEnabled = true;
    charaSelector.setSize(int(charaPaths.size()), 1); // On set juste la size en plus petit pour pas qu'il ai accès à des perso mdr
    modelRotation = 0;
    mapPaths.push_back("Default");
    mapPaths.push_back("Random");
    for (const auto &entry : std::filesystem::directory_iterator("../ressources/maps/"))
        mapPaths.push_back(entry.path().u8string());
    mapSelector.setSize(int(mapPaths.size()), 1);
    playerKeys = {};
    this->getSavedKeybinds();
    for (size_t buttonType = (size_t)BUTTON_TYPE::SKIN; buttonType < (size_t)BUTTON_TYPE::NONE; buttonType++) {
        this->buttons.insert({ (BUTTON_TYPE)buttonType, std::make_unique<Button>(context) });
    }
}

Indie::SoloScene::~SoloScene()
{
    std::vector<std::vector<std::string>> dataToWrite;

    for (auto key : this->playerKeys) {
        dataToWrite.push_back({ std::to_string((int)key.second), std::to_string((int)key.first) });
    }
    try {
        ServiceLocator::getInstance().get<CSVParser>().writeToFile("../ressources/.saves/keybinds.txt", dataToWrite);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

void Indie::SoloScene::init()
{
    // TODO : XP BAR
    // TODO : SCORE
    unsigned short int xp = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo()->xp;
    unsigned short int lvl = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo()->lvl;
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
    this->buttons.at(BUTTON_TYPE::SKIN)->init(context, "../ressources/images/solo/Perso.png", 1, 1, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::THEME)->init(context, "../ressources/images/solo/Theme.png", 1, 2, POS(0, 0));
    this->buttons.at(BUTTON_TYPE::MAP)->init(context, "../ressources/images/solo/Niveau.png", 1, 0, POS(0, 0));
    /* ================================================================== */
    // CHECKBOXES CREATE
    /* ================================================================== */
    pUps.reset(new Checkbox(context));
    pUps->setStatus(pUpsEnabled);
    /* ================================================================== */
    // CHECKBOXES INIT
    /* ================================================================== */
    pUps->init("../ressources/images/solo/Check.png", 1, 3, POS(0, 0));
    pUps->setStatus(pUpsEnabled);
    /* ================================================================== */
    // KEYBINDS INIT
    /* ================================================================== */
    this->keybinds.at(KEY_TYPE::UP)->init("../ressources/images/solo/KB_Up.png", 1, 4, POS(183, 468));
    this->keybinds.at(KEY_TYPE::DOWN)->init("../ressources/images/solo/KB_Down.png", 1, 5, POS(183, 547));
    this->keybinds.at(KEY_TYPE::LEFT)->init("../ressources/images/solo/KB_Left.png", 0, 5, POS(108, 547));
    this->keybinds.at(KEY_TYPE::RIGHT)->init("../ressources/images/solo/KB_Right.png", 2, 5, POS(261, 547));
    this->keybinds.at(KEY_TYPE::DROP)->init("../ressources/images/solo/KB_Bar.png", 3, 5, POS(456, 547));
    // Some inits :
    playerTexture = charaPaths[charaSelector.getPos().first].first;
    playerColor = charaPaths[charaSelector.getPos().first].second;
    mapPath = mapPaths[mapSelector.getPos().first];
    mapTheme = (themeSelector.getPos().first == 0) ? Components::THEME::DIRT : Components::THEME::STONE;
}

void Indie::SoloScene::reset()
{
    context.getSceneManager()->clear();
    selector.setPos(0, 0);
    init();
}

void Indie::SoloScene::getSavedKeybinds(void)
{
    try {
        std::vector<std::vector<std::string>> parsedData = ServiceLocator::getInstance().get<CSVParser>().parse("../ressources/.saves/keybinds.txt");

        if (parsedData.size() != 5)
            throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/keybinds.txt\" corrupted.");
        for (auto datas : parsedData) {
            if (datas.size() != 2)
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/keybinds.txt\" corrupted.");
            int keyType = std::stoi(datas.at(0));
            int keyNb = std::stoi(datas.at(1));

            if (keyType >= (int)KEY_TYPE::NONE || keyType < (int)KEY_TYPE::LEFT)
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/keybinds.txt\" corrupted.");
            if (std::find_if(Keybind::keyCodes.begin(), Keybind::keyCodes.end(), [keyNb](const auto &var) { return ((int)var.first == keyNb); })
                == Keybind::keyCodes.end())
                throw Indie::Exceptions::FileCorruptedException(ERROR_STR, "File \"../ressources/.saves/keybinds.txt\" corrupted.");
            this->keybinds.insert({ (Indie::Components::KEY_TYPE)keyType, std::make_unique<Keybind>(context, (irr::EKEY_CODE)keyNb) });
        }
    } catch (const std::exception &e) {
        this->resetKeybinds();
        std::cout << e.what() << std::endl;
    }
}

void Indie::SoloScene::update(irr::f32 ticks)
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
    // KEYBINDS SET USED
    /* ================================================================== */
    playerKeys.clear();
    playerKeys.push_back({ this->keybinds.at(KEY_TYPE::UP)->getKey(), Indie::Components::KEY_TYPE::UP });
    playerKeys.push_back({ this->keybinds.at(KEY_TYPE::DOWN)->getKey(), Indie::Components::KEY_TYPE::DOWN });
    playerKeys.push_back({ this->keybinds.at(KEY_TYPE::LEFT)->getKey(), Indie::Components::KEY_TYPE::LEFT });
    playerKeys.push_back({ this->keybinds.at(KEY_TYPE::RIGHT)->getKey(), Indie::Components::KEY_TYPE::RIGHT });
    playerKeys.push_back({ this->keybinds.at(KEY_TYPE::DROP)->getKey(), Indie::Components::KEY_TYPE::DROP });
    for (auto &keybind : this->keybinds) {
        keybind.second->setUsedKeys(this->playerKeys);
    }
    /* ================================================================== */
    // UPDATE KEYBINDS
    /* ================================================================== */
    for (auto &keybind : this->keybinds) {
        keybind.second->update(selector.getPos());
    }
    if (this->keybinds.at(KEY_TYPE::UP)->getStatus() || this->keybinds.at(KEY_TYPE::DOWN)->getStatus()
        || this->keybinds.at(KEY_TYPE::LEFT)->getStatus() || this->keybinds.at(KEY_TYPE::RIGHT)->getStatus()
        || this->keybinds.at(KEY_TYPE::DROP)->getStatus())
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
    this->buttons.at(BUTTON_TYPE::PLAY)->update(this->selector.getPos());
    this->buttons.at(BUTTON_TYPE::BACK)->update(this->selector.getPos());
    this->buttons.at(BUTTON_TYPE::SKIN)->update(this->selector.getPos());
    this->buttons.at(BUTTON_TYPE::THEME)->update(this->selector.getPos());
    this->buttons.at(BUTTON_TYPE::MAP)->update(this->selector.getPos());
    /* ================================================================== */
    // UPDATE CHECKBOXES
    /* ================================================================== */
    pUps->update(selector.getPos());
    pUpsEnabled = pUps->getStatus();
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
    /* ================================================================== */
    // CLICK BUTTONS
    /* ================================================================== */
    if (this->buttons.at(BUTTON_TYPE::PLAY)->getStatus() == Button::Status::Pressed
        || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_KEY_P) == true) {
        InitGame init;
        PlayerParams initPlayer;

        context.getSceneManager()->clear();
        init.mapPath = mapPath;
        init.mode = GameScene::MODE::SOLO;
        init.nbAi = 3;
        init.mapTheme = mapTheme;
        init.mapType = (mapSelector.getPos().first == 0)
            ? Components::MAP_TYPE::DEFAULT
            : ((mapSelector.getPos().first == 1) ? Components::MAP_TYPE::RANDOM : Components::MAP_TYPE::SAVED);
        init.powerUp = pUpsEnabled;
        init.timeLimit = 180;
        initPlayer.playerTexture = charaPaths[charaSelector.getPos().first].first;
        initPlayer.playerColor = charaPaths[charaSelector.getPos().first].second;
        for (auto &it : playerKeys) {
            initPlayer.playerKeys.insert(it);
        }
        init.playersParams = { initPlayer };
        ServiceLocator::getInstance().get<SceneManager>().getScene<GameScene>()->setInitGame(init);
        ServiceLocator::getInstance().get<SceneManager>().setScene<GameScene>(context);
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<IntroScene>();
        skipScene(false, false, true, true);
    }
    if (this->buttons.at(BUTTON_TYPE::BACK)->getStatus() == Button::Status::Pressed
        || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        context.getSceneManager()->clear();
        skipScene(true, true, true, true);
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<MainMenuScene>();
    }
    EventHandler::getInstance().resetKeys();
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
    /* ================================================================== */
    // DISPLAY BUTONS
    /* ================================================================== */
    for (auto const &button : this->buttons) {
        button.second->draw();
    }
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

    std::map<std::string, int>scores_map = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo()->scores_map;
    int mapScore = 0;
    for (auto score : scores_map) {
        if (score.first == mapPath) {
            mapScore = score.second;
            break;
        }
    }
    font->draw(mPath.c_str(), RECT(410 - (5 * int(mPath.size())), 139, 0, 0), {255, 255, 255, 255});
    font->draw(pName.c_str(), RECT(410 - (5 * int(pName.size())), 218, 0, 0), {255, 255, 255, 255});
    font->draw(tName.c_str(), RECT(410 - (5 * int(tName.size())), 300, 0, 0), {255, 255, 255, 255});
    font->draw(std::to_string(mapScore).c_str(), RECT(1000, 400, 0, 0), {255, 255, 255, 255});

    /* ================================================================== */
    // DISPLAY KEYBINDS
    /* ================================================================== */
    for (auto const &keybind : this->keybinds) {
        keybind.second->draw();
    }
    if (this->keybinds.at(KEY_TYPE::UP)->getStatus() || this->keybinds.at(KEY_TYPE::DOWN)->getStatus()
        || this->keybinds.at(KEY_TYPE::LEFT)->getStatus() || this->keybinds.at(KEY_TYPE::RIGHT)->getStatus()
        || this->keybinds.at(KEY_TYPE::DROP)->getStatus())
        context.displayImage(this->keybinds.at(KEY_TYPE::UP)->tick);
}

void Indie::SoloScene::resetKeybinds(void)
{
    this->keybinds.clear();
    this->keybinds.insert(
        { Indie::Components::KEY_TYPE::UP, std::make_unique<Keybind>(context, std::find_if(playerKeys.begin(), playerKeys.end(), [](const auto &var) {
             return (var.second == Indie::Components::KEY_TYPE::UP);
         })->first) });
    this->keybinds.insert({ Indie::Components::KEY_TYPE::DOWN,
        std::make_unique<Keybind>(context, std::find_if(playerKeys.begin(), playerKeys.end(), [](const auto &var) {
            return (var.second == Indie::Components::KEY_TYPE::DOWN);
        })->first) });
    this->keybinds.insert({ Indie::Components::KEY_TYPE::LEFT,
        std::make_unique<Keybind>(context, std::find_if(playerKeys.begin(), playerKeys.end(), [](const auto &var) {
            return (var.second == Indie::Components::KEY_TYPE::LEFT);
        })->first) });
    this->keybinds.insert({ Indie::Components::KEY_TYPE::RIGHT,
        std::make_unique<Keybind>(context, std::find_if(playerKeys.begin(), playerKeys.end(), [](const auto &var) {
            return (var.second == Indie::Components::KEY_TYPE::RIGHT);
        })->first) });
    this->keybinds.insert({ Indie::Components::KEY_TYPE::DROP,
        std::make_unique<Keybind>(context, std::find_if(playerKeys.begin(), playerKeys.end(), [](const auto &var) {
            return (var.second == Indie::Components::KEY_TYPE::DROP);
        })->first) });
}

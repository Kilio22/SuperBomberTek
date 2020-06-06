/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MultiKeybindsScene
*/

#include "MultiKeybindsScene.hpp"
#include "GameScene.hpp"
#include "InitGame.hpp"
#include "IntroScene.hpp"
#include "MultiScene.hpp"
#include "ServiceLocator.hpp"
#include "SoloScene.hpp"

void Indie::MultiKeybindsScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

Indie::MultiKeybindsScene::MultiKeybindsScene(Indie::ContextManager &context)
    : context(context)
    , selector(8, 6, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , p1CharaSelector(1, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , p2CharaSelector(1, 1, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , play(std::make_unique<Button>(context))
    , back(std::make_unique<Button>(context))
    , p1CharaButton(std::make_unique<Button>(context))
    , p2CharaButton(std::make_unique<Button>(context))
    , initGame(std::make_unique<InitGame>())
{
    p1CharaSelector.setSize(int(ServiceLocator::getInstance().get<SceneManager>().getScene<SoloScene>()->charaPaths.size()),
        1); // On set juste la size en plus petit pour pas qu'il ai accès à des perso mdr
    p2CharaSelector.setSize(int(ServiceLocator::getInstance().get<SceneManager>().getScene<SoloScene>()->charaPaths.size()),
        1); // On set juste la size en plus petit pour pas qu'il ai accès à des perso mdr
    title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi2/title.png");
    layout = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/multi2/Layout.png");
    font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    /* ================================================================== */
    // Keybinds p1
    /* ================================================================== */
    p1Keybinds.push_back(
        std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(Components::KEY_TYPE::UP, new Keybind(context, irr::EKEY_CODE::KEY_UP)));
    p1Keybinds.push_back(
        std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(Components::KEY_TYPE::DOWN, new Keybind(context, irr::EKEY_CODE::KEY_DOWN)));
    p1Keybinds.push_back(
        std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(Components::KEY_TYPE::LEFT, new Keybind(context, irr::EKEY_CODE::KEY_LEFT)));
    p1Keybinds.push_back(std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(
        Components::KEY_TYPE::RIGHT, new Keybind(context, irr::EKEY_CODE::KEY_RIGHT)));
    p1Keybinds.push_back(std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(
        Components::KEY_TYPE::DROP, new Keybind(context, irr::EKEY_CODE::KEY_KEY_M)));
    /* ================================================================== */
    // Keybinds p2
    /* ================================================================== */
    p2Keybinds.push_back(
        std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(Components::KEY_TYPE::UP, new Keybind(context, irr::EKEY_CODE::KEY_KEY_Z)));
    p2Keybinds.push_back(std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(
        Components::KEY_TYPE::DOWN, new Keybind(context, irr::EKEY_CODE::KEY_KEY_S)));
    p2Keybinds.push_back(std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(
        Components::KEY_TYPE::LEFT, new Keybind(context, irr::EKEY_CODE::KEY_KEY_Q)));
    p2Keybinds.push_back(std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(
        Components::KEY_TYPE::RIGHT, new Keybind(context, irr::EKEY_CODE::KEY_KEY_D)));
    p2Keybinds.push_back(std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>(
        Components::KEY_TYPE::DROP, new Keybind(context, irr::EKEY_CODE::KEY_KEY_F)));
}

Indie::MultiKeybindsScene::~MultiKeybindsScene() {}

void Indie::MultiKeybindsScene::setData(InitGame *initGame)
{
    this->initGame->mapPath.assign(initGame->mapPath);
    this->initGame->mapTheme = initGame->mapTheme;
    this->initGame->mapType = initGame->mapType;
    this->initGame->mode = initGame->mode;
    this->initGame->nbAi = initGame->nbAi;
    this->initGame->playersParams = initGame->playersParams;
    this->initGame->powerUp = initGame->powerUp;
    this->initGame->timeLimit = initGame->timeLimit;
}

void Indie::MultiKeybindsScene::init()
{
    /* ================================================================== */
    // Buttons
    /* ================================================================== */
    p1CharaButton->init(context, "../ressources/images/multi2/Perso1.png", 0, 2, POS(0, 0));
    p2CharaButton->init(context, "../ressources/images/multi2/Perso2.png", 0, 3, POS(0, 0));
    play->init(context, "../ressources/images/multi2/Jouer.png", 0, 4, POS(0, 0));
    back->init(context, "../ressources/images/multi2/Retour.png", 0, 5, POS(0, 0));
    /* ================================================================== */
    // Keybinds p1
    /* ================================================================== */
    std::find_if(p1Keybinds.begin(), p1Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::UP);
    })->second->init("../ressources/images/multi2/P1KB_up.png", 1, 0, POS(188, 206));
    std::find_if(p1Keybinds.begin(), p1Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::DOWN);
    })->second->init("../ressources/images/multi2/P1KB_down.png", 1, 1, POS(188, 286));
    std::find_if(p1Keybinds.begin(), p1Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::LEFT);
    })->second->init("../ressources/images/multi2/P1KB_left.png", 0, 1, POS(115, 286));
    std::find_if(p1Keybinds.begin(), p1Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::RIGHT);
    })->second->init("../ressources/images/multi2/P1KB_right.png", 2, 1, POS(264, 286));
    std::find_if(p1Keybinds.begin(), p1Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::DROP);
    })->second->init("../ressources/images/multi2/P1KB_bomb.png", 3, 1, POS(460, 286));
    /* ================================================================== */
    // Keybinds p2
    /* ================================================================== */
    std::find_if(p2Keybinds.begin(), p2Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::UP);
    })->second->init("../ressources/images/multi2/P2KB_up.png", 5, 0, POS(850, 206));
    std::find_if(p2Keybinds.begin(), p2Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::DOWN);
    })->second->init("../ressources/images/multi2/P2KB_down.png", 5, 1, POS(850, 286));
    std::find_if(p2Keybinds.begin(), p2Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::LEFT);
    })->second->init("../ressources/images/multi2/P2KB_left.png", 4, 1, POS(774, 286));
    std::find_if(p2Keybinds.begin(), p2Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::RIGHT);
    })->second->init("../ressources/images/multi2/P2KB_right.png", 6, 1, POS(924, 286));
    std::find_if(p2Keybinds.begin(), p2Keybinds.end(), [](const auto &var) {
        return (var.first == Indie::Components::KEY_TYPE::DROP);
    })->second->init("../ressources/images/multi2/P2KB_bomb.png", 7, 1, POS(1122, 286));
    pKeybinds.reserve(p1Keybinds.size() + p2Keybinds.size());
    pKeybinds.insert(pKeybinds.end(), p1Keybinds.begin(), p1Keybinds.end());
    pKeybinds.insert(pKeybinds.end(), p2Keybinds.begin(), p2Keybinds.end());
}

void Indie::MultiKeybindsScene::reset()
{
    selector.setPos(0, 0);
    init();
}

void Indie::MultiKeybindsScene::update(irr::f32 ticks)
{
    /* ================================================================== */
    // KEYBINDS UPDATE
    /* ================================================================== */
    bool wasKeyUpdated = false;
    for (auto &it : pKeybinds) {
        it.second->setUsedKeys(pKeybinds);
        it.second->update(selector.getPos());
        wasKeyUpdated = (it.second->getStatus()) ? true : wasKeyUpdated;
    }
    if (wasKeyUpdated)
        return;
    /* ================================================================== */
    // LAYOUT EDIT
    /* ================================================================== */
    selector.update();
    if (selector.getPos().second > 1 && selector.getPos().first != 0)
        selector.setPos(0, selector.getPos().second); // Cannot move right after keys;
    if (selector.getPos().second == 0) {
        if (selector.getPos().first == 0)
            selector.setPos(1, 0);
        if (selector.getPos().first == 2)
            selector.setPos(1, 0);
        if (selector.getPos().first == 3)
            selector.setPos(1, 0);
        if (selector.getPos().first == 4)
            selector.setPos(5, 0);
        if (selector.getPos().first == 6)
            selector.setPos(5, 0);
        if (selector.getPos().first == 7) // All of this is the first row btw.
            selector.setPos(5, 0); // To skip empty spaces & go back to the up key
    }
    /* ================================================================== */
    // BUTTONS UPDATE
    /* ================================================================== */
    play->update(selector.getPos());
    back->update(selector.getPos());
    p1CharaButton->update(selector.getPos());
    p2CharaButton->update(selector.getPos());
    /* ================================================================== */
    // CLICK BUTTONS
    /* ================================================================== */
    if (p1CharaButton->getStatus() == Button::Status::Selected)
        p1CharaSelector.update();
    if (p2CharaButton->getStatus() == Button::Status::Selected)
        p2CharaSelector.update();
    if (play->getStatus() == Button::Status::Pressed) {
        SceneManager &sceneManager = ServiceLocator::getInstance().get<SceneManager>();

        this->initGameStruct(sceneManager);
        sceneManager.setScene<GameScene>(context);
        sceneManager.setSubScene<IntroScene>();
        skipScene(false, false, true, true);
        EventHandler::getInstance().resetKeys();
    }
    if (back->getStatus() == Button::Status::Pressed || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE) == true) {
        context.getSceneManager()->clear();
        skipScene(true, true, true, true);
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<MultiScene>();
        EventHandler::getInstance().resetKeys();
    }
}

void Indie::MultiKeybindsScene::initGameStruct(SceneManager &sceneManager)
{
    PlayerParams p1Params;
    PlayerParams p2Params;

    p1Params.playerColor = sceneManager.getScene<SoloScene>()->charaPaths[p1CharaSelector.getPos().first].second;
    p1Params.playerTexture = sceneManager.getScene<SoloScene>()->charaPaths[p1CharaSelector.getPos().first].first;
    for (auto &i : p1Keybinds)
        p1Params.playerKeys.insert({ i.second->getKey(), i.first });
    p2Params.playerColor = sceneManager.getScene<SoloScene>()->charaPaths[p2CharaSelector.getPos().first].second;
    p2Params.playerTexture = sceneManager.getScene<SoloScene>()->charaPaths[p2CharaSelector.getPos().first].first;
    for (auto &i : p2Keybinds)
        p2Params.playerKeys.insert({ i.second->getKey(), i.first });
    this->initGame->mode = GameScene::MODE::MULTI;
    this->initGame->playersParams = {};
    this->initGame->playersParams.push_back({ p1Params });
    this->initGame->playersParams.push_back({ p2Params });
    sceneManager.getScene<GameScene>()->setInitGame(*this->initGame);
}

void Indie::MultiKeybindsScene::renderPre3D()
{
    /* ================================================================== */
    // DISPLAY IMAGES
    /* ================================================================== */
    context.displayImage(title);
    context.displayImage(layout);
}

void Indie::MultiKeybindsScene::renderPost3D()
{
    bool wasKeyUpdated = false;

    /* ================================================================== */
    // DISPLAY BUTONS
    /* ================================================================== */
    play->draw();
    back->draw();
    p1CharaButton->draw();
    p2CharaButton->draw();
    /* ================================================================== */
    // DISPLAY TEXTS
    /* ================================================================== */
    std::string p1Name
        = getFileName(ServiceLocator::getInstance().get<SceneManager>().getScene<SoloScene>()->charaPaths[p1CharaSelector.getPos().first].first);
    std::string p2Name
        = getFileName(ServiceLocator::getInstance().get<SceneManager>().getScene<SoloScene>()->charaPaths[p2CharaSelector.getPos().first].first);
    font->draw(p1Name.c_str(), RECT(450 - (5 * int(p1Name.size())), 462, 0, 0), { 255, 255, 255, 255 });
    font->draw(p2Name.c_str(), RECT(450 - (5 * int(p2Name.size())), 540, 0, 0), { 255, 255, 255, 255 });
    /* ================================================================== */
    // DISPLAY KEYBINDS
    /* ================================================================== */
    for (auto &it : pKeybinds)
        it.second->draw();
    for (auto &it : pKeybinds)
        wasKeyUpdated = (it.second->getStatus()) ? true : wasKeyUpdated;
    if (wasKeyUpdated)
        context.displayImage((pKeybinds.begin())->second->tick);
}

std::string Indie::MultiKeybindsScene::getFileName(std::string const &filepath)
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
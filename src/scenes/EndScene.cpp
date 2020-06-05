/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EndScene
*/

#include "EndScene.hpp"
#include "Scenes.hpp"
#include "IntroScene.hpp"
#include "MenuScene.hpp"
#include "MainMenuScene.hpp"
#include "ServiceLocator.hpp"

Indie::EndScene::EndScene(ContextManager &context)
    : context(context)
    , selector(1, 2, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , endGame(std::make_unique<Indie::EndGame>())
{}

void Indie::EndScene::init()
{
    this->title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/menu/title.png");
    this->menu.reset(new Button(context));
    this->restart.reset(new Button(context));

    this->font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");

    this->menu->init(context, "../ressources/images/solo/Play.png", 0, 0, POS(0,0));
    this->restart->init(context, "../ressources/images/solo/Retour.png", 0, 1, POS(0,0));
}

void Indie::EndScene::reset()
{
    selector.setPos(0, 0);
    init();
}

void Indie::EndScene::update(irr::f32 ticks)
{
    selector.update();
    this->menu->update(selector.getPos());
    this->restart->update(selector.getPos());

    if (this->menu->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
        skipScene(true, true, true, true);
    }
    if (this->restart->getStatus() == Button::Status::Pressed) {
        // ServiceLocator::getInstance().get<EntityManager>().reset();
        // Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::GameScene>()->reset();
        // Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(false);
        // Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
        // Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::IntroScene>();
        // Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(true);
        // Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(true);
        // Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<IntroScene>()->skipScene();
        // EventHandler::getInstance().resetKeys();
    }
    EventHandler::getInstance().resetKeysStatusOnce();
    EventHandler::getInstance().resetKeysStatus();
}

void Indie::EndScene::renderPre3D() {}

void Indie::EndScene::renderPost3D()
{
    this->menu->draw();
    this->restart->draw();
    context.displayImage(title);

    unsigned short int xp = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo()->xp;
    unsigned short int lvl = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo()->lvl;

    // if (this->endGame->matchPlay == MATCH_PLAY::WIN)
    //     font->draw("Gagné", RECT(800, 100, 0, 0), {255, 255, 255, 255});
    // else if (this->endGame->matchPlay == MATCH_PLAY::LOSE)
    //     font->draw("Perdu", RECT(800, 100, 0, 0), {255, 255, 255, 255});
    // else if (this->endGame->matchPlay == MATCH_PLAY::DRAW)
    //     font->draw("Egalité", RECT(800, 100, 0, 0), {255, 255, 255, 255});
    // else if (this->endGame->matchPlay == MATCH_PLAY::P1_WON)
    //     font->draw("Joueur 1 à gagné", RECT(800, 100, 0, 0), {255, 255, 255, 255});
    // else if (this->endGame->matchPlay == MATCH_PLAY::P2_WON)
    //     font->draw("Joueur 2 à gagné", RECT(800, 100, 0, 0), {255, 255, 255, 255});
    // else if (this->endGame->matchPlay == MATCH_PLAY::BOTH_LOSE)
    //     font->draw("Bande de naze", RECT(800, 100, 0, 0), {255, 255, 255, 255});

    for (size_t i = 0; i < this->endGame->scores.size(); i++)
        font->draw(this->endGame->scores.at(i).first.c_str(), RECT(400, 300 + ((int)i * 50), 0, 0), {255, 255, 255, 255});

    font->draw(std::to_string(lvl).c_str(), RECT(400, 500, 0, 0), {255, 255, 255, 255});
    font->draw(std::to_string(xp).c_str(), RECT(400, 600, 0, 0), {255, 255, 255, 255});
}

void Indie::EndScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

Indie::EndGame *Indie::EndScene::getEndGame(void) const
{
    return this->endGame.get();
}

void Indie::EndScene::setEndGame(const Indie::EndGame &endGame)
{
    this->endGame = std::make_unique<Indie::EndGame>(endGame);
}
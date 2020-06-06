/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EndScene
*/

#include "EndScene.hpp"
#include "Scenes.h"
#include "IntroScene.hpp"
#include "MainMenuScene.hpp"
#include "ServiceLocator.hpp"
#include "InitGame.hpp"

static float getPercentage(Indie::MasterInfo *info)
{
    int sumXp = 0;

    for (int i = 0; i < info->lvl + 1; i++)
        sumXp += i * 250;
    return (float(info->xp - sumXp) / float((info->lvl + 1) * 250)) * 100.f;
}

Indie::EndScene::EndScene(ContextManager &context)
    : context(context)
    , selector(1, 2, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{}

void Indie::EndScene::init()
{
    ServiceLocator::getInstance().get<MusicManager>().setMusic(0);
    this->title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/menu/title.png");
    this->menu.reset(new Button(context));
    this->restart.reset(new Button(context));
    this->font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    this->menu->init(context, "../ressources/images/solo/Play.png", 0, 0, POS(0,0));
    this->restart->init(context, "../ressources/images/solo/Retour.png", 0, 1, POS(0,0));
    if (this->endGame.xp != 0) {
        this->nbXpToSub = (float)this->endGame.xp / 102.f;
        ServiceLocator::getInstance().get<SoundManager>().playSound("xp_up");
    }
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
        ServiceLocator::getInstance().get<EntityManager>().reset();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setScene<Indie::MenuScene>(context);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
    }
    if (this->restart->getStatus() == Button::Status::Pressed) {
        ServiceLocator::getInstance().get<EntityManager>().reset();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::GameScene>()->reset();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(false);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::IntroScene>();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<IntroScene>()->skipScene();
        EventHandler::getInstance().resetKeys();
    }
}

void Indie::EndScene::renderPre3D() {}

void Indie::EndScene::renderPost3D()
{
    MasterInfo *info = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo();
    InitGame *gameInfo = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::GameScene>()->getInitGame();

    this->menu->draw();
    this->restart->draw();
    context.displayImage(title);
    unsigned int actualLevel = (unsigned int)floor(((1 + sqrt(1 + 8 * (int)info->xp / 250)) / 2) - 1);

    // if (this->endGame.matchPlay == MATCH_PLAY::WIN)
    //     font->draw("Gagne", RECT(800, 100, 0, 0), {255, 255, 255, 255});
    // else if (this->endGame.matchPlay == MATCH_PLAY::LOSE)
    //     font->draw("Perdu", RECT(800, 100, 0, 0), {255, 255, 255, 255});
    // else if (this->endGame.matchPlay == MATCH_PLAY::DRAW)
    //     font->draw("Egalite", RECT(800, 100, 0, 0), {255, 255, 255, 255});
    for (size_t i = 0; i < this->endGame.scores.size(); i++)
        font->draw(std::to_string(this->endGame.scores.at(i).second).c_str(), RECT(400, 300 + ((int)i * 50), 0, 0), {255, 255, 255, 255});

    // Save du HighScore
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->saveHighScoreMap(gameInfo->mapPath, this->endGame.scores.at(0).second);

    // Increase Xp
    this->increaseXp(info);

    // Level calculator
    info->lvl = (unsigned int)floor(((1 + sqrt(1 + 8 * (int)info->xp / 250)) / 2) - 1);

    std::cout << getPercentage(info) << std::endl;

    //play sound if player has level up
    if (actualLevel < info->lvl)
        ServiceLocator::getInstance().get<SoundManager>().playSound("level_up");

    font->draw("Xp", RECT(300, 600, 0, 0), {255, 255, 255, 255});
    font->draw(std::to_string(info->xp).c_str(), RECT(400, 600, 0, 0), {255, 255, 255, 255});
    font->draw("Level", RECT(300, 500, 0, 0), {255, 255, 255, 255});
    font->draw(std::to_string(info->lvl).c_str(), RECT(400, 500, 0, 0), {255, 255, 255, 255});

}

void Indie::EndScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(subRender);
}

const Indie::EndGame &Indie::EndScene::getEndGame(void) const
{
    return this->endGame;
}

void Indie::EndScene::setEndGame(const Indie::EndGame &endGame)
{
    this->endGame = endGame;
}

void Indie::EndScene::increaseXp(Indie::MasterInfo *info)
{
    if (this->endGame.xp != 0) {
        if (this->endGame.xp < (unsigned int)this->nbXpToSub) {
            info->xp += this->endGame.xp;
            this->endGame.xp = 0;
        }
        else {
            this->xpToAdd += this->nbXpToSub;
            if ((int)floor(this->xpToAdd) >= 1) {
                this->endGame.xp -= (int)floor(this->xpToAdd);
                info->xp += (int)floor(this->xpToAdd);
                this->xpToAdd = 0;
            }
        }
    }
}
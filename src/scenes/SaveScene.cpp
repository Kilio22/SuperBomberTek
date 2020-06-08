/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SaveScene
*/

#include "EntityManager.hpp"
#include "ImageLoader.hpp"
#include "SaveScene.hpp"
#include "ServiceLocator.hpp"
#include "SceneManager.hpp"
#include "SaveManager.hpp"
#include "Scenes.h"
#include <ctime>
#include <time.h>

Indie::SaveScene::SaveScene(ContextManager &context)
    : context(context)
    , selector(3, 3, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
{
}

void Indie::SaveScene::init()
{
    this->title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/save/title.png");
    this->font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");

    this->play.reset(new Button(context));
    this->save1.reset(new Button(context));
    this->save2.reset(new Button(context));
    this->save3.reset(new Button(context));
    this->prompt.reset(new Prompt(context));

    this->save1->init(context, "../ressources/images/save/Save1.png", 0, 0, POS(0,0), false);
    this->save2->init(context, "../ressources/images/save/Save2.png", 1, 0, POS(0,0), false);
    this->save3->init(context, "../ressources/images/save/Save3.png", 2, 0, POS(0,0), false);

    this->prompt->init("../ressources/images/save/TextBar.png", 1, 1, POS(460, 455));
    this->play->init(context, "../ressources/images/save/Jouer.png", 1, 2, POS(0, 0));
}

void Indie::SaveScene::reset()
{
    this->selector.setPos(0, 0);
    this->init();
}

void Indie::SaveScene::update(irr::f32 ticks)
{
    selector.update();
    if (selector.getPos().second >= 1)
        selector.setPos(1, selector.getPos().second);
    this->save1->update(selector.getPos());
    this->save2->update(selector.getPos());
    this->save3->update(selector.getPos());
    this->prompt->update(selector.getPos());
    this->play->update(selector.getPos());

    if (Indie::EventHandler::getInstance().isKeyPressed(irr::KEY_ESCAPE) == true) {
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
        skipScene(true, true, true, true);
        this->saveSelected = 0;
    }
    if (play->getStatus() == Button::Status::Pressed && this->prompt->getText().size() > 0) {
        ServiceLocator::getInstance().get<SaveManager>().loadSave("../ressources/.saves/" + this->prompt->getText() + ".txt");
        ServiceLocator::getInstance().get<SaveManager>().saveCurrentSave();
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
        skipScene(true, true, true, true);
        this->saveSelected = 0;
    }
    if (save1->getStatus() == Button::Status::Pressed)
        this->saveSelected = 1;
    if (save2->getStatus() == Button::Status::Pressed)
        this->saveSelected = 2;
    if (save3->getStatus() == Button::Status::Pressed)
        this->saveSelected = 3;
}

void Indie::SaveScene::renderPre3D() {}

void Indie::SaveScene::renderPost3D()
{
    std::unordered_map<std::string, std::time_t> savedGame = ServiceLocator::getInstance().get<Indie::SaveManager>().getSavedGame();
    int i = 0;

    if (this->saveSelected == 1)
        this->save1->setStatus(Button::Status::Selected);
    if (this->saveSelected == 2)
        this->save2->setStatus(Button::Status::Selected);
    if (this->saveSelected == 3)
        this->save3->setStatus(Button::Status::Selected);
    context.displayImage(title);
    this->save1->draw();
    this->save2->draw();
    this->save3->draw();
    this->play->draw();
    this->prompt->draw();

    for (const auto game : savedGame) {
        struct tm * timeinfo = localtime (&game.second);
        char time[80];
        strftime (time,80,"%d/%m/%Y %H:%M:%S",timeinfo);
        std::string timeString(time);

        font->draw(game.first.c_str(), RECT(120 + (i * 380), 190, 0, 0), {255, 255, 255, 255});
        font->draw(time, RECT(350 + (i * 380) - (9 * timeString.size()), 330, 0, 0), {255, 255, 255, 255});
        i++;
    }
    for (i; i < 3; i++) {
        font->draw("Vide", RECT(120 + (i * 380), 190, 0, 0), {255, 255, 255, 255});
        font->draw("N/A", RECT(350 + (i * 380) - 15, 330, 0, 0), {255, 255, 255, 255});
    }
}

void Indie::SaveScene::skipScene(bool update, bool render, bool subUpdate, bool subRender)
{
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneUpdateActive(update);
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneRenderActive(render);
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneUpdateActive(subUpdate);
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneRenderActive(subRender);
}
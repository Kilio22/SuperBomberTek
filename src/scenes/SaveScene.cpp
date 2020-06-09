/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SaveScene
*/

#define __STDC_WANT_LIB_EXT1__ 1
#define _XOPEN_SOURCE

#include "SaveScene.hpp"
#include "EntityManager.hpp"
#include "ImageLoader.hpp"
#include "ServiceLocator.hpp"
#include "SceneManager.hpp"
#include "SaveManager.hpp"
#include "Scenes.h"
#include <ctime>
#include <time.h>
#include <stdio.h>

Indie::SaveScene::SaveScene(ContextManager &context)
    : context(context)
    , selector(3, 3, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , play(std::make_unique<Button>(context))
    , prompt(std::make_unique<Prompt>(context))
{
    for (size_t buttonType = (size_t)SAVE_BUTTON_TYPE::SAVE1; buttonType < (size_t)SAVE_BUTTON_TYPE::NONE; buttonType++) {
        this->saveButtons.insert({(SAVE_BUTTON_TYPE)buttonType, std::make_unique<Button>(context)});
    }
}

void Indie::SaveScene::init()
{
    this->font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    this->title = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage("../ressources/images/save/title.png");
    this->saveButtons.at(SAVE_BUTTON_TYPE::SAVE1)->init(context, "../ressources/images/save/Save1.png", 0, 0, POS(0,0), false);
    this->saveButtons.at(SAVE_BUTTON_TYPE::SAVE2)->init(context, "../ressources/images/save/Save2.png", 1, 0, POS(0,0), false);
    this->saveButtons.at(SAVE_BUTTON_TYPE::SAVE3)->init(context, "../ressources/images/save/Save3.png", 2, 0, POS(0,0), false);
    this->prompt->init("../ressources/images/save/TextBar.png", 1, 1, POS(460, 455));
    this->play->init(context, "../ressources/images/save/Jouer.png", 1, 2, POS(0, 0));
    this->savedGame = ServiceLocator::getInstance().get<Indie::SaveManager>().getSavedGame();
}

void Indie::SaveScene::reset()
{
    this->selector.setPos(0, 0);
    this->init();
}

void Indie::SaveScene::update(irr::f32 ticks)
{
    std::string toDelete;

    selector.update();
    if (selector.getPos().second >= 1)
        selector.setPos(1, selector.getPos().second);
    this->saveButtons.at(SAVE_BUTTON_TYPE::SAVE1)->update(selector.getPos());
    this->saveButtons.at(SAVE_BUTTON_TYPE::SAVE2)->update(selector.getPos());
    this->saveButtons.at(SAVE_BUTTON_TYPE::SAVE3)->update(selector.getPos());
    this->prompt->update(selector.getPos());
    this->play->update(selector.getPos());

    if (Indie::EventHandler::getInstance().isKeyPressed(irr::KEY_ESCAPE) == true) {
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::TitleScene>();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSceneRenderActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneUpdateActive(true);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubSceneRenderActive(true);
        EventHandler::getInstance().resetKeys();
        skipScene(true, true, true, true);
        this->saveSelected = 0;
    }
    if (play->getStatus() == Button::Status::Pressed && this->prompt->getText().size() > 0 && this->saveSelected != 0) {
        ServiceLocator::getInstance().get<SaveManager>().loadSave("../ressources/.saves/" + this->prompt->getText() + ".supersave");
        ServiceLocator::getInstance().get<SaveManager>().saveCurrentSave();
        if ((int)this->savedGame.size() >= this->saveSelected && this->savedGame.at(this->saveSelected - 1).first != this->prompt->getText()) {
            toDelete = "../ressources/.saves/" + this->savedGame.at(this->saveSelected - 1).first + ".supersave";
            ServiceLocator::getInstance().get<SaveManager>().loadSave(toDelete);
            std::unordered_map<std::string, std::string> currentSave = ServiceLocator::getInstance().get<SaveManager>().getCurrentSave();
            ServiceLocator::getInstance().get<SaveManager>().loadSave("../ressources/.saves/" + this->prompt->getText() + ".supersave");
            ServiceLocator::getInstance().get<SaveManager>().setCurrentSave(currentSave);
            ServiceLocator::getInstance().get<SaveManager>().saveCurrentSave();
            std::remove(toDelete.c_str());
        }
        this->prompt->setText("");
        this->onUpdate();
        ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
        skipScene(true, true, true, true);
        this->saveSelected = 0;
    }
    if (EventHandler::getInstance().isKeyPressedAtOnce(irr::KEY_DELETE) && this->saveSelected != 0 && this->savedGame.size() > 0) {
        toDelete = "../ressources/.saves/" + this->savedGame.at(this->saveSelected - 1).first + ".supersave";
        this->saveSelected = 0;
        std::remove(toDelete.c_str());
        this->prompt->setText("");
        this->onUpdate();
    }

    for (size_t buttonType = (size_t)SAVE_BUTTON_TYPE::SAVE1; buttonType < (size_t)SAVE_BUTTON_TYPE::NONE; buttonType++) {
        if (this->saveButtons.at((SAVE_BUTTON_TYPE)buttonType)->getStatus() == Button::Status::Pressed) {
            this->saveSelected = buttonType + 1;
            if (this->savedGame.size() >= buttonType + 1)
                this->prompt->setText(this->savedGame.at(buttonType).first);
            else
                this->prompt->setText("");
        }
    }
}

void Indie::SaveScene::renderPre3D() {}

void Indie::SaveScene::renderPost3D()
{
    int i = 0;

    for (size_t buttonType = (size_t)SAVE_BUTTON_TYPE::SAVE1; buttonType < (size_t)SAVE_BUTTON_TYPE::NONE; buttonType++) {
        if (this->saveSelected == (int)(buttonType) + 1)
            this->saveButtons.at((SAVE_BUTTON_TYPE)buttonType)->setStatus(Button::Status::Selected);
    }
    context.displayImage(title);
    for (size_t buttonType = (size_t)SAVE_BUTTON_TYPE::SAVE1; buttonType < (size_t)SAVE_BUTTON_TYPE::NONE; buttonType++)
        this->saveButtons.at((SAVE_BUTTON_TYPE)buttonType)->draw();
    this->play->draw();
    this->prompt->draw();

    for (const auto game : this->savedGame) {
        struct tm * timeinfo = localtime(&game.second);
        char time[80];
        #ifdef __STDC_LIB_EXT1__
            localtime_s(&timeinfo, &game.second);
        #else
            timeinfo = localtime(&game.second);
        #endif
        (void)strftime(time, 80, "%d/%m/%Y %H:%M:%S", timeinfo);
        std::string timeString(time);
        font->draw(game.first.c_str(), RECT(120 + (i * 380), 190, 0, 0), {255, 255, 255, 255});
        font->draw(time, RECT(350 + (i * 380) - (9 * timeString.size()), 330, 0, 0), {255, 255, 255, 255});
        i++;
    }
    for (; i < 3; i++) {
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

void Indie::SaveScene::onUpdate()
{
    this->savedGame = ServiceLocator::getInstance().get<Indie::SaveManager>().getSavedGame();
}
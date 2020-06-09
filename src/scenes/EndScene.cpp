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
#include "ImageLoader.hpp"
#include "SceneManager.hpp"
#include "MusicManager.hpp"
#include "SoundManager.hpp"
#include <stdio.h>

const std::unordered_map<Indie::EndScene::UI_IMAGE_TYPE, std::string> Indie::EndScene::imagePaths
    = { {Indie::EndScene::UI_IMAGE_TYPE::BG, "../ressources/images/black_bg.png"},
        {Indie::EndScene::UI_IMAGE_TYPE::LAYOUT, "../ressources/images/end/Layout.png"},
        {Indie::EndScene::UI_IMAGE_TYPE::LVL_UP_PLAYER, "../ressources/images/end/lvlup.png"},
        {Indie::EndScene::UI_IMAGE_TYPE::LVL_UP_MAP, "../ressources/images/end/lvlup2.png"} };

Indie::EndScene::EndScene(ContextManager &context)
    : context(context)
    , selector(1, 2, irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT, irr::EKEY_CODE::KEY_RIGHT)
    , menu(std::make_unique<Button>(context))
    , restart(std::make_unique<Button>(context))
    , popUpDuration(0)
    , xpBar(context)
{
    for (size_t i = (size_t)UI_IMAGE_TYPE::BG; i < (size_t)UI_IMAGE_TYPE::NONE; i++) {
        images.insert({ (UI_IMAGE_TYPE)i, ServiceLocator::getInstance().get<ImageLoader>().getImage(imagePaths.at((UI_IMAGE_TYPE)i)) });
    }
    this->font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    if (this->font == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/Banschrift.xml\"");
    }
    this->fontBig = context.getGuiEnv()->getFont("../ressources/font/myfont2.xml");
    if (this->fontBig == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/myfont2.xml\"");
    }
    this->fontVeryBig = context.getGuiEnv()->getFont("../ressources/font/myfont3.xml");
    if (this->fontVeryBig == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/myfont3.xml\"");
    }
}

void Indie::EndScene::init()
{
    ServiceLocator::getInstance().get<MusicManager>().setMusic(0);

    xpBar.init("../ressources/images/Bar.png", 0, 100, 0);
    this->restart->init(context, "../ressources/images/end/Recommencer.png", 0, 0, POS(0,0));
    this->menu->init(context, "../ressources/images/end/Menu.png", 0, 1, POS(0,0));
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
    Indie::MasterInfo info = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo();
    selector.update();
    if (popUpDuration == 0) {
        this->menu->update(selector.getPos());
        this->restart->update(selector.getPos());
    }

    if (this->menu->getStatus() == Button::Status::Pressed && popUpDuration == 0) {
        ServiceLocator::getInstance().get<EntityManager>().reset();
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setScene<Indie::MenuScene>(context);
        Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().setSubScene<Indie::MainMenuScene>();
    }
    if (this->restart->getStatus() == Button::Status::Pressed && popUpDuration == 0) {
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
    popUpDuration = (popUpDuration > 0) ? (time_t)(popUpDuration - ticks) : (time_t)0;
    if (EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_RETURN)) {
        popUpDuration = 0;
        EventHandler::getInstance().resetKeys();
    }
    this->increaseXp(info);
    xpBar.setSize(0, MasterInfo::xp_level[info.lvl]);
    xpBar.setValue(info.xp);
    xpBar.setLevel(info.lvl);
    xpBar.update();
    if (info.xp >= MasterInfo::xp_level[info.lvl]) {
        ServiceLocator::getInstance().get<SoundManager>().playSound("level_up");
        popUpDuration = 200;
        lvlUpType = (info.lvl % 2 == 0) ? UI_IMAGE_TYPE::LVL_UP_MAP : UI_IMAGE_TYPE::LVL_UP_PLAYER;
        info.xp -= MasterInfo::xp_level[info.lvl];
        info.lvl++;
    }
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->setMasterInfo(info);

}

void Indie::EndScene::renderPre3D()
{}

void Indie::EndScene::renderPost3D()
{
    MasterInfo info;
    InitGame *gameInfo = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::GameScene>()->getInitGame();

    context.displayImage(images.at(UI_IMAGE_TYPE::BG));
    context.displayImage(images.at(UI_IMAGE_TYPE::LAYOUT));
    fontVeryBig->draw(this->endText, RECT(154, 107, 0, 0), {255, 255, 255, 255});
    this->menu->draw();
    this->restart->draw();
    unsigned int actualLevel = 0;
    for (size_t i = 0; i < this->endGame.scores.size(); i++)
        fontBig->draw((this->endGame.scores.at(i).first + "  :  " + std::to_string(this->endGame.scores.at(i).second)).c_str(), RECT(150, 400 + ((int)i * 50), 0, 0), {255, 255, 255, 255});
    Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->saveHighScoreMap(gameInfo->mapPath, this->endGame.scores.at(0).second);
    info = Indie::ServiceLocator::getInstance().get<Indie::SceneManager>().getScene<Indie::MenuScene>()->getMasterInfo();
    xpBar.draw(POS(50, 600));
    if (popUpDuration > 0)
        context.displayImage(images.at(lvlUpType));
}

const Indie::EndGame &Indie::EndScene::getEndGame(void) const
{
    return this->endGame;
}

void Indie::EndScene::setEndGame(const Indie::EndGame &endGame)
{
    this->endGame = endGame;

    mode = (this->endGame.scores.size() == 1) ? GAME_MODE::SOLO : GAME_MODE::MULTI;
    if (mode == GAME_MODE::SOLO) {
        if (this->endGame.matchPlay == Indie::MATCH_PLAY::WIN)
            swprintf(endText, 100, L"Tu as gagn\u00E9 !");
        else
            swprintf(endText, 100, L"Tu as perdu...");
    } else {
        if (this->endGame.matchPlay == Indie::MATCH_PLAY::DRAW)
            swprintf(endText, 100, L"Egalit\u00E9 !");
        else if (this->endGame.matchPlay == Indie::MATCH_PLAY::LOSE)
            swprintf(endText, 100, L"Vous avez perdu...");
        else {
            #ifdef WIN32
                const size_t cSize = strlen(this->endGame.scores[0].first.c_str())+1;
                wchar_t *wc = new wchar_t[cSize];
                mbstowcs_s(NULL, wc, cSize, this->endGame.scores[0].first.c_str(), cSize - 1);
                swprintf(endText, 100,  L"%s a gagn\u00E9 !", wc);
                delete[] wc;
            #else
                swprintf(endText, 100,  L"%s a gagn\u00E9 !", this->endGame.scores[0].first.c_str());
            #endif // WIN32
        }
    }
}

void Indie::EndScene::setPlayerNames(const std::vector<std::string> &names)
{
    playerNames.clear();
    for (const auto &it : names)
        playerNames.push_back(it);
}

void Indie::EndScene::increaseXp(Indie::MasterInfo &info)
{
    // c'est de la magie noir ce truc je sais pas comment le changer
    if (this->endGame.xp != 0) {
        if (this->endGame.xp < (unsigned int)this->nbXpToSub) {
            info.xp += this->endGame.xp;
            this->endGame.xp = 0;
        }
        else {
            this->xpToAdd += this->nbXpToSub;
            if ((int)floor(this->xpToAdd) >= 1) {
                this->endGame.xp -= (int)floor(this->xpToAdd);
                info.xp += (int)floor(this->xpToAdd);
                this->xpToAdd = 0;
            }
        }
    }
}
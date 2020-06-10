/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CreditScene
*/

#include "CreditScene.hpp"
#include "ServiceLocator.hpp"
#include "MainMenuScene.hpp"
#include "EventHandler.hpp"
#include "Exceptions.h"
#include "SceneManager.hpp"
#include "SoundManager.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

const std::vector<std::pair<irr::core::stringw, Indie::CreditScene::TEXT_SIZE>> Indie::CreditScene::lines =
    { // on peut decommenter toutes les lignes pour plus espacer.
        {L"CREDITS", Indie::CreditScene::TEXT_SIZE::BIG},
        {L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Directors", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Ghassane SEBA\u00CF", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Guilian GANSTER", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Nathan LECORCHET", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Thomas BASTIEN", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Zylian ZALAN", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Programmers", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Ghassane SEBA\u00CF", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Guilian GANSTER", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Nathan LECORCHET", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Thomas BASTIEN", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Zylian ZALAN", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"AI Programmer", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Thomas BASTIEN", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"ECS Programmers", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Zylian ZALAN", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Nathan LECORCHET", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Thomas BASTIEN", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Sound Programmers", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Ghassane SEBA\u00CF", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Nathan LECORCHET", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Graphic Designer", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Ghassane SEBA\u00CF", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"UI Design", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Ghassane SEBA\u00CF", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Nathan LECORCHET", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Zylian ZALAN", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Save System Programmers", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Thomas BASTIEN", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Zylian ZALAN", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Sound Design", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Ghassane SEBA\u00CF", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Music By", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Ghassane SEBA\u00CF - Remix", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Jun CHIKUMA - Original Composer", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Tomoyuki HAMADA - Original Composer", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Lead Artist", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Ghassane SEBA\u00CF", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Inspired By", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Neo Bomberman", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Super Bomberman", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Super Bomberman R", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Special Thanks To", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Jean-Pierre PERNAUT", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Le Pas-de-Calais", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"L\u00E9o de la chaine Techmakers", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Nicolas CAGE", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Shreksophone", Indie::CreditScene::TEXT_SIZE::SMALL},
        {L"Stackov ERFLOW", Indie::CreditScene::TEXT_SIZE::SMALL},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        //{L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"", Indie::CreditScene::TEXT_SIZE::MEDIUM},
        {L"Merci d'avoir jou\u00E9", Indie::CreditScene::TEXT_SIZE::BIG}
    };


Indie::CreditScene::CreditScene(ContextManager &context)
    : context(context)
    , speed(80)
    , pos(720.f)
{
    this->fonts[0] = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    if (this->fonts[0] == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/Banschrift.xml\"");
    }
    this->fonts[1] = context.getGuiEnv()->getFont("../ressources/font/myfont2.xml");
    if (this->fonts[1] == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/myfont2.xml\"");
    }
    this->fonts[2] = context.getGuiEnv()->getFont("../ressources/font/myfont3.xml");
    if (this->fonts[2] == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/myfont3.xml\"");
    }
}

void Indie::CreditScene::init()
{
    int offset = 0;
    for (const auto &it : CreditScene::lines) {
        irr::gui::IGUIStaticText *tmp = context.getGuiEnv()->addStaticText(it.first.c_str(), irr::core::rect<irr::s32>(0, 0, 1280, 720), false, false, 0, -1, false);
        irr::s32 tmpX = tmp->getTextWidth();
        irr::s32 tmpY = tmp->getTextHeight();
        tmp->setRelativePosition(POS(0, (int)(tmpY + offset + pos)));
        tmp->setTextAlignment(irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER, irr::gui::EGUI_ALIGNMENT::EGUIA_UPPERLEFT);
        tmp->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
        tmp->enableOverrideColor(true);
        tmp->setOverrideFont(fonts[(int)it.second]);
        texts.push_back({tmp, (float)(tmpY + offset)});
        offset += (int)(tmpY * 7.5);
    }

}

void Indie::CreditScene::reset()
{
    context.getGuiEnv()->clear();
    texts.clear();
    pos = 700.f;
    init();
}

void Indie::CreditScene::update(irr::f32 ticks)
{
    if (EventHandler::getInstance().isAnyKeyPressed())
        pos -= (float)(speed * ticks * 10);
    else
        pos -= (float)(speed * ticks);
    if (EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_ESCAPE)) {
        ServiceLocator::getInstance().get<SceneManager>().setSceneUpdateActive(true);
        ServiceLocator::getInstance().get<SceneManager>().setSceneRenderActive(true);
        ServiceLocator::getInstance().get<SceneManager>().setSubSceneUpdateActive(true);
        ServiceLocator::getInstance().get<SceneManager>().setSubSceneRenderActive(true);
        ServiceLocator::getInstance().get<SoundManager>().playSound("menu_back");
        ServiceLocator::getInstance().get<SceneManager>().setSubScene<MainMenuScene>();
        context.getGuiEnv()->clear();
        return;
    }
    for (const auto &it : texts) {
        irr::s32 tmpX = it.first->getRelativePosition().UpperLeftCorner.X;
        irr::s32 tmpXNew = irr::s32(100 * (cos(int((it.second + pos) / 80))));
        // pour pas que ça bouge faut juste filer tmpX en premier arg au lieu de tmpXNew.
        it.first->setRelativePosition(POS(tmpXNew, irr::s32(it.second + pos)));
    }
}

void Indie::CreditScene::renderPre3D()
{}

void Indie::CreditScene::renderPost3D()
{}
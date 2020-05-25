/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuScene
*/

#include "MenuScene.hpp"
#include "ServiceLocator.hpp"

const std::string Indie::MenuScene::filepaths[5] = {
    "../ressources/images/bg_boxes.png",
    "../ressources/images/clouds.png",
    "../ressources/images/mountains.png",
    "../ressources/images/trees.png",
    "../ressources/images/ground.png"
};

const irr::core::vector2df Indie::MenuScene::velocities[5] = {
    irr::core::vector2df((irr::f32)0.005, (irr::f32)0.005),
    irr::core::vector2df((irr::f32)0.010, (irr::f32)0.000),
    irr::core::vector2df((irr::f32)0.020, (irr::f32)0.000),
    irr::core::vector2df((irr::f32)0.030, (irr::f32)0.000),
    irr::core::vector2df((irr::f32)0.040, (irr::f32)0.000)
};

Indie::MenuScene::MenuScene(ContextManager &context)
    : context(context)
{}

void Indie::MenuScene::setColor(irr::video::SColor color)
{
    for (size_t i = 0; i < parallax.size(); i++)
        parallax[i].setColor(color);
}

void Indie::MenuScene::init()
{
    Indie::ServiceLocator::getInstance().get<Indie::MusicManager>().setMusic(0);

    for (size_t i = 0; i < 5; i++) {
        Parallax tmp;
        tmp.init(this->context, this->filepaths[i], POS(1280, 720), this->velocities[i]);
        this->parallax.push_back(tmp);
    }
}

void Indie::MenuScene::reset()
{
    parallax.clear();
    init();
}

void Indie::MenuScene::update(irr::f32 ticks)
{
    for (size_t i = 0; i < parallax.size(); i++)
        parallax[i].update(ticks);
}

void Indie::MenuScene::renderPre3D()
{
    for (size_t i = 0; i < parallax.size(); i++)
        parallax[i].draw(context);
}

void Indie::MenuScene::renderPost3D() {}
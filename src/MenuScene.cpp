/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuScene
*/

#include "Scenes/MenuScene.hpp"

const irr::io::path filepaths[5] {
    "../ressources/images/bg_boxes.png",
    "../ressources/images/clouds.png",
    "../ressources/images/mountains.png",
    "../ressources/images/trees.png",
    "../ressources/images/ground.png"
};

const irr::core::position2d<float> velocities[5] {
    irr::core::position2d<float>(0.005, 0.005),
    irr::core::position2d<float>(0.010, 0.000),
    irr::core::position2d<float>(0.020, 0.000),
    irr::core::position2d<float>(0.030, 0.000),
    irr::core::position2d<float>(0.040, 0.000)
};

bool MenuScene::init(ContextManager &_context)
{
    MusicManager::setMusic(0);
    for (size_t i = 0; i < 5; i++) {
        Parallax tmp;
        if (!tmp.init(_context, filepaths[i], POS(1280, 720), velocities[i]))
            return (false);
        parallax.push_back(tmp);
    }
    this->context = &_context;
    return (true);
}

bool MenuScene::reset(ContextManager &_context)
{
    parallax.clear();
    return (init(_context));
}

void MenuScene::update()
{
    for (size_t i = 0; i < parallax.size(); i++)
        parallax[i].update();
}

void MenuScene::renderPre3D()
{
    for (size_t i = 0; i < parallax.size(); i++)
        parallax[i].draw(*context);
}

void MenuScene::renderPost3D() {}
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuScene
*/

#ifndef MENUSCENE_HPP_
#define MENUSCENE_HPP_

#include <iostream>
#include <vector>

#include "IScene.hpp"
#include "Parallax.hpp"
#include "ContextManager.hpp"

class MenuScene : public IScene {
    public:
        MenuScene() {}
        ~MenuScene() {}

        bool init(ContextManager &context);
        bool reset(ContextManager &context);
        void update();
        void renderPre3D();
        void renderPost3D();

    private:
        ContextManager *context;
        std::vector<Parallax> parallax;
};

#endif /* !MENUSCENE_HPP_ */
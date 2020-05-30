/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Button
*/

#include "Button.hpp"

Indie::Button::Button(ContextManager &context) : context(context)
{
    posX = 0;
    posY = 0;
    status = Status::Idle;
    keyPressed = false;
}

Indie::Button::~Button()
{
    if (idle)
        context.getDriver()->removeTexture(idle);
    if (selected)
        context.getDriver()->removeTexture(selected);
    if (pressed)
        context.getDriver()->removeTexture(pressed);
}

void Indie::Button::init(Indie::ContextManager &context, const std::string &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos)
{
    std::string extension = filepath.substr(filepath.find_last_of("."));
    std::string fp = filepath;
    fp.resize(fp.size() - extension.size());

    this->context = context;
    this->pos = pos;
    this->posX = posX;
    this->posY = posY;
    idle = context.getDriver()->getTexture(std::string(fp + "_idle" + extension).c_str());
    selected = context.getDriver()->getTexture(std::string(fp + "_selected" + extension).c_str());
    pressed = context.getDriver()->getTexture(std::string(fp + "_pressed" + extension).c_str());
    if (idle == nullptr || selected == nullptr || pressed == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + fp + "\" not found.");
    }
}

void Indie::Button::update(std::pair<int, int> pos)
{
    if (this->posX == pos.first && this->posY == pos.second)
        status = Status::Selected;
    else
        status = Status::Idle;
    if (status == Status::Selected && keyPressed && !EventHandler::getInstance().isKeyPressed(SELECTBUTTON))
        status = Status::Pressed;
    keyPressed = EventHandler::getInstance().isKeyPressed(SELECTBUTTON);
}

void Indie::Button::draw()
{
    if (status == Status::Idle)
        this->context.displayImage(idle, pos);
    else if (status == Status::Selected && keyPressed)
        this->context.displayImage(pressed, pos);
    else
        this->context.displayImage(selected, pos);
}

Indie::Button::Status Indie::Button::getStatus() const
{
    return status;
}
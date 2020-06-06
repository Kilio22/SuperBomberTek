/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Button
*/

#include "Button.hpp"
#include "ServiceLocator.hpp"

Indie::Button::Button(ContextManager &context) : playSounds(true), context(context)
{
    posX = 0;
    posY = 0;
    status = Status::Idle;
    keyPressed = false;
}

Indie::Button::Button(ContextManager &context, bool sounds) : playSounds(sounds), context(context)
{
    posX = 0;
    posY = 0;
    status = Status::Idle;
    keyPressed = false;
}

Indie::Button::~Button()
{}

void Indie::Button::init(Indie::ContextManager &context, const std::string &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos)
{
    std::string extension = filepath.substr(filepath.find_last_of("."));
    std::string fp = filepath;
    fp.resize(fp.size() - extension.size());

    this->context = context;
    this->pos = pos;
    this->posX = posX;
    this->posY = posY;
    idle = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(std::string(fp + "_idle" + extension).c_str());
    selected = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(std::string(fp + "_selected" + extension).c_str());
    pressed = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(std::string(fp + "_pressed" + extension).c_str());
}

void Indie::Button::init(Indie::ContextManager &context, const std::string &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos, bool sound)
{
    std::string extension = filepath.substr(filepath.find_last_of("."));
    std::string fp = filepath;
    fp.resize(fp.size() - extension.size());

    this->context = context;
    this->pos = pos;
    this->posX = posX;
    this->posY = posY;
    idle = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(std::string(fp + "_idle" + extension).c_str());
    selected = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(std::string(fp + "_selected" + extension).c_str());
    pressed = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(std::string(fp + "_pressed" + extension).c_str());
    this->playSounds = sound;
}

void Indie::Button::update(std::pair<int, int> pos)
{
    if (this->posX == pos.first && this->posY == pos.second)
        status = Status::Selected;
    else
        status = Status::Idle;
    if (!keyPressed && EventHandler::getInstance().isKeyPressedAtOnce(SELECTBUTTON) && playSounds)
        ServiceLocator::getInstance().get<SoundManager>().playSound("menu_select");
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

void Indie::Button::setStatus(Status status)
{
    this->status = status;
}
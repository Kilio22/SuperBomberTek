/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Checkbox
*/

#include "Checkbox.hpp"

Indie::Checkbox::Checkbox(Indie::ContextManager &context) : context(context), status(false), button(context), pos(POS(0, 0))
{}

Indie::Checkbox::~Checkbox()
{
    if (tick)
    context.getDriver()->removeTexture(tick);
}

void Indie::Checkbox::init(std::string const &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos)
{
    std::string extension = filepath.substr(filepath.find_last_of("."));
    std::string strippedFilepath;
    std::copy(filepath.c_str(), filepath.c_str() + filepath.size() - extension.size(), std::back_inserter(strippedFilepath));

    this->pos = pos;
    tick = context.getDriver()->getTexture(std::string(strippedFilepath + "_tick" + extension).c_str());
    if (tick == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + strippedFilepath + "\" not found.");
    }
    button.init(context, strippedFilepath + extension, posX, posY, pos);
}

void Indie::Checkbox::update(std::pair<int, int> pos)
{
    if (button.getStatus() == Button::Status::Pressed)
        status = !status;
    button.update(pos);
}

void Indie::Checkbox::draw()
{
    button.draw();
    if (status)
        this->context.displayImage(tick, pos);
}

bool Indie::Checkbox::getStatus() const
{
    return status;
}

void Indie::Checkbox::setStatus(bool status)
{
    this->status = status;
}
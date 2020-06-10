/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bar
*/

#include "Bar.hpp"
#include "ServiceLocator.hpp"
#include "ImageLoader.hpp"
#include "Exceptions.h"
#include "time.h"

Indie::Bar::Bar(ContextManager &context)
    : context(context)
    , min(0)
    , max(100)
    , value(0)
    , percentage(0)
    , level(0)
{
    this->font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    if (this->font == nullptr) {
        throw Indie::Exceptions::FileNotFoundException(ERROR_STR, "Cannot open file: \"../ressources/font/Banschrift.xml\"");
    }
}

void Indie::Bar::init(const std::string &filepath, int min, int max, int current)
{
    std::string extension = filepath.substr(filepath.find_last_of("."));
    std::string fp = filepath;
    fp.resize(fp.size() - extension.size());

    this->min = min;
    this->max = max;
    this->value = current;

    this->layout = ServiceLocator::getInstance().get<ImageLoader>().getImage(fp + "_layout" + extension.c_str());
    this->empty = ServiceLocator::getInstance().get<ImageLoader>().getImage(fp + "_empty" + extension.c_str());
    this->full = ServiceLocator::getInstance().get<ImageLoader>().getImage(fp + "_full" + extension.c_str());
    this->percentage = ((current - min) * 100) / (max - min);
}

void Indie::Bar::update()
{
    this->percentage = ((this->value - this->min) * 100) / (this->max - this->min);
}

void Indie::Bar::setSize(int min, int max)
{
    this->min = min;
    this->max = max;
}

void Indie::Bar::setLevel(int level)
{
    this->level = level;
}

void Indie::Bar::setValue(int value)
{
    this->value = value;
}

void Indie::Bar::draw(irr::core::position2d<irr::s32> pos) const
{
    std::string lvlText = std::to_string(this->level);
    std::string percentageText;
    
    if ((time(NULL) / 4) % 2 == 0)
        percentageText = std::to_string(this->percentage) + "%";
    else
        percentageText = std::to_string(this->value) + "/" + std::to_string(this->max);

    context.displayImage(this->empty, pos);
    context.displayImage(this->full, RECT(0, 0, (325 * this->percentage / 100) + 175, 63) ,pos);
    context.displayImage(this->layout, pos);
    font->draw(lvlText.c_str(), RECT(115 - (5 * (int)lvlText.size()) + pos.X, 15 + pos.Y, 0, 0), {255, 255, 255, 255});
    font->draw(percentageText.c_str(), RECT(333 - (5 * (int)percentageText.size()) + pos.X, 15 + pos.Y, 0, 0), {255, 255, 255, 255});
}
// text pos 114 19
// % pos 333 19
// Edit : je sais pas compter
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Prompt
*/

#include "Prompt.hpp"
#include "EventHandler.hpp"
#include "iostream"

const std::vector<std::pair<irr::EKEY_CODE, std::string>> Indie::Prompt::keyCodesMaj = {
    {irr::EKEY_CODE::KEY_KEY_A, "A"},
    {irr::EKEY_CODE::KEY_KEY_B, "B"},
    {irr::EKEY_CODE::KEY_KEY_C, "C"},
    {irr::EKEY_CODE::KEY_KEY_D, "D"},
    {irr::EKEY_CODE::KEY_KEY_E, "E"},
    {irr::EKEY_CODE::KEY_KEY_F, "F"},
    {irr::EKEY_CODE::KEY_KEY_G, "G"},
    {irr::EKEY_CODE::KEY_KEY_H, "H"},
    {irr::EKEY_CODE::KEY_KEY_I, "I"},
    {irr::EKEY_CODE::KEY_KEY_J, "J"},
    {irr::EKEY_CODE::KEY_KEY_K, "K"},
    {irr::EKEY_CODE::KEY_KEY_L, "L"},
    {irr::EKEY_CODE::KEY_KEY_M, "M"},
    {irr::EKEY_CODE::KEY_KEY_N, "N"},
    {irr::EKEY_CODE::KEY_KEY_O, "O"},
    {irr::EKEY_CODE::KEY_KEY_P, "P"},
    {irr::EKEY_CODE::KEY_KEY_Q, "Q"},
    {irr::EKEY_CODE::KEY_KEY_R, "R"},
    {irr::EKEY_CODE::KEY_KEY_S, "S"},
    {irr::EKEY_CODE::KEY_KEY_T, "T"},
    {irr::EKEY_CODE::KEY_KEY_U, "U"},
    {irr::EKEY_CODE::KEY_KEY_V, "V"},
    {irr::EKEY_CODE::KEY_KEY_W, "W"},
    {irr::EKEY_CODE::KEY_KEY_X, "X"},
    {irr::EKEY_CODE::KEY_KEY_Y, "Y"},
    {irr::EKEY_CODE::KEY_KEY_Z, "Z"},
};

const std::vector<std::pair<irr::EKEY_CODE, std::string>> Indie::Prompt::keyCodes = {
    {irr::EKEY_CODE::KEY_KEY_A, "a"},
    {irr::EKEY_CODE::KEY_KEY_B, "b"},
    {irr::EKEY_CODE::KEY_KEY_C, "c"},
    {irr::EKEY_CODE::KEY_KEY_D, "d"},
    {irr::EKEY_CODE::KEY_KEY_E, "e"},
    {irr::EKEY_CODE::KEY_KEY_F, "f"},
    {irr::EKEY_CODE::KEY_KEY_G, "g"},
    {irr::EKEY_CODE::KEY_KEY_H, "h"},
    {irr::EKEY_CODE::KEY_KEY_I, "i"},
    {irr::EKEY_CODE::KEY_KEY_J, "j"},
    {irr::EKEY_CODE::KEY_KEY_K, "k"},
    {irr::EKEY_CODE::KEY_KEY_L, "l"},
    {irr::EKEY_CODE::KEY_KEY_M, "m"},
    {irr::EKEY_CODE::KEY_KEY_N, "n"},
    {irr::EKEY_CODE::KEY_KEY_O, "o"},
    {irr::EKEY_CODE::KEY_KEY_P, "p"},
    {irr::EKEY_CODE::KEY_KEY_Q, "q"},
    {irr::EKEY_CODE::KEY_KEY_R, "r"},
    {irr::EKEY_CODE::KEY_KEY_S, "s"},
    {irr::EKEY_CODE::KEY_KEY_T, "t"},
    {irr::EKEY_CODE::KEY_KEY_U, "u"},
    {irr::EKEY_CODE::KEY_KEY_V, "v"},
    {irr::EKEY_CODE::KEY_KEY_W, "w"},
    {irr::EKEY_CODE::KEY_KEY_X, "x"},
    {irr::EKEY_CODE::KEY_KEY_Y, "y"},
    {irr::EKEY_CODE::KEY_KEY_Z, "z"},
    {irr::EKEY_CODE::KEY_SPACE, "_"},
    {irr::EKEY_CODE::KEY_BACK, ""},

};

Indie::Prompt::Prompt(ContextManager &context)
    : context(context)
    , button(context)
{}


void Indie::Prompt::init(std::string const &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos)
{
    std::string extension = filepath.substr(filepath.find_last_of("."));
    std::string strippedFilepath;
    std::copy(filepath.c_str(), filepath.c_str() + filepath.size() - extension.size(), std::back_inserter(strippedFilepath));

    font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    this->pos = pos;
    button.init(context, strippedFilepath + extension, posX, posY, POS(0, 0));
}

void Indie::Prompt::update(std::pair<int, int> pos)
{
    button.update(pos);
    if ((pos.first == 1 && pos.second == 1) && EventHandler::getInstance().isAnyKeyPressedAtOnce()) {
        for (auto it : keyCodes) {
            if (EventHandler::getInstance().isKeyPressedAtOnce(it.first)) {
                if (it.first == irr::EKEY_CODE::KEY_BACK && (text.size() >= 1))
                    text = text.erase(text.size() - 1);
                else if (text.size() <= 20) {
                    if (EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_LSHIFT) || EventHandler::getInstance().isKeyPressed(irr::EKEY_CODE::KEY_RSHIFT)) {
                    for (auto itMaj : keyCodesMaj) {
                        if (EventHandler::getInstance().isKeyPressedAtOnce(itMaj.first))
                            text = text + itMaj.second;
                        }
                    }
                    else
                        text = text + it.second;
                }
            }
        }
    }
}

void Indie::Prompt::draw()
{
    button.draw();
    this->font->draw(irr::core::stringw(text.c_str()), RECT(this->pos.X, this->pos.Y, 0, 0), irr::video::SColor(255, 255, 255, 255));
}

std::string Indie::Prompt::getText(void) const
{
    return this->text;
}

void Indie::Prompt::setText(std::string newText)
{
    this->text = newText;
}
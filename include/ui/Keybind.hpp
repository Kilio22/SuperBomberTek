/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Keybind
*/

#ifndef KEYBIND_HPP_
#define KEYBIND_HPP_

#include "Button.hpp"
#include "Components.h"
#include "ContextManager.hpp"
#include "EventHandler.hpp"
#include "Exceptions.h"
#include <irrlicht.h>
#include <string>
#include <utility>
#include <vector>

namespace Indie
{
    class Keybind
    {
    public:
        Keybind(ContextManager &context, irr::EKEY_CODE key);
        ~Keybind() = default;

        void init(std::string const &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos);
        void update(std::pair<int, int>);
        void draw();
        bool getStatus() const;
        irr::EKEY_CODE getKey() const;
        void setStatus(bool status);
        void setUsedKeys(std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>>& list);
        void setUsedKeys(std::vector<std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>>& list);

        static const std::vector<std::pair<irr::EKEY_CODE, irr::core::stringw>> keyCodes;
        Image *tick;

    protected:
    private:
        ContextManager &context;
        bool status;
        Button button;
        irr::core::position2d<irr::s32> pos;
        irr::EKEY_CODE key;
        irr::gui::IGUIFont *font;
        std::vector<irr::EKEY_CODE> usedKeys;
    };
}

#endif /* !KEYBIND_HPP_ */
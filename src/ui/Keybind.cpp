/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Keybind
*/

#include "Keybind.hpp"
#include "ServiceLocator.hpp"

const std::vector<std::pair<irr::EKEY_CODE, irr::core::stringw>> Indie::Keybind::keyCodes = {
    {irr::EKEY_CODE::KEY_TAB, L"Tab"},
    {irr::EKEY_CODE::KEY_SHIFT, L"Shift"},
    {irr::EKEY_CODE::KEY_CONTROL, L"Control"},
    {irr::EKEY_CODE::KEY_CAPITAL, L"Maj"},
    {irr::EKEY_CODE::KEY_SPACE, L"Space"},
    {irr::EKEY_CODE::KEY_END, L"End"},
    {irr::EKEY_CODE::KEY_LEFT, L"Left"},
    {irr::EKEY_CODE::KEY_UP, L"Up"},
    {irr::EKEY_CODE::KEY_RIGHT, L"Right"},
    {irr::EKEY_CODE::KEY_DOWN, L"Down"},
    {irr::EKEY_CODE::KEY_INSERT, L"Insert"},
    {irr::EKEY_CODE::KEY_DELETE, L"Del"},
    {irr::EKEY_CODE::KEY_KEY_0, L"0"},
    {irr::EKEY_CODE::KEY_KEY_1, L"1"},
    {irr::EKEY_CODE::KEY_KEY_2, L"2"},
    {irr::EKEY_CODE::KEY_KEY_3, L"3"},
    {irr::EKEY_CODE::KEY_KEY_4, L"4"},
    {irr::EKEY_CODE::KEY_KEY_5, L"5"},
    {irr::EKEY_CODE::KEY_KEY_6, L"6"},
    {irr::EKEY_CODE::KEY_KEY_7, L"7"},
    {irr::EKEY_CODE::KEY_KEY_8, L"8"},
    {irr::EKEY_CODE::KEY_KEY_9, L"9"},
    {irr::EKEY_CODE::KEY_KEY_A, L"A"},
    {irr::EKEY_CODE::KEY_KEY_B, L"B"},
    {irr::EKEY_CODE::KEY_KEY_C, L"C"},
    {irr::EKEY_CODE::KEY_KEY_D, L"D"},
    {irr::EKEY_CODE::KEY_KEY_E, L"E"},
    {irr::EKEY_CODE::KEY_KEY_F, L"F"},
    {irr::EKEY_CODE::KEY_KEY_G, L"G"},
    {irr::EKEY_CODE::KEY_KEY_H, L"H"},
    {irr::EKEY_CODE::KEY_KEY_I, L"I"},
    {irr::EKEY_CODE::KEY_KEY_J, L"J"},
    {irr::EKEY_CODE::KEY_KEY_K, L"K"},
    {irr::EKEY_CODE::KEY_KEY_L, L"L"},
    {irr::EKEY_CODE::KEY_KEY_M, L"M"},
    {irr::EKEY_CODE::KEY_KEY_N, L"N"},
    {irr::EKEY_CODE::KEY_KEY_O, L"O"},
    {irr::EKEY_CODE::KEY_KEY_P, L"P"},
    {irr::EKEY_CODE::KEY_KEY_Q, L"Q"},
    {irr::EKEY_CODE::KEY_KEY_R, L"R"},
    {irr::EKEY_CODE::KEY_KEY_S, L"S"},
    {irr::EKEY_CODE::KEY_KEY_T, L"T"},
    {irr::EKEY_CODE::KEY_KEY_U, L"U"},
    {irr::EKEY_CODE::KEY_KEY_V, L"V"},
    {irr::EKEY_CODE::KEY_KEY_W, L"W"},
    {irr::EKEY_CODE::KEY_KEY_X, L"X"},
    {irr::EKEY_CODE::KEY_KEY_Y, L"Y"},
    {irr::EKEY_CODE::KEY_KEY_Z, L"Z"},
    {irr::EKEY_CODE::KEY_NUMPAD0, L"Num0"},
    {irr::EKEY_CODE::KEY_NUMPAD1, L"Num1"},
    {irr::EKEY_CODE::KEY_NUMPAD2, L"Num2"},
    {irr::EKEY_CODE::KEY_NUMPAD3, L"Num3"},
    {irr::EKEY_CODE::KEY_NUMPAD4, L"Num4"},
    {irr::EKEY_CODE::KEY_NUMPAD5, L"Num5"},
    {irr::EKEY_CODE::KEY_NUMPAD6, L"Num6"},
    {irr::EKEY_CODE::KEY_NUMPAD7, L"Num7"},
    {irr::EKEY_CODE::KEY_NUMPAD8, L"Num8"},
    {irr::EKEY_CODE::KEY_NUMPAD9, L"Num9"},
    {irr::EKEY_CODE::KEY_MULTIPLY, L"Mul"},
    {irr::EKEY_CODE::KEY_ADD, L"Add"},
    {irr::EKEY_CODE::KEY_SUBTRACT, L"Sub"},
    {irr::EKEY_CODE::KEY_DIVIDE, L"Div"},
    {irr::EKEY_CODE::KEY_F1, L"F1"},
    {irr::EKEY_CODE::KEY_F2, L"F2"},
    {irr::EKEY_CODE::KEY_F3, L"F3"},
    {irr::EKEY_CODE::KEY_F4, L"F4"},
    {irr::EKEY_CODE::KEY_F5, L"F5"},
    {irr::EKEY_CODE::KEY_F6, L"F6"},
    {irr::EKEY_CODE::KEY_F7, L"F7"},
    {irr::EKEY_CODE::KEY_F8, L"F8"},
    {irr::EKEY_CODE::KEY_F9, L"F9"},
    {irr::EKEY_CODE::KEY_F10, L"F10"},
    {irr::EKEY_CODE::KEY_F11, L"F11"},
    {irr::EKEY_CODE::KEY_F12, L"F12"},
    {irr::EKEY_CODE::KEY_NUMLOCK, L"NumLock"},
    {irr::EKEY_CODE::KEY_LSHIFT, L"LShift"},
    {irr::EKEY_CODE::KEY_RSHIFT, L"RShift"},
    {irr::EKEY_CODE::KEY_LCONTROL, L"LControl"},
    {irr::EKEY_CODE::KEY_RCONTROL, L"RControl"},
    {irr::EKEY_CODE::KEY_PLUS, L"Plus"},
    {irr::EKEY_CODE::KEY_COMMA, L"Comma"},
    {irr::EKEY_CODE::KEY_MINUS, L"Minus"},
    {irr::EKEY_CODE::KEY_PERIOD, L"Period"}
};

Indie::Keybind::Keybind(Indie::ContextManager &context, irr::EKEY_CODE key)
    : context(context)
    , status(false)
    , button(context)
    , pos(POS(0, 0))
    , key(key)
{
}

void Indie::Keybind::init(std::string const &filepath, int posX, int posY, irr::core::position2d<irr::s32> pos)
{
    std::string extension = filepath.substr(filepath.find_last_of("."));
    std::string strippedFilepath;
    std::copy(filepath.c_str(), filepath.c_str() + filepath.size() - extension.size(), std::back_inserter(strippedFilepath));

    font = context.getGuiEnv()->getFont("../ressources/font/Banschrift.xml");
    this->pos = pos;
    tick = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(std::string(strippedFilepath + "_tick" + extension).c_str());
    if (tick == nullptr) {
        throw Exceptions::FileNotFoundException(ERROR_STR, "File \"" + strippedFilepath + "\" not found.");
    }
    button.init(context, strippedFilepath + extension, posX, posY, POS(0, 0));
    status = false;
}

void Indie::Keybind::update(std::pair<int, int> pos)
{
    button.update(pos);
    if (button.getStatus() == Button::Status::Pressed) {
        EventHandler::getInstance().resetKeysStatus();
        EventHandler::getInstance().resetKeysStatusOnce();
        status = true;
    }
    if (status) {
        for (auto it : keyCodes) {
            if (EventHandler::getInstance().isKeyPressedAtOnce(it.first)) {
                if (it.first == key) {
                    status = false;
                    ServiceLocator::getInstance().get<SoundManager>().playSound("menu_back");
                    EventHandler::getInstance().resetKeysStatus();
                    EventHandler::getInstance().resetKeysStatusOnce();
                    break;
                }
                if (std::find(usedKeys.begin(), usedKeys.end(), it.first) != usedKeys.end()) {
                    ServiceLocator::getInstance().get<SoundManager>().playSound("bad");
                    continue;
                }
                key = it.first;
                status = false;
                ServiceLocator::getInstance().get<SoundManager>().playSound("menu_back");
                EventHandler::getInstance().resetKeysStatus();
                EventHandler::getInstance().resetKeysStatusOnce();
                break;
            }
        }
    }
}

void Indie::Keybind::draw()
{
    if (!status) {
        irr::core::stringw keyStr("N/A");
            for (auto it : keyCodes) {
                if (it.first == key)
                    keyStr = it.second;
            }
        button.draw();
        font->draw(keyStr, RECT(pos.X - (5 * int(keyStr.size())), pos.Y, 0, 0), irr::video::SColor(255, 255, 255, 255));
    }
    // Si jamais on a qu'une keybind c'est cool ça.
    // Mais comme on en a plusieurs on le fait à la mano.
    //if (status)
    //    this->context.displayImage(tick, POS(0,0));
    // Je laisse ça ici au cas où quand même
}

bool Indie::Keybind::getStatus() const
{
    return status;
}

irr::EKEY_CODE Indie::Keybind::getKey() const
{
    return key;
}

void Indie::Keybind::setStatus(bool status)
{
    this->status = status;
}

void Indie::Keybind::setUsedKeys(std::vector<std::pair<Indie::Components::KEY_TYPE, std::unique_ptr<Keybind>>>& list)
{
    usedKeys.clear();
    for (const auto& it : list)
        usedKeys.push_back(it.second->getKey());
}

void Indie::Keybind::setUsedKeys(std::vector<std::pair<Indie::Components::KEY_TYPE, std::shared_ptr<Keybind>>>& list)
{
    usedKeys.clear();
    for (const auto& it : list)
        usedKeys.push_back(it.second->getKey());
}
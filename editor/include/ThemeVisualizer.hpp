/*
** EPITECH PROJECT, 2019
** editor
** File description:
** ThemeVisualizer.hpp
*/

#ifndef B66D51B0_AC5F_4241_BC87_9ADD130D727E
#define B66D51B0_AC5F_4241_BC87_9ADD130D727E

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class ThemeVizualizer : public sf::Drawable, public sf::Transformable {
    public:
        enum THEME {LIGHT, DARK, MOUNTAIN};

    public:
        ThemeVizualizer(THEME theme = THEME::LIGHT);
        ~ThemeVizualizer();
    
    public:
        void setTheme(THEME theme) {_theme = theme;};
        THEME getTheme() const {return _theme;};

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update();
    private:

    private:
        THEME _theme;
        sf::Texture _lightTexture;
        sf::Texture _darkTexture;
        sf::Texture _mountainTexture;

        sf::Sprite _lightSprites[4];
        sf::Sprite _darkSprites[4];
        sf::Sprite _mountainSprite[4];
        int _animId;
        sf::Clock _clock;
};

#endif /* B66D51B0_AC5F_4241_BC87_9ADD130D727E */

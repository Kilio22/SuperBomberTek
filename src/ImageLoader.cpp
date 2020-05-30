/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ImageLoader
*/

#include "ImageLoader.hpp"
#include "Exceptions.h"
#include "ServiceLocator.hpp"

const std::vector<std::string> Indie::ImageLoader::paths = {
    "../ressources/images/bg_boxes.png",
    "../ressources/images/clouds.png",
    "../ressources/images/mountains.png",
    "../ressources/images/ground.png",
    "../ressources/images/trees.png",
    "../ressources/images/logo.png",
    "../ressources/images/press.png",
    "../ressources/images/Loading.png",
    "../ressources/images/black_bg.png",
    "../ressources/images/pause/Recommencer_selected.png",
    "../ressources/images/pause/Title.png",
    "../ressources/images/pause/Recommencer_pressed.png",
    "../ressources/images/pause/Menu_pressed.png",
    "../ressources/images/pause/Quitter_pressed.png",
    "../ressources/images/pause/Continue_idle.png",
    "../ressources/images/pause/Continue_selected.png",
    "../ressources/images/pause/Menu_idle.png",
    "../ressources/images/pause/Menu_selected.png",
    "../ressources/images/pause/Pause.png",
    "../ressources/images/pause/Quitter_idle.png",
    "../ressources/images/pause/Quitter_selected.png",
    "../ressources/images/pause/Continue_pressed.png",
    "../ressources/images/pause/Recommencer_idle.png",
    "../ressources/images/options/title.png",
    "../ressources/images/options/drawing.png",
    "../ressources/images/options/Retour_idle.png",
    "../ressources/images/options/Retour_selected.png",
    "../ressources/images/options/Retour_pressed.png",
    "../ressources/images/options/Layout.png",
    "../ressources/images/options/Check1_idle.png",
    "../ressources/images/options/Check1_selected.png",
    "../ressources/images/options/Check1_pressed.png",
    "../ressources/images/options/Check1_tick.png",
    "../ressources/images/options/Check2_idle.png",
    "../ressources/images/options/Check2_selected.png",
    "../ressources/images/options/Check2_pressed.png",
    "../ressources/images/options/Check2_tick.png",
    "../ressources/images/options/Vol1_idle.png",
    "../ressources/images/options/Vol1_selected.png",
    "../ressources/images/options/Vol1_pressed.png",
    "../ressources/images/options/Vol2_idle.png",
    "../ressources/images/options/Vol2_selected.png",
    "../ressources/images/options/Vol2_pressed.png",
    "../ressources/images/menu/Multi_idle.png",
    "../ressources/images/menu/Options_idle.png",
    "../ressources/images/menu/Solo_idle.png",
    "../ressources/images/menu/title.png",
    "../ressources/images/menu/Credits_idle.png",
    "../ressources/images/menu/Quitter_idle.png",
    "../ressources/images/menu/Solo_selected.png",
    "../ressources/images/menu/Multi_selected.png",
    "../ressources/images/menu/Options_selected.png",
    "../ressources/images/menu/Credits_selected.png",
    "../ressources/images/menu/Quitter_selected.png",
    "../ressources/images/menu/Solo_pressed.png",
    "../ressources/images/menu/Multi_pressed.png",
    "../ressources/images/menu/Options_pressed.png",
    "../ressources/images/menu/Credits_pressed.png",
    "../ressources/images/menu/Quitter_pressed.png",
    "../ressources/images/menu/bomb.png",
    "../ressources/images/splash/bg.png",
    "../ressources/images/splash/bomberLogos.png",
    "../ressources/images/splash/Logo.png",
    "../ressources/images/splash/Project.png"
};

Indie::ImageLoader::ImageLoader()
    : context(Indie::ServiceLocator::getInstance().get<ContextManager>())
{
    for (auto path : paths) {
        Image *tmp = nullptr;
        tmp = context.getDriver()->getTexture(path.c_str());
        if (tmp == nullptr)
            throw Exceptions::FileNotFoundException(ERROR_STR, "File " + path + " not found.");
        images.insert({path, tmp});
    }
}

Indie::ImageLoader::~ImageLoader()
{
    for (auto it=images.begin(); it!=images.end(); ++it)
        context.getDriver()->removeTexture(it->second);
}

Image *Indie::ImageLoader::getImage(std::string const &filepath)
{
    return this->images.at(filepath);
}
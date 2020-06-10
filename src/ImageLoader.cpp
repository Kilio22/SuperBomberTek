/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ImageLoader
*/

#include "ImageLoader.hpp"
#include "FileParser.hpp"
#include "Exceptions.h"
#include "ServiceLocator.hpp"

Indie::ImageLoader::ImageLoader()
    : context(Indie::ServiceLocator::getInstance().get<ContextManager>())
{
    std::unordered_map<std::string, std::string> paths = {};

    paths = ServiceLocator::getInstance().get<FileParser>().parse("../ressources/image_paths.txt", 1);
    for (auto path : paths) {
        Image *tmp = nullptr;

        tmp = context.getDriver()->getTexture(path.first.c_str());
        if (tmp == nullptr)
            throw Exceptions::FileNotFoundException(ERROR_STR, "File " + path.first + " not found.");
        images.insert({ path.first, tmp });
    }
}

Indie::ImageLoader::~ImageLoader()
{
    for (auto it = images.begin(); it != images.end(); ++it)
        context.getDriver()->removeTexture(it->second);
}

Indie::Image *Indie::ImageLoader::getImage(std::string const &filepath)
{
    return this->images.at(filepath);
}
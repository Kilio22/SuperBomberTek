/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ImageLoader
*/

#include "ImageLoader.hpp"
#include "CSVParser.hpp"
#include "Exceptions.h"
#include "ServiceLocator.hpp"

Indie::ImageLoader::ImageLoader()
    : context(Indie::ServiceLocator::getInstance().get<ContextManager>())
{
    std::vector<std::vector<std::string>> paths = {};

    paths = ServiceLocator::getInstance().get<CSVParser>().parse("../ressources/image_paths.txt");
    for (auto path : paths) {
        Image *tmp = nullptr;

        tmp = context.getDriver()->getTexture(path.at(0).c_str());
        if (tmp == nullptr)
            throw Exceptions::FileNotFoundException(ERROR_STR, "File " + path.at(0) + " not found.");
        images.insert({ path.at(0), tmp });
    }
}

Indie::ImageLoader::~ImageLoader()
{
    for (auto it = images.begin(); it != images.end(); ++it)
        context.getDriver()->removeTexture(it->second);
}

Image *Indie::ImageLoader::getImage(std::string const &filepath)
{
    return this->images.at(filepath);
}
/*
** EPITECH PROJECT, 2020
** *
** File description:
** *
*/

#ifndef IMAGELOADER_HPP_
#define IMAGELOADER_HPP_

#include <string>
#include <unordered_map>
#include <vector>
#include "ContextManager.hpp"

namespace Indie
{
    class ImageLoader {
        public:
            ImageLoader();
            ~ImageLoader();
            Image *getImage(std::string const &filepath);

        private:
            ContextManager &context;
            std::unordered_map<std::string, Image *> images;
    };
}

#endif /* !IMAGELOADER_HPP_ */
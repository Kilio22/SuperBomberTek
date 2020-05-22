/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MeshComponent
*/

#ifndef MESHCOMPONENT_HPP_
#define MESHCOMPONENT_HPP_

#include <string>
#include <map>

namespace Indie::Components
{
    class MeshComponent
    {
        public:
            MeshComponent(const std::string &texturePath);
            ~MeshComponent() = default;

            enum POSITION {
                STAND,
                RUN
            };

            const std::string &getTexturePath(void) const;
            void setTexturePath(const std::string &newPath);

            const POSITION &getCurrentPosition(void) const;
            void setCurrentPosition(POSITION newPostition);

            std::string getMeshPathByPosition(POSITION position) const;

        protected:
        private:
            static const std::map<POSITION, std::string> meshPaths;
            std::string texturePath;
            POSITION currentPosition;
    };
}

#endif /* !MESHCOMPONENT_HPP_ */

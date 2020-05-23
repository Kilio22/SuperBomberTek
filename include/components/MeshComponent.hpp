/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MeshComponent
*/

#ifndef MESHCOMPONENT_HPP_
#define MESHCOMPONENT_HPP_

#include <irrlicht.h>
#include <string>
#include <map>
#include "ContextManager.hpp"

namespace Indie::Components
{
    class MeshComponent
    {
        public:
            MeshComponent(const ContextManager &contextManager, const std::string &texturePath);
            ~MeshComponent() = default;

            enum class POSITION {
                STAND,
                RUN
            };

            irr::video::ITexture *getTexture(void) const;

            const POSITION &getCurrentPosition(void) const;
            void setCurrentPosition(POSITION newPostition);

            irr::scene::IAnimatedMesh *getMeshByPosition(POSITION position) const;

        protected:
        private:
            static const std::string STAND_MESH_PATH;
            static const std::string RUN_MESH_PATH;

            std::map<POSITION, irr::scene::IAnimatedMesh *> meshs;
            irr::video::ITexture *texture;
            POSITION currentPosition;
    };
}

#endif /* !MESHCOMPONENT_HPP_ */

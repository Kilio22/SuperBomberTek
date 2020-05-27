/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderComponent
*/

#ifndef RENDERCOMPONENT_HPP_
#define RENDERCOMPONENT_HPP_

#include <irrlicht.h>
#include <string>
#include "ContextManager.hpp"

namespace Indie::Components
{
    class RenderComponent
    {
        public:
            RenderComponent(const std::string &meshPath, const std::string &texturePath, const ContextManager &contextManager, irr::core::vector3df position, bool lightSensible);
            ~RenderComponent();

            irr::scene::IAnimatedMeshSceneNode *getMesh(void) const;
            irr::video::ITexture *getTexture(void) const;
            const std::string &getMeshPath(void) const;
            const std::string &getTexturePath(void) const;

            void setMesh(irr::scene::IAnimatedMeshSceneNode *newMesh);

        private:
            irr::scene::IAnimatedMeshSceneNode *mesh;
            irr::video::ITexture *texture;
            std::string meshPath;
            std::string texturePath;
    };
}

#endif /* !RENDERCOMPONENT_HPP_ */

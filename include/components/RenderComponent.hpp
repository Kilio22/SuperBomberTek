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
            RenderComponent(const std::string &meshPath, const std::string &texturePath, const ContextManager &contextManager, irr::core::vector3df position);
            ~RenderComponent();

            irr::scene::IAnimatedMeshSceneNode *getMesh(void) const;
            void setMesh(irr::scene::IAnimatedMeshSceneNode *newMesh);

        private:
            irr::scene::IAnimatedMeshSceneNode *mesh;
    };
}

#endif /* !RENDERCOMPONENT_HPP_ */

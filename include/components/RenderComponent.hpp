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
            RenderComponent(std::string const &, std::string const &, ContextManager const &, irr::core::vector3df);
            ~RenderComponent() = default;

            irr::scene::IAnimatedMeshSceneNode *getMesh() const;
            void setMesh(irr::scene::IAnimatedMeshSceneNode *);
            const ContextManager &getContextManager() const;

        private:
            irr::scene::IAnimatedMeshSceneNode *mesh;
            const ContextManager &contextManager;
    };
}

#endif /* !RENDERCOMPONENT_HPP_ */

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
#include "AComponent.hpp"

namespace Indie::Components
{
    class RenderComponent : public AComponent
    {
        public:
            RenderComponent(std::string const &, std::string const &, irr::scene::ISceneManager *, irr::video::IVideoDriver *);
            ~RenderComponent();

            irr::scene::IAnimatedMeshSceneNode *getMesh();
            void setMesh(irr::scene::IAnimatedMesh *, irr::scene::ISceneManager *);
        private:
            irr::scene::IAnimatedMeshSceneNode *mesh;
    };
}

#endif /* !RENDERCOMPONENT_HPP_ */

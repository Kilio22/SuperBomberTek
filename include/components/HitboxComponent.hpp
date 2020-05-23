/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** HitboxComponent
*/

#ifndef HITBOXCOMPONENT_HPP_
#define HITBOXCOMPONENT_HPP_

#include <irrlicht.h>
#include "ContextManager.hpp"

namespace Indie::Components
{
    class HitboxComponent
    {
        public:
            HitboxComponent(irr::core::vector3df, const ContextManager &);
            ~HitboxComponent() = default;

            irr::scene::IAnimatedMeshSceneNode *getMesh(void) const;

        private:
            irr::scene::IAnimatedMeshSceneNode *mesh;
    };
} // namespace Indie::Components


#endif /* !HITBOXCOMPONENT_HPP_ */

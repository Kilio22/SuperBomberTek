/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** RenderComponent
*/

#ifndef RENDERCOMPONENT_HPP_
#define RENDERCOMPONENT_HPP_

#include "ContextManager.hpp"
#include <irrlicht.h>
#include <string>

namespace Indie::Components
{
    /**
     * @brief Render component
     */
    class RenderComponent
    {
    public:
        RenderComponent(const std::string &meshPath, const std::string &texturePath, const ContextManager &contextManager,
            irr::core::vector3df position, bool lightSensible);
        ~RenderComponent();

        /**
         * @brief Gets the current mesh
         * @return irr::scene::IAnimatedMeshSceneNode* The mesh
         */
        irr::scene::IAnimatedMeshSceneNode *getMesh(void) const;

        /**
         * @brief Gets the current texture
         * @return irr::video::ITexture* The texture
         */
        irr::video::ITexture *getTexture(void) const;

        /**
         * @brief Gets the current mesh path
         * @return const std::string& The mesh path
         */
        const std::string &getMeshPath(void) const;

        /**
         * @brief Gets the current texture path
         * @return const std::string& the texture path
         */
        const std::string &getTexturePath(void) const;

        /**
         * @brief Sets the current mesh
         * @param newMesh The new mesh
         */
        void setMesh(irr::scene::IAnimatedMeshSceneNode *newMesh);

    private:
        irr::scene::IAnimatedMeshSceneNode *mesh;
        irr::video::ITexture *texture;
        std::string meshPath;
        std::string texturePath;
    };
}

#endif /* !RENDERCOMPONENT_HPP_ */

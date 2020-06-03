/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MeshComponent
*/

#ifndef MESHCOMPONENT_HPP_
#define MESHCOMPONENT_HPP_

#include "ContextManager.hpp"
#include <irrlicht.h>
#include <map>
#include <string>

namespace Indie::Components
{
    /**
     * @brief Mesh component
     */
    class MeshComponent
    {
    public:
        MeshComponent(const ContextManager &contextManager, const std::string &texturePath);
        ~MeshComponent() = default;

        enum class MESH_STATE
        {
            STAND,
            RUN,
            DIE
        };

        /**
         * @brief Gets the mesh's texture
         * @return irr::video::ITexture* The texture
         */
        irr::video::ITexture *getTexture(void) const;

        /**
         * @brief Gets the mesh's state
         * @return const MESH_STATE& The mesh's state
         */
        const MESH_STATE &getCurrentMeshState(void) const;

        /**
         * @brief Sets the current mesh's state
         * @param newState The new state
         */
        void setCurrentMeshState(MESH_STATE newState);

        /**
         * @brief Get a mesh according to specified state
         * @param state The wanted state
         * @return irr::scene::IAnimatedMesh* The mesh
         */
        irr::scene::IAnimatedMesh *getMeshByState(MESH_STATE state) const;

    private:
        static const std::string STAND_MESH_PATH;
        static const std::string RUN_MESH_PATH;
        static const std::string DIE_MESH_PATH;

        std::map<MESH_STATE, irr::scene::IAnimatedMesh *> meshs;
        irr::video::ITexture *texture;
        MESH_STATE currentMeshState;
    };
}

#endif /* !MESHCOMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <vector>
#include <memory>
#include <iostream>
#include <irrlicht.h>
#include "Entity.hpp"
#include "PositionComponent.hpp"
#include "RenderComponent.hpp"

namespace Indie
{
    class EntityManager
    {
        public:
            EntityManager() = default;
            ~EntityManager() = default;

            std::vector<Entity> getEntitiesByComponents(int componentId)
            {
                std::vector<Entity> vec;

                for (auto &ref : this->entities) {
                    if (ref.hasComponent(componentId))
                        vec.push_back(ref);
                }
                return vec;
            }

            void createGround(irr::core::vector3df const &vector, const std::string &modelPath, const std::string &texturePath, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver)
            {
                Entity deglingue;
                std::shared_ptr<Components::PositionComponent> xd = std::make_shared<Components::PositionComponent>(vector.X, vector.Y, vector.Z);
                std::shared_ptr<Components::RenderComponent> xd2 = std::make_shared<Components::RenderComponent>(modelPath, texturePath, sceneManager, videoDriver);

                deglingue.addComponent(std::static_pointer_cast<Components::IComponent>(xd));
                deglingue.addComponent(std::static_pointer_cast<Components::IComponent>(xd2));

                this->entities.push_back(deglingue);
            }

            // void createWall(irr::core::vector3df &vector);
            // void createPlayer(irr::core::vector3df &vector);
            // void createBomb(irr::core::vector3df &vector);
            // void createIA(irr::core::vector3df &vector);

        private:
            std::vector<Entity> entities;
    };
}

#endif /* !ENTITYMANAGER_HPP_ */

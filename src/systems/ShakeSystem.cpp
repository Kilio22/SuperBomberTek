/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ShakeSystem | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "ShakeSystem.hpp"
#include "Components.h"
#include "Exceptions.h"

void Indie::Systems::ShakeSystem::onUpdate(irr::f32 deltaTime, EntityManager &entityManager) const
{
    for (auto entity : entityManager.each<Components::ShakeComponent>()) {
        auto shakeComponent = entity->getComponent<Components::ShakeComponent>();

        if (shakeComponent->getIsShaking() == false)
            return;
        irr::u32 currentTime = ServiceLocator::getInstance().get<ContextManager>().getDevice()->getTimer()->getTime();
        irr::u32 startTime = shakeComponent->getStartingTime();
        irr::scene::ICameraSceneNode *camera = ServiceLocator::getInstance().get<ContextManager>().getSceneManager()->getActiveCamera();

        if (camera == nullptr) {
            throw Indie::Exceptions::CameraNotFoundException(ERROR_STR, "No camera is active.");
        }
        if (currentTime - startTime >= 2) {
            shakeComponent->setIsShaking(false);
            shakeComponent->setStartingTime(0);
            camera->setPosition(shakeComponent->getInitialPosition());
            camera->setTarget(shakeComponent->getInitialTarget());
            return;
        }
        irr::core::vector3df camPos = camera->getPosition();
        irr::core::vector3df targetPos = camera->getTarget();
        int valX = std::rand() % 10 - 5;
        int valZ = std::rand() % 10 - 5;

        camPos.X += valX;
        camPos.Z += valZ;
        targetPos.X += valX;
        targetPos.Z += valZ;
        camera->setPosition(camPos);
        camera->setTarget(targetPos);
    }
}

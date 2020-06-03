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
        irr::f32 currentDeltaTime = shakeComponent->getDeltaTime() + deltaTime;
        irr::scene::ICameraSceneNode *camera = ServiceLocator::getInstance().get<ContextManager>().getSceneManager()->getActiveCamera();

        if (camera == nullptr) {
            throw Indie::Exceptions::CameraNotFoundException(ERROR_STR, "No camera is active.");
        }
        if (currentDeltaTime >= 0.1f) {
            shakeComponent->setIsShaking(false);
            camera->setPosition(shakeComponent->getInitialPosition());
            camera->setTarget(shakeComponent->getInitialTarget());
            return;
        } else {
            shakeComponent->setDeltaTime(currentDeltaTime);
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

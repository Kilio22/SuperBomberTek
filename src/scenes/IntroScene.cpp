/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IntroScene | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#include "IntroScene.hpp"
#include "CameraNotFoundException.hpp"
#include "ServiceLocator.hpp"

Indie::IntroScene::IntroScene(ContextManager &context)
    : context(context)
    , camera(nullptr)
    , currentRotationAngle(303.15f, 48.9909f, 0.f)
    , shouldResetTarget(true)
{}

Indie::IntroScene::~IntroScene() {}

void Indie::IntroScene::init()
{
    this->camera = this->context.getSceneManager()->getActiveCamera();
    if (this->camera == nullptr)
        throw Indie::Exceptions::CameraNotFoundException(ERROR_STR, "No camera is active.");
    this->currentRotationAngle = irr::core::vector3df(0.f, 0.f, 120.f);
    this->shouldResetTarget = true;
    this->camera->setTarget(irr::core::vector3df(138.593f, 280.f, 121.f));
}

void Indie::IntroScene::reset()
{
    this->init();
}

void Indie::IntroScene::update(irr::f32 deltaTime)
{
    irr::core::vector3df newRotatationAngle;

    if (this->camera == nullptr) {
        throw Indie::Exceptions::CameraNotFoundException(ERROR_STR, "Camera not initiliazed.");
    }
    if (this->currentRotationAngle.Y < 360.f) {
        this->worldTour(deltaTime);
    } else if (this->shouldResetTarget == true) {
        this->resetTarget();
    } else {
        this->downTarget(deltaTime);
    }
    if (EventHandler::getInstance().isKeyPressed(irr::KEY_ESCAPE)) {
        this->skipScene();
    }
}

void Indie::IntroScene::renderPre3D() {}

void Indie::IntroScene::renderPost3D() {}

void Indie::IntroScene::skipScene(void)
{
    this->camera->setRotation(irr::core::vector3df(0.f, 0.f, 0.f));
    this->camera->setTarget(irr::core::vector3df(138.593f, -34.13f, 121.f));
    EventHandler::getInstance().resetKeys();
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneUpdateActive(true);
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSceneRenderActive(true);
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneRenderActive(false);
    Indie::ServiceLocator::getInstance().get<SceneManager>().setSubSceneUpdateActive(false);
    Indie::ServiceLocator::getInstance().get<MusicManager>().setStatus(Music::Status::Loop);
}

void Indie::IntroScene::worldTour(irr::f32 deltaTime)
{
    irr::core::vector3df newRotatationAngle;

    this->currentRotationAngle.Y += deltaTime * 20.f;
    newRotatationAngle = this->currentRotationAngle;
    if (this->currentRotationAngle.Y >= 360.f)
        newRotatationAngle.Y = 0.f;
    this->camera->setRotation(newRotatationAngle);
}

void Indie::IntroScene::resetTarget(void)
{
    camera->setTarget(irr::core::vector3df(138.593f, 280.f, 121.f));
    this->shouldResetTarget = false;
}

void Indie::IntroScene::downTarget(irr::f32 deltaTime)
{
    irr::core::vector3df target = this->camera->getTarget();

    if (target.Y > -34.f) {
        target.Y -= deltaTime * 30.f;
        this->camera->setTarget(target);
    } else {
        this->skipScene();
    }
}

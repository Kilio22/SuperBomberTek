/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IntroScene | Author: Kylian BALAN - kylian.balan@epitech.eu
*/

#ifndef INTROSCENE_HPP_
#define INTROSCENE_HPP_

#include "IScene.hpp"

namespace Indie
{
    class IntroScene : public IScene
    {
        public:
        IntroScene(ContextManager &context);
        ~IntroScene() = default;

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void skipScene(void);

        private:
        void worldTour(irr::f32 deltaTime);
        void resetTarget(void);
        void downTarget(irr::f32 deltaTime);

        ContextManager &context;
        irr::scene::ICameraSceneNode *camera;
        irr::core::vector3df currentRotationAngle;
        bool shouldResetTarget;
    };
} // namespace Indie

#endif /* !INTROSCENE_HPP_ */

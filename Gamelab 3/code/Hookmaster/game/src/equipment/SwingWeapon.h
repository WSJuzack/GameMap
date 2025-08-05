#pragma once

#include "Weapon.h"
#include "../entities/Hookshot.h"
#include <soloud.h>
#include <soloud_wav.h>

namespace gl3
{
    class SwingWeapon: public Weapon {
    public:
        SwingWeapon(Game* game, Player* player);
        ~SwingWeapon();

        void setActive(bool value) override;

        void shooting(Game* game,float deltaTime) override;
        void beforeKillWeapon() override;
        void draw(const Camera& camera) override;
        void update(float deltaTime) override;
        void calculateInterpolateTransform(float accumulator, float timeStep) override;

        void checkHitTarget(bool hitTarget);
        void destroyHookshot(bool rightOne);
        void handleJoint (bool create, bool BaSJoint);
        void fillRopeSegments(int ropeSegmentCount);

    private:
        bool shotLeft = false;
        bool shotRight = false;
        bool pulling = false;
        const float jumpSpeed = 1.5f;
        const float pullSpeed = 1000.0f;
        std::vector<std::unique_ptr<Entity>> ropeSegments;
        std::unique_ptr<Hookshot> hookshotLeft;
        std::unique_ptr<Hookshot> hookshotRight;
        SoLoud::Wav ropeBreakSound;
    };
}
#pragma once

#include "Weapon.h"
#include "../Physics/RaycastCallbackBlastAway.h"

namespace gl3
{
    class BlastAwayWeapon : public Weapon {
    public:
        BlastAwayWeapon(Game* game, Player* player);
        ~BlastAwayWeapon();

        void calculateBlastAway(rp3d::Vector3 treePosition);

        void setActive(bool value) override;
        void shooting(Game* game,float deltaTime) override;
        void beforeKillWeapon() override;
        void draw(const Camera& camera) override;
        void update(float deltaTime) override;
        void calculateInterpolateTransform(float accumulator, float timeStep) override;

    private:
        bool pressedRight;
        bool pressedLeft;
        bool blasted;
        const float blastSpeed = 40;
        RaycastCallbackBlastAway raycastBlastAway;
        rp3d::Ray blastRay;
        float blastRange = 75;
    };
}

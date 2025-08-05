#pragma once

#include "reactphysics3d/reactphysics3d.h"

namespace gl3 {
    class RaycastCallbackBlastAway : public rp3d::RaycastCallback {
    public:
        RaycastCallbackBlastAway();

        void setRightOrLeft(bool value) { m_rightOne = value; }

        void setOrigin(Game* game, BlastAwayWeapon* weapon);

        rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) override;
    private:
        Game* m_game;
        BlastAwayWeapon* m_weapon;
        bool m_rightOne;
    };
}

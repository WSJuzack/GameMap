#pragma once

#include "reactphysics3d/reactphysics3d.h"

namespace gl3 {
    class RaycastCallbackSelection : public rp3d::RaycastCallback {
    public:
        RaycastCallbackSelection();

        void setRightOrLeft(bool value) { m_rightOne = value; }

        void setOrigin(Game* game, DragWeapon* weapon);

        rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) override;
    private:
        Game* m_game;
        DragWeapon* m_weapon;
        bool m_rightOne;
    };
}
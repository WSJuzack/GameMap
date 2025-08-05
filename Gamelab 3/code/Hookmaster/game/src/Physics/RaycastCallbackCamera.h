#pragma once

#include "reactphysics3d/reactphysics3d.h"

namespace gl3 {
    class RaycastCallbackCamera : public rp3d::RaycastCallback {
    public:
        RaycastCallbackCamera();

        void setOrigin(Game* game);
        rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) override;
    private:

        Game* m_game = nullptr;
    };
}
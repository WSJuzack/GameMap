#pragma once

#include "reactphysics3d/reactphysics3d.h"

namespace gl3 {
    class RaycastCallbackRopebreak : public rp3d::RaycastCallback {
    public:
        RaycastCallbackRopebreak();

        void setOrigin(Hookshot* shot, Game* game);
        rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) override;
    private:

        Hookshot* m_shot;
        Game* m_game;
    };
}
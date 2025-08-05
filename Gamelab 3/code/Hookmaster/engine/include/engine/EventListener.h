#pragma once

#include "../../../game/src/forward.h"
#include "reactphysics3d/reactphysics3d.h"

namespace gl3 {
    class EventListener : public rp3d::EventListener{
    public:
        EventListener(Game* game);

        Collision* voidConvertion_collision (void* p);
        void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) override;
        void onContact(const rp3d::CollisionCallback::CallbackData& callbackData) override;

    private:
        Collision* OBody1 = nullptr;
        Collision* OBody2 = nullptr;
    };
}

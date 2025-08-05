#pragma once
#include "../../../game/src/forward.h"

#include "reactphysics3d/reactphysics3d.h"

namespace gl3 {

    class World {
    public:
        World();
        rp3d::PhysicsWorld::WorldSettings settings;

    };

}
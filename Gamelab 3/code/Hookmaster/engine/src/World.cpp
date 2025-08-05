#include "../../game/src/Game.h"

namespace gl3 {
    World::World()
    {
        settings.defaultVelocitySolverNbIterations = 20;
        settings.isSleepingEnabled = true;
        settings.gravity = rp3d::Vector3(0, -9.81, 0);
        settings.worldName = "testWorld";
    }
}

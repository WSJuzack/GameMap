#pragma once

#include "../forward.h"
#include "reactphysics3d/reactphysics3d.h"
#include "engine/Entity.h"

namespace gl3 {

    class Terrain: public Entity {
    public:
        explicit Terrain(Game* game, const std::string& modelPath,
                         glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, int terrainType, bool invisible = false);
        ~Terrain();
        void draw(const Camera& camera) override;
        void startCollisionTrigger(Collision* otherBody) override;
        void duringCollisionTrigger(Collision* otherBody) override;
        void endCollisionTrigger(Collision* otherBody) override;
        void startCollision(Collision* otherBody) override;
        void duringCollision(Collision* otherBody) override;
        void endCollision(Collision* otherBody) override;
        short getCollisionBit() override;

    private:
        bool collidedWithCamera = false;
        bool collidedWithRay = false;
        bool isInvisible = false;
    };
}

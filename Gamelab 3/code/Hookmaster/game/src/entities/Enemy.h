#include "engine/Entity.h"

namespace gl3 {
    class Enemy: public Entity {
    public:
        explicit Enemy(Game* game, glm::vec3 rotation, glm::vec3 position, glm::vec3 scale, glm::vec3 end, float timeToEndPos, bool isTrigger = true);
        ~Enemy();

        void startCollisionTrigger(Collision* otherBody) override;
        void duringCollisionTrigger(Collision* otherBody) override;
        void endCollisionTrigger(Collision* otherBody) override;
        void startCollision(Collision* otherBody) override;
        void duringCollision(Collision* otherBody) override;
        void endCollision(Collision* otherBody) override;
        short getCollisionBit() override;
        bool filterCheck(bool check) override;

        void update(float deltaTime) override;
        void draw(const Camera& camera) override;

    private:

        glm::vec3 m_startPos;
        glm::vec3 m_endPos;
        glm::vec3 m_distance;
        float m_time;
        float elapsedTime = 0;
        bool startToEnd = true;
    };
}


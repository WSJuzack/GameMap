#include "engine/Entity.h"

namespace gl3 {
    class Goal: public Entity {
    public:
        explicit Goal(Game* game, const std::string& modelPath, glm::vec3 position, glm::vec3 scale, bool final);
        ~Goal();

        void startCollisionTrigger(Collision* otherBody) override;
        void duringCollisionTrigger(Collision* otherBody) override;
        void endCollisionTrigger(Collision* otherBody) override;
        void startCollision(Collision* otherBody) override;
        void duringCollision(Collision* otherBody) override;
        void endCollision(Collision* otherBody) override;
        short getCollisionBit() override;
        bool filterCheck(bool check) override;

        void update(float deltaTime) override;
        void draw(const gl3::Camera &camera) override;

    private:

        SoLoud::Soloud audio;
        SoLoud::Wav goalSound;
        float sinCache = 0;
        float initY = 0;
        bool m_final;
        bool goalReached = false;
    };
}
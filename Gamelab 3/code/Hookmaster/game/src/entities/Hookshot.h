#pragma once

#include "engine/Entity.h"
#include "Tree.h"
#include "../physics/RaycastCallback.h"
#include "../physics/RaycastCallbackRopebreak.h"

namespace gl3 {

    class Hookshot: public Entity {
        public:
            explicit Hookshot(Game* game, Player* player, rp3d::Vector3 direction,
                              SwingWeapon* originWeapon, bool rightOne);
            ~Hookshot() override;
            void setToDestroy(bool Destroy) { toDestroy = Destroy;}
            [[nodiscard]] rp3d::Vector3 getDirection() const{ return m_direction; }
            [[nodiscard]] glm::vec3& getHookshotToHit() { return hookshotToHit; }
            [[nodiscard]] bool getHasHitTarget() const{ return hitTarget; }
            [[nodiscard]] rp3d::BallAndSocketJoint* getBaSJoint() { return BaSJoint; }
            [[nodiscard]] rp3d::Ray* getRay() { return &endPointRay; }
            [[nodiscard]] Tree* getHitTree() const { return hitTree; }
            void setIntersectionPoint(rp3d::Vector3 intersectionPoint) { m_intersectionPoint = intersectionPoint; }
            glm::vec3 startLocationSetOff(glm::vec3 vector, const float factor, glm::vec3 playerFront);
            glm::vec3 hookDrawStartLocation(bool rightOne);
            void handleJoint(bool create, bool BaSJoint = true);
            void createJoint(bool ballandsocket);
            bool destroyJoint();
            void RayCallback(const rp3d::Ray& ray);
            void meshMovement(Game* game, float deltaTime);
            void hitboxMovement(Game* game, float deltaTime);
            void calculateHookshotToHit(glm::vec3& hookshotToHit,const rp3d::Ray& hitRay,
                                        const rp3d::Vector3& intersectionPoint = {0,0,0});

            void update(float deltaTime) override;
            void startCollisionTrigger(Collision* otherBody) override;
            void duringCollisionTrigger(Collision* otherBody) override;
            void endCollisionTrigger(Collision* otherBody) override;
            void startCollision(Collision* otherBody) override;
            void duringCollision(Collision* otherBody) override;
            void endCollision(Collision* otherBody) override;
            short getCollisionBit() override;
            bool filterCheck(bool check) override;

    private:
        rp3d::SphereShape* sphereCollider;
        float speed = 200;
        rp3d::Vector3 m_direction;
        bool hitTarget = false;
        Player* m_player;
        rp3d::Vector3 m_intersectionPoint;
        rp3d::BallAndSocketJoint* BaSJoint = nullptr;
        rp3d::SliderJoint* SJoint = nullptr;
        RaycastCallback rayCaster;
        RaycastCallbackRopebreak ropeBreakRayCaster;
        rp3d::Ray endPointRay;
        rp3d::Ray ropeBreakRay;
        glm::vec3 hookshotToHit;
        bool m_rightOne;
        bool toDestroy = false;
        SwingWeapon* m_weapon = nullptr;
        Tree* hitTree = nullptr;
    };

}






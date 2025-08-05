#pragma once

#include "engine/Entity.h"
#include <soloud.h>
#include <soloud_wav.h>


namespace gl3 {

    class Player: public Entity
            {

    public:
        explicit Player(Game *game,
                rp3d::Vector3 position = rp3d::Vector3(0.0f, 0.0f, 0.0f),
                glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3 scale = glm::vec3(0.5f, 0.5f, 0.5f));
        virtual ~Player()                        override;
        void update(float deltaTime) override;
        void draw (const Camera& camera)         override;

        [[nodiscard]] bool getFlyingState() const { return isFlying; }
        [[nodiscard]] float getGroundSpeed() const { return groundSpeed; }
        [[nodiscard]] float getAirSpeed() const { return airSpeed; }
        [[nodiscard]] bool getBananaCollected() const { return bananaCollected; }
        [[nodiscard]] rp3d::Vector3 getRespawnLocation() const { return respawnLocation; }
        void setRespawnLocation(rp3d::Vector3 value) { respawnLocation = value; }
        void setGroundSpeed(float value) { groundSpeed = value; }
        void setAirSpeed(float value) { airSpeed = value; }
        void setFlyingState(bool value);
        void setWeaponHit(bool value) { weaponHit = value; }
        void setMovementLock (bool value) { movementLock = value; }
        void weaponInit();
        void weaponSwap(bool firstWeapon = false);
        void setDragTreeWeapon(Tree* tree);
        void playerDeath();
        void setCollectedBanana(bool value) { bananaCollected = value; }

        void startCollisionTrigger(Collision* otherBody)                        override;
        void duringCollisionTrigger(Collision* otherBody)                       override;
        void endCollisionTrigger(Collision* otherBody)                          override;
        void startCollision(Collision* otherBody)                               override;
        void duringCollision(Collision* otherBody)                              override;
        void endCollision(Collision* otherBody)                                 override;
        short getCollisionBit()                                                 override;
        bool filterCheck(bool check)                                            override;
        void calculateInterpolateTransform(float accumulator, float timeStep)   override;

        //no deltaTime needed -> movement calculated through physics -> already has deltaTime build in
        void gatherMovementKeys(Game* game, float deltaTime);
        void calculateGroundMovement(float degree);
        void calculateAirMovement(float degree, float deltaTime);
        void calculateJump();
        void manageAirMovement(bool WKey, bool AKey, bool SKey, bool DKey, float deltaTime);
        void manageGroundMovement(bool WKey, bool AKey, bool SKey, bool DKey, bool SpaceKey);
        void stopMovement();

    private:
      ///please only change through setFlyingState(bool value)
      bool isFlying = false;
      bool isMoving = false;
      bool WPressed = false;
      bool APressed = false;
      bool SPressed = false;
      bool DPressed = false;
      bool SpacePressed = false;
      bool weaponSwapLock = false;
      bool movementLock = false;
      bool bananaCollected = false;
      bool weaponHit = false;
      bool godMode = false;
      int currentWeaponIndex = 0;
      float movementLockCooldown = 0.0f;
      SoLoud::Soloud audio;
      SoLoud::Wav deathSound;
      float groundSpeed = 12.5f;
      float airSpeed = 1000.0f;
      glm::vec3 m_playerFront;
      rp3d::Vector3 respawnLocation = {0.0f, 1.0f, 0.0f};
      rp3d::Quaternion m_orientation;
      rp3d::SphereShape* sphereCollider = nullptr;
      std::vector<std::unique_ptr<Weapon>> playerWeapons;
      Weapon* activeWeapon = nullptr;
    };
}

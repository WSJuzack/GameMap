#pragma once

#include "../../../game/src/forward.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/Collision.h"
#include "reactphysics3d/reactphysics3d.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "engine/EventListener.h"
#include "../../../game/src/Physics/RaycastCallbackCamera.h"

namespace gl3 {


    class Camera : public Collision {

    public:
        Camera(GLFWwindow* window, Game* game, int height, int width);
        ~Camera();
        void update();
        void startCollisionTrigger(Collision* otherBody) override;
        void duringCollisionTrigger(Collision* otherBody) override;
        void endCollisionTrigger(Collision* otherBody) override;
        void startCollision(Collision* otherBody) override;
        void duringCollision(Collision* otherBody) override;
        void endCollision(Collision* otherBody) override;
        short getCollisionBit() override;
        bool filterCheck(bool check) override;

        static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
        static glm::mat4 calculateMvpMatrix(const glm::vec3& position,const glm::vec3& rotation, const glm::vec3& scale);
        static glm::mat4 calculateModelMatrix(const glm::vec3& position,const glm::vec3& rotation, const glm::vec3& scale);
        static glm::mat4 calculateViewMatrix();
        static glm::mat4 calculateProjectionMatrix();
        static void getPlayerPosition(const Player& player);
        static void setPlayerRotation(Player& player);
        static float calculateHorizontalDistance(float fov, float customPitch = 0);
        static float calculateVerticalDistance(float fov, float customPitch = 0);
        static void calculateCameraPosition(glm::vec3& outPos, const glm::vec3& target, const float horizontalDistance,
                                            const float verticalDistance, const float addDegree = 0.0f);
        static void calculateForwardVector(glm::vec3& outPos,const glm::vec3& drawVec, const glm::vec3& target,
                                           const float horizontalDistance, const float verticalDistance,
                                           const float addDegree = 0.0f);

        static int startingX;
        static int startingY;
        static float pitch;
        static float fov;
        static float renderDistance;
        static bool firstMouse;
        static glm::vec3 cameraUp;
        static glm::vec3 cameraPos;
        static glm::vec3 cameraTarget;
        static glm::vec3 cameraFront;
        static float angleAroundPlayer;
        static bool isMouseMoving;

    private:
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
        glm::vec3 sceneUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraRight = glm::normalize(glm::cross(sceneUp, cameraDirection));
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
        //has to be glm to save position - rp3d_to_glm creates temporary copy
        glm::vec3 colliderPosition = {0,0,0};
        rp3d::RigidBody* cameraBody = nullptr;
        rp3d::PhysicsCommon cameraPhysicsCommon;
        rp3d::Ray cameraRay;
        Game* m_game;
        RaycastCallbackCamera rayCasterCamera;
    };
}


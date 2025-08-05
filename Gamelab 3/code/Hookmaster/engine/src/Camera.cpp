#include "engine/Camera.h"
#include "../../game/src/entities/Player.h"
#include "../../game/src/Game.h"

namespace gl3 {

    int       Camera::startingX = 0;
    int       Camera::startingY = 0;
    float     Camera::pitch = 10.0f;
    float     Camera::angleAroundPlayer = 0;
    float     Camera::fov = 20.0f;
    float     Camera::renderDistance = 300.0f;
    glm::vec3 Camera::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Camera::cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Camera::cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Camera::cameraFront = glm::vec3(0.0f, 1.0f, 0.0f);
    bool      Camera::firstMouse = true;
    bool      Camera::isMouseMoving = false;

    Camera::Camera(GLFWwindow* window, Game* game, int height, int width) :
            m_game(game),
            //Values don't matter -> gets new values every Update()
            cameraRay(convert::glm_to_rp3d(cameraTarget), convert::glm_to_rp3d(cameraTarget))
    {
        startingX = width/2;
        startingY = height/2;

        //true Body
        rp3d::Quaternion orientation = rp3d::Quaternion::identity();
        rp3d::Transform transform (convert::glm_to_rp3d(cameraPos), orientation);
        cameraBody = game->getWorld()->createRigidBody(transform);
        cameraBody->setType(rp3d::BodyType::KINEMATIC);
        cameraBody->setUserData(this);

        rp3d::SphereShape* sphereCollider = cameraPhysicsCommon.createSphereShape(1);
        cameraBody->addCollider(sphereCollider, {{0,0,0}, orientation});
        cameraBody->getCollider(0)->setCollisionCategoryBits(game->camera);
        cameraBody->getCollider(0)->setCollideWithMaskBits(game->staticTerrain | game->swingSurface);
        cameraBody->getCollider(0)->setIsTrigger(true);

        rayCasterCamera.setOrigin(m_game);
    }

    Camera::~Camera()
    {

    }

    void Camera::startCollisionTrigger(Collision* otherBody)
    {

    }

    void Camera::duringCollisionTrigger(Collision* otherBody)
    {
        if(otherBody->getCollisionBit() == m_game->staticTerrain ||
           otherBody->getCollisionBit() == m_game->wall ||
           otherBody->getCollisionBit() == m_game->enemy ||
           otherBody->getCollisionBit() == m_game->goal)
        {
            otherBody->setCollidedWithCamera(true);
        }
    }

    void Camera::endCollisionTrigger(Collision* otherBody)
    {
        if(otherBody->getCollisionBit() == m_game->staticTerrain ||
           otherBody->getCollisionBit() == m_game->wall ||
           otherBody->getCollisionBit() == m_game->enemy ||
           otherBody->getCollisionBit() == m_game->goal)
        {
            otherBody->setCollidedWithCamera(false);
        }
    }

    void Camera::startCollision(Collision* otherBody)
    {

    }

    void Camera::duringCollision(Collision* otherBody)
    {

    }

    void Camera::endCollision(Collision* otherBody)
    {

    }

    short Camera::getCollisionBit()
    {
        return cameraBody->getCollider(0)->getCollisionCategoryBits();
    }

    bool Camera::filterCheck(bool check)
    {
        return false;
    }

    void Camera::getPlayerPosition(const Player& player)
    {
        cameraTarget = player.getDrawVec();
    }

    void Camera::setPlayerRotation(Player& player)
    {
        player.setYRotation(-angleAroundPlayer);
    }

    float Camera::calculateHorizontalDistance(float fov, float customPitch)
    {
        if (customPitch == 0)
        {
            return fov * cos(glm::radians(pitch));
        }
        else
        {
            return fov * cos(glm::radians(customPitch));
        }
    }

    float Camera::calculateVerticalDistance(float fov, float customPitch)
    {
        if (customPitch == 0)
        {
            return fov * sin(glm::radians(pitch));
        }
        else
        {
            return fov * sin(glm::radians(customPitch));
        }
    }

    void Camera::calculateCameraPosition(glm::vec3& outPos, const glm::vec3& target, const float horizontalDistance, const float verticalDistance, const float addDegree)
    {
        float theta = angleAroundPlayer + addDegree;
        float offsetX = horizontalDistance * sin(glm::radians(theta));
        float offsetZ = horizontalDistance * cos(glm::radians(theta));
        outPos.x = target.x + offsetX;
        outPos.z = target.z - offsetZ;
        outPos.y = target.y + verticalDistance;
    }

    void Camera::calculateForwardVector(glm::vec3& outPos,const glm::vec3& drawVec, const glm::vec3& target, const float horizontalDistance, const float verticalDistance, const float addDegree)
    {
        calculateCameraPosition(outPos, target, horizontalDistance, verticalDistance, addDegree);
        outPos -= drawVec;
        convert::glm_normalize(outPos);
    }

    glm::mat4 Camera::calculateMvpMatrix(const glm::vec3& position,const glm::vec3& rotation, const glm::vec3& scale)
    {
        glm::mat4 model = calculateModelMatrix(position, rotation, scale);

        glm::mat4 view = calculateViewMatrix();

        glm::mat4 projection = calculateProjectionMatrix();

        return projection * view * model;
    }

    glm::mat4 Camera::calculateModelMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        return model;
    }

    glm::mat4 Camera::calculateViewMatrix()
    {
        glm::mat4 view = glm::lookAt(cameraPos ,cameraTarget + cameraFront, cameraUp);

        return view;
    }

    glm::mat4 Camera::calculateProjectionMatrix()
    {
        glm::mat4 projection = glm::perspective(glm::radians(fov), 100.0f / 60.0f, 0.1f, renderDistance);

        return projection;
    }


    void Camera::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
    {
        if (firstMouse)
        {
            startingX = xposIn;
            startingY = yposIn;
            firstMouse = false;
        }

        //calculating the differents
        angleAroundPlayer = xposIn - startingX;
        pitch = yposIn - startingY;

        //Mouse movement in y is different to x, sensitivity has to be adjusted
        float sensitivity = 0.025f;
        pitch *= sensitivity;
        sensitivity = 0.1f;
        angleAroundPlayer *= sensitivity;

        //if pitch exceeds 90 degrees lookAt inverses
        if (pitch > 80.0f)
            pitch = 80.0f;
        if (pitch < -80.0f)
            pitch = -80.0f;

        float horizontalDistance = calculateHorizontalDistance(fov);
        float verticalDistance = calculateVerticalDistance(fov);
        calculateCameraPosition(cameraPos, cameraTarget, horizontalDistance, verticalDistance);

        isMouseMoving = true;
    }

    void Camera::update()
    {
        cameraRay.point1 = convert::glm_to_rp3d(cameraTarget);
        cameraRay.point2 = cameraBody->getTransform().getPosition();
        m_game->getWorld()->raycast(cameraRay, &rayCasterCamera);

        if (isMouseMoving)
        {
            isMouseMoving = false;
        } else
        {
            //to keep the camera on the player we need to update it, even if the camera is not moving
            calculateCameraPosition(cameraPos, cameraTarget, calculateHorizontalDistance(fov), calculateVerticalDistance(fov));
        }
        cameraBody->setTransform({convert::glm_to_rp3d(cameraPos),
                                  cameraBody->getTransform().getOrientation()});
    }
}

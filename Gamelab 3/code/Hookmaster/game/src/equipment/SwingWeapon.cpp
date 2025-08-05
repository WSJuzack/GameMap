#include "SwingWeapon.h"
#include <glm/gtx/quaternion.hpp>
#include "../Game.h"

namespace gl3
{
    SwingWeapon::SwingWeapon(Game* game, Player* player)
    :
    Weapon(game, player, "meshes/Tails/Swingtail.obj", game->SwingWeapon)
    {
        fillRopeSegments(50);
        m_firingSound.load(resolveAssetPath("audio/shot.mp3").string().c_str());
        m_firingSound.setSingleInstance(true);
        ropeBreakSound.load(resolveAssetPath("audio/RopebreakSound.mp3").string().c_str());
        ropeBreakSound.setSingleInstance(true);
    }

    SwingWeapon::~SwingWeapon()
    {
        destroyHookshot(rechts);
        destroyHookshot(links);
    }

    void SwingWeapon::beforeKillWeapon()
    {
        if (hookshotLeft)
        {
            hookshotLeft->setToDestroy(true);
            hookshotLeft->destroyJoint();
        }
        if (hookshotRight)
        {
            hookshotRight->setToDestroy(true);
            hookshotRight->destroyJoint();
        }
    }

    void SwingWeapon::setActive(bool value)
    {
        if (!value)
        {
            beforeKillWeapon();
        }
        activeWeapon = value;
    }

    void SwingWeapon::shooting(Game* game,float deltaTime)
    {
        auto window = game->getWindow();
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !shotLeft)
        {
            //can only create a new hookshot if there isn't one already
            if (!hookshotLeft) {
                Camera::calculateForwardVector(m_playerFront, m_player->getDrawVec(), Camera::cameraTarget - Camera::cameraFront,
                                               Camera::calculateHorizontalDistance(Camera::fov),
                                               Camera::calculateVerticalDistance(Camera::fov));
                m_audio.play(m_firingSound);
                hookshotLeft = std::make_unique<Hookshot>(game, m_player, convert::glm_to_rp3d(m_playerFront), this, links);
                hookshotLeft->setXRotation(m_player->getXRotation() + 90);
                //hookshotLeft->setYRotation(m_rotationVec.y);
                //y goes into z because of the model
                hookshotLeft->setZRotation(-m_player->getYRotation());
                shotLeft = true;
            }
            //to make sure that only one hookshot is present
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            if (hookshotLeft)
            {
                if (shotLeft)
                {
                    destroyHookshot(links);
                }
            }
            shotLeft = false;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !shotRight)
        {
            //can only create a new hookshot if there isn't one already
            if (!hookshotRight) {
                Camera::calculateForwardVector(m_playerFront, m_player->getDrawVec(), Camera::cameraTarget - Camera::cameraFront,
                                               Camera::calculateHorizontalDistance(Camera::fov),
                                               Camera::calculateVerticalDistance(Camera::fov));
                m_audio.play(m_firingSound);
                hookshotRight = std::make_unique<Hookshot>(game, m_player, convert::glm_to_rp3d(m_playerFront), this, rechts);
                hookshotRight->setXRotation(m_player->getXRotation() + 90);
                //hookshotRight->setYRotation(m_rotationVec.y);
                //y goes into z because of the model
                hookshotRight->setZRotation(-m_player->getYRotation());
                shotRight = true;
            }
            //to make sure that only one hookshot is present
        } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        {
            if (hookshotRight)
            {
                if (shotRight)
                {
                    destroyHookshot(rechts);
                }
            }
            shotRight = false;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            if (hookshotLeft && hookshotRight)
            {
                if (hookshotLeft->getHasHitTarget() && hookshotRight->getHasHitTarget())
                {
                    if (hookshotLeft->getHitTree()->getTreeType() == m_game->pullTree &&
                        hookshotRight->getHitTree()->getTreeType() == m_game->pullTree)
                    {
                        hookshotLeft->destroyJoint();
                        hookshotRight->destroyJoint();
                        rp3d::Vector3 hookshotMiddle = (hookshotRight->getrp3dVec() + hookshotLeft->getrp3dVec()) / 2;
                        rp3d::Vector3 swingDirection = hookshotMiddle - m_player->getBody()->getTransform().getPosition();
                        swingDirection.normalize();
                        swingDirection = {swingDirection.x, swingDirection.y,
                                           swingDirection.z};
                        m_player->getBody()->setLinearVelocity(swingDirection * pullSpeed);
                    }
                }
            }
            else if (hookshotLeft)
            {
                if (hookshotLeft->getHasHitTarget())
                {
                    if (hookshotLeft->getHitTree()->getTreeType() == m_game->pullTree)
                    {
                        hookshotLeft->destroyJoint();
                        hookshotLeft->createJoint(false);
                        rp3d::Vector3 swingDirection = hookshotLeft->getrp3dVec() - m_player->getBody()->getTransform().getPosition();
                        swingDirection.normalize();
                        swingDirection = {swingDirection.x, swingDirection.y,
                                           swingDirection.z};
                        m_player->getBody()->setLinearVelocity(swingDirection * pullSpeed);
                    }
                }
            }
            else if (hookshotRight)
            {
                if (hookshotRight->getHasHitTarget())
                {
                    if (hookshotRight->getHitTree()->getTreeType() == m_game->pullTree)
                    {
                        hookshotRight->destroyJoint();
                        hookshotRight->createJoint(false);
                        rp3d::Vector3 swingDirection = hookshotRight->getrp3dVec() - m_player->getBody()->getTransform().getPosition();
                        swingDirection.normalize();
                        swingDirection = {swingDirection.x, swingDirection.y,
                                          swingDirection.z};
                        m_player->getBody()->setLinearVelocity(swingDirection * pullSpeed);
                    }
                }
            }
            pulling = true;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE)
        {
            if (pulling)
            {
                if (hookshotRight && hookshotLeft)
                {
                    if (hookshotRight->destroyJoint())
                    {
                        hookshotRight->createJoint(true);
                    }
                    if (hookshotLeft->destroyJoint())
                    {
                        hookshotLeft->createJoint(true);
                    }
                }
                else if (hookshotRight)
                {
                    if (hookshotRight->destroyJoint())
                    {
                        hookshotRight->createJoint(true);
                    }
                }
                else if (hookshotLeft)
                {
                    if (hookshotLeft->destroyJoint())
                    {
                        hookshotLeft->createJoint(true);
                    }
                }
                pulling = false;
            }
        }
    }

    void SwingWeapon::handleJoint(bool create, bool BaSJoint)
    {
        if(hookshotLeft)
        {
            if(hookshotLeft->getHasHitTarget())
            {
                hookshotLeft->handleJoint(create, BaSJoint);
            }
        }
        if(hookshotRight)
        {
            if(hookshotRight->getHasHitTarget())
            {
                hookshotRight->handleJoint(create, BaSJoint);
            }
        }
    }

    void SwingWeapon::destroyHookshot(bool rightOne)
    {
        if (rightOne)
        {
            if(hookshotRight)
            {
                m_audio.play(ropeBreakSound);
                checkHitTarget(hookshotRight->getHasHitTarget());
                hookshotRight.reset();
            }
        }
        else
        {
            if(hookshotLeft)
            {
                m_audio.play(ropeBreakSound);
                checkHitTarget(hookshotLeft->getHasHitTarget());
                hookshotLeft.reset();
            }
        }
    }

    void SwingWeapon::checkHitTarget(bool hitTarget)
    {
        if (hitTarget)
        {
            m_player->setWeaponHit(false);
        }
    }

    void SwingWeapon::calculateInterpolateTransform(float accumulator, float timeStep)
    {

    }

    void SwingWeapon::fillRopeSegments(int ropeSegmentCount)
    {
        ropeSegments.clear();
        for(int i = 0; i < ropeSegmentCount; i++)
        {
            auto segment = std::make_unique<Entity>(Shader("Shaders/vertexShader.vert", "Shaders/fragmentShader.frag"),
                                                    Model("meshes/Rope/RopeSegment.obj"),
                                                    m_game,
                                                    m_player->getBody()->getTransform().getPosition(),
                                                    glm::vec3{1.0f, 1.0f, 1.0f},
                                                    glm::vec3{0.3f, 0.3f, 0.3f},
                                                    m_player->getColor());
            ropeSegments.push_back(std::move(segment));
        }
    }

    void SwingWeapon::draw(const Camera& camera)
    {
        if (activeWeapon)
        {
            if (hookshotLeft)
            {
                hookshotLeft->draw(camera);
                if (hookshotLeft->getHasHitTarget() && hookshotLeft->getHitTree())
                {
                    glm::vec3 vectorBetween{glm::normalize(hookshotLeft->getDrawVec() - m_player->getDrawVec())};
                    for (int i = 0; i < ropeSegments.size(); ++i)
                    {
                        // Interpolate between player and static mesh position
                        float t = (float)i / (ropeSegments.size());
                        ropeSegments[i]->setDrawVec(glm::mix(hookshotLeft->getDrawVec(),
                                                             m_player->getDrawVec(),
                                                             t));
                        ropeSegments[i]->setXRotation(vectorBetween.z * 90);
                        ropeSegments[i]->setZRotation(-vectorBetween.x * 90);
                        ropeSegments[i]->draw(camera);
                    }
                }
            }
            if (hookshotRight)
            {
                hookshotRight->draw(camera);
                if (hookshotRight->getHasHitTarget() && hookshotRight->getHitTree())
                {
                    glm::vec3 vectorBetween{glm::normalize(hookshotRight->getDrawVec() - m_player->getDrawVec())};
                    for (int i = 0; i < ropeSegments.size(); ++i)
                    {
                        // Interpolate between player and static mesh position
                        float t = (float)i / (ropeSegments.size());
                        ropeSegments[i]->setDrawVec(glm::mix(hookshotRight->getDrawVec(),
                                                             m_player->getDrawVec(),
                                                             t));
                        ropeSegments[i]->setXRotation(vectorBetween.z * 90);
                        ropeSegments[i]->setZRotation(-vectorBetween.x * 90);
                        ropeSegments[i]->draw(camera);
                    }
                }
            }
            m_tail.setYRotation(m_player->getYRotation() + 90);
            m_tail.draw(camera);
        }
    }

    void SwingWeapon::update(float deltaTime)
    {
        if (activeWeapon)
        {
            if (hookshotLeft)
            {
                hookshotLeft->update(deltaTime);
            }
            if (hookshotRight)
            {
                hookshotRight->update(deltaTime);
            }
        }
    }
}

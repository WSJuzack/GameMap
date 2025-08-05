#pragma once

#include "BlastAwayWeapon.h"
#include "../Game.h"

namespace gl3
{
    BlastAwayWeapon::BlastAwayWeapon(Game* game, Player* player)
    :
    blastRay(player->getrp3dVec(), player->getrp3dVec()),
    Weapon(game, player, "meshes/Tails/Blasttail.obj",game->BlastAwayWeapon)
    {
        raycastBlastAway.setOrigin(game, this);
        m_firingSound.load(resolveAssetPath("audio/BlastSound.mp3").string().c_str());
        m_firingSound.setSingleInstance(true);
    }

    BlastAwayWeapon::~BlastAwayWeapon()
    {

    }

    void BlastAwayWeapon::beforeKillWeapon()
    {

    }

    void BlastAwayWeapon::setActive(bool value)
    {
        activeWeapon = value;
    }

    void BlastAwayWeapon::shooting(gl3::Game *game, float deltaTime)
    {
        auto window = game->getWindow();
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if (!pressedLeft && !blasted)
            {
                pressedLeft = true;
                Camera::calculateForwardVector(m_playerFront, m_player->getDrawVec(), Camera::cameraTarget - Camera::cameraFront,
                                               Camera::calculateHorizontalDistance(Camera::fov),
                                               Camera::calculateVerticalDistance(Camera::fov));
                m_audio.play(m_firingSound);
                blastRay.point1 = m_player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront);
                blastRay.point2 = m_player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront) - convert::glm_to_rp3d(m_playerFront) * blastRange;
                raycastBlastAway.setRightOrLeft(links);
                blasted = true;
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            pressedLeft = false;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            if (!pressedRight && !blasted)
            {
                pressedRight = true;
                Camera::calculateForwardVector(m_playerFront, m_player->getDrawVec(), Camera::cameraTarget - Camera::cameraFront,
                                               Camera::calculateHorizontalDistance(Camera::fov),
                                               Camera::calculateVerticalDistance(Camera::fov));
                m_audio.play(m_firingSound);
                blastRay.point1 = m_player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront);
                blastRay.point2 = m_player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront) - convert::glm_to_rp3d(m_playerFront) * blastRange;
                raycastBlastAway.setRightOrLeft(rechts);
                blasted = true;
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        {
            pressedRight = false;
        }
    }

    void BlastAwayWeapon::calculateBlastAway(rp3d::Vector3 treePosition)
    {
        rp3d::Vector3 _direction = m_player->getrp3dVec() - treePosition;
        _direction.normalize();
        m_player->getBody()->setLinearVelocity(_direction * blastSpeed);
    }

    void BlastAwayWeapon::calculateInterpolateTransform(float accumulator, float timeStep)
    {

    }

    void BlastAwayWeapon::draw(const gl3::Camera &camera)
    {
        if (activeWeapon)
        {
            m_tail.setYRotation(m_player->getYRotation() + 90);
            m_tail.draw(camera);
        }
    }

    void BlastAwayWeapon::update(float deltaTime)
    {
        if (activeWeapon)
        {
            if (blasted)
            {
                m_game->getWorld()->raycast(blastRay, &raycastBlastAway);
                blasted = false;
            }
        }
    }
}
#pragma once

#include "DragWeapon.h"
#include "../Game.h"

namespace gl3
{
    DragWeapon::DragWeapon(Game* game, Player* player)
    :
    selectionRay(player->getrp3dVec(), player->getrp3dVec()),
    Weapon(game, player, "meshes/Tails/Dragtail.obj",game->DragWeapon)
    {
        m_firingSound.load(resolveAssetPath("audio/DragSound.mp3").string().c_str());
        m_firingSound.setSingleInstance(true);
    }

    DragWeapon::~DragWeapon()
    {

    }

    void DragWeapon::beforeKillWeapon()
    {

    }

    void DragWeapon::setActive(bool value)
    {
        activeWeapon = value;
    }

    void DragWeapon::shooting(gl3::Game *game, float deltaTime)
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
                selectionRay.point1 = m_player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront);
                selectionRay.point2 = m_player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront) - convert::glm_to_rp3d(m_playerFront) * selectionRange;
                raycastSelectionRay.setRightOrLeft(links);
                blasted = true;
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            pressedLeft = false;
            if (dragTree && !pressedRight)
            {
                dragTree = nullptr;
            }
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
                selectionRay.point1 = m_player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront);
                selectionRay.point2 = m_player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront) - convert::glm_to_rp3d(m_playerFront) * selectionRange;
                raycastSelectionRay.setRightOrLeft(rechts);
                blasted = true;
            }
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        {
            pressedRight = false;
            if (dragTree && !pressedLeft)
            {
                dragTree = nullptr;
            }
        }
    }

    void DragWeapon::setDragTree(Tree* tree)
    {
        dragTree = tree;
        treeDistance = convert::rp3d_distance(tree->getrp3dVec(), m_player->getrp3dVec());
    }

    void DragWeapon::calculateInterpolateTransform(float accumulator, float timeStep)
    {

    }

    void DragWeapon::update(float deltaTime)
    {
        if (activeWeapon)
        {
            if (blasted)
            {
                m_game->getWorld()->raycast(selectionRay, &raycastSelectionRay);
                blasted = false;
            }
            if (dragTree)
            {
                Camera::calculateForwardVector(m_playerFront, m_player->getDrawVec(), Camera::cameraTarget - Camera::cameraFront,
                                               Camera::calculateHorizontalDistance(Camera::fov),
                                               Camera::calculateVerticalDistance(Camera::fov));
                if (Game::scrollYOffset != 0)
                {
                    treeDistance += Game::scrollYOffset;
                }
                dragTree->setDrawVec(m_player->getDrawVec() + Camera::cameraFront - m_playerFront * treeDistance);
                dragTree->getBody()->setTransform({convert::glm_to_rp3d(dragTree->getDrawVec()), rp3d::Quaternion::identity()});
            }
        }
    }

    void DragWeapon::draw(const gl3::Camera &camera)
    {
        if (activeWeapon)
        {
            m_tail.setYRotation(m_player->getYRotation() + 90);
            m_tail.draw(camera);
        }
    }
}
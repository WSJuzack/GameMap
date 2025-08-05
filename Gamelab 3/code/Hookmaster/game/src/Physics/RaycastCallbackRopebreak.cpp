#pragma once

#include "../Game.h"

namespace gl3 {

    RaycastCallbackRopebreak::RaycastCallbackRopebreak()
    {

    }

    void RaycastCallbackRopebreak::setOrigin(Hookshot *shot, Game* game)
    {
        m_shot = shot;
        m_game = game;
    }

    rp3d::decimal RaycastCallbackRopebreak::notifyRaycastHit(const rp3d::RaycastInfo& info)
    {
        auto userData = (Collision*)info.body->getUserData();
        if (userData != nullptr)
        {
            if (userData->getCollisionBit() == m_game->playerCharacter)
            {
                return -1;
            }
            if (userData->getCollisionBit() == m_game->staticTerrain || userData->getCollisionBit() == m_game->enemy)
            {
                m_shot->setToDestroy(true);
                return 0;
            }
        }
    }
}
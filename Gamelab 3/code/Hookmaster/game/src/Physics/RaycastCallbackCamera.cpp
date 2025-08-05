#include "../Game.h"

namespace gl3 {

    RaycastCallbackCamera::RaycastCallbackCamera()
    {

    }

    void RaycastCallbackCamera::setOrigin(Game* game)
    {
        m_game = game;
    }

    rp3d::decimal RaycastCallbackCamera::notifyRaycastHit(const rp3d::RaycastInfo& info)
    {
        auto userData = (Collision*)info.body->getUserData();
        if(userData != nullptr)
        {
            if (userData->getCollisionBit() == m_game->camera)
            {
                return -1;
            }
            if(userData->getCollisionBit() == m_game->staticTerrain ||
               userData->getCollisionBit() == m_game->wall ||
               userData->getCollisionBit() == m_game->enemy ||
               userData->getCollisionBit() == m_game->goal)
            {
                userData->setCollidedWithRay(true);
            }
        }
        return 1;
    }
}

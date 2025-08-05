#include "../Game.h"

namespace gl3 {

    RaycastCallbackBlastAway::RaycastCallbackBlastAway()
    {

    }

    void RaycastCallbackBlastAway::setOrigin(gl3::Game *game, gl3::BlastAwayWeapon *weapon)
    {
        m_game = game;
        m_weapon = weapon;
    }

    rp3d::decimal RaycastCallbackBlastAway::notifyRaycastHit(const rp3d::RaycastInfo& info)
    {
        auto userData = (Collision*)info.body->getUserData();
        if (userData != nullptr)
        {
            if (userData->getCollisionBit() == m_game->swingSurface)
            {
                Tree* _treePointer = (Tree*)userData;
                if (_treePointer && _treePointer->getTreeType() == m_game->blastTree && _treePointer->getIsActive())
                {
                    if (_treePointer->filterCheck(m_rightOne))
                    {
                        m_weapon->calculateBlastAway(info.worldPoint);
                        return 0;
                    }
                }
            }
        }
        return -1;
    }
}
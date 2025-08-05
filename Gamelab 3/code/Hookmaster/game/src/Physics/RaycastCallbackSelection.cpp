#include "../Game.h"

namespace gl3 {

    RaycastCallbackSelection::RaycastCallbackSelection()
    {

    }

    void RaycastCallbackSelection::setOrigin(Game *game, DragWeapon *weapon)
    {
        m_game = game;
        m_weapon = weapon;
    }

    rp3d::decimal RaycastCallbackSelection::notifyRaycastHit(const rp3d::RaycastInfo& info)
    {
        auto userData = (Collision*)info.body->getUserData();
        if (userData != nullptr)
        {
            if (userData->getCollisionBit() == m_game->swingSurface)
            {
                Tree* _treePointer = (Tree*)userData;
                if (_treePointer && _treePointer->getTreeType() == m_game->dragTree && _treePointer->getIsActive())
                {
                    if (_treePointer->filterCheck(m_rightOne))
                    {
                        _treePointer->setDragTreeForWeapon();
                        return 0;
                    }
                }
            }
        }
        return -1;
    }
}
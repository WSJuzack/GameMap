#include "../Game.h"

namespace gl3 {

    RaycastCallback::RaycastCallback()
    {

    }

    void RaycastCallback::setOrigin(Hookshot *shot, Game* game)
    {
        m_shot = shot;
        m_game = game;
    }

    rp3d::decimal RaycastCallback::notifyRaycastHit(const rp3d::RaycastInfo& info)
    {
        auto userData = (Collision*)info.body->getUserData();
        if (userData != nullptr)
        {
            if (userData->getCollisionBit() == m_game->swingSurface)
            {
                Tree* _treePointer = (Tree*)userData;
                if (userData->getIsActive())
                {
                    if (_treePointer->getTreeType() == m_game->swingTree || _treePointer->getTreeType() == m_game->pullTree)
                    {
                        m_shot->setIntersectionPoint(info.body->getTransform().getPosition());
                        return 0;
                    }
                }
            }
        }
        return -1;
    }
}
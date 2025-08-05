#pragma once

#include "../../../game/src/forward.h"

namespace gl3 {

    class Collision {
    public:
        Collision();

        [[nodiscard]] bool getIsActive() { return isActive; }

        virtual void startCollision(Collision* otherBody);
        virtual void duringCollision(Collision* otherBody);
        virtual void endCollision(Collision* otherBody);
        virtual void startCollisionTrigger(Collision* otherBody);
        virtual void duringCollisionTrigger(Collision* otherBody);
        virtual void endCollisionTrigger(Collision* otherBody);
        virtual short getCollisionBit();
        virtual bool filterCheck(bool check);
        virtual void setCollidedWithRay(bool value) { m_collidedWithRay = value; }
        virtual void setCollidedWithCamera(bool value) { m_collidedWithCamera = value; }
        virtual void setIsActive(bool value) { isActive = value; }

    protected:
        bool isActive = true;
        bool m_collidedWithRay = false;
        bool m_collidedWithCamera = false;
    };
}




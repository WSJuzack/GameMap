#include <iostream>
#include "engine/Collision.h"

namespace gl3{

    Collision::Collision() = default;

    void Collision::startCollisionTrigger(Collision* otherBody)
    {
        std::cout<<"startTriggerBase"<<std::endl;
    }

    void Collision::duringCollisionTrigger(Collision* otherBody)
    {
        std::cout<<"duringTriggerBase"<<std::endl;
    }

    void Collision::endCollisionTrigger(Collision* otherBody)
    {
        std::cout<<"endTriggerBase"<<std::endl;
    }

    void Collision::startCollision(Collision* otherBody)
    {
        std::cout<<"startCollisionBase"<<std::endl;
    }

    void Collision::duringCollision(Collision* otherBody)
    {
        std::cout<<"duringCollisionBase"<<std::endl;
    }

    void Collision::endCollision(Collision* otherBody)
    {
        std::cout<<"endCollisionBase"<<std::endl;
    }

    short Collision::getCollisionBit()
    {
        return 0;
    }

    bool Collision::filterCheck(bool check)
    {
        std::cout<<"filterCheckBase"<<std::endl;
        return false;
    }
}
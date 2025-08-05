#include "engine/Camera.h"
#include "engine/EventListener.h"
#include "../../game/src/Game.h"

namespace gl3 {

    EventListener::EventListener(Game* game)
    {
        game->getWorld()->setEventListener(this);
    }

    Collision *EventListener::voidConvertion_collision(void *p)
    {
        return (Collision*)p;
    }

    void EventListener::onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData)
    {
        //could create infinite loop, if 32bit is wrong
        for(rp3d::uint32 p= 0; p < callbackData.getNbOverlappingPairs(); p++) {

            rp3d::OverlapCallback::OverlapPair overlapPair = callbackData.getOverlappingPair(p);
            OBody1 = voidConvertion_collision(overlapPair.getBody1()->getUserData());
            OBody2 = voidConvertion_collision(overlapPair.getBody2()->getUserData());
            if (overlapPair.getEventType() == rp3d::OverlapCallback::OverlapPair::EventType::OverlapStart)
            {
                OBody1->startCollisionTrigger(OBody2);
                OBody2->startCollisionTrigger(OBody1);
                continue;
            }
            else if (overlapPair.getEventType() == rp3d::OverlapCallback::OverlapPair::EventType::OverlapStay)
            {
                OBody1->duringCollisionTrigger(OBody2);
                OBody2->duringCollisionTrigger(OBody1);
                continue;
            }
            else if (overlapPair.getEventType() == rp3d::OverlapCallback::OverlapPair::EventType::OverlapExit)
            {
                OBody1->endCollisionTrigger(OBody2);
                OBody2->endCollisionTrigger(OBody1);
                continue;
            }
        }
    }

    void EventListener::onContact(const rp3d::CollisionCallback::CallbackData& callbackData)
    {
        //could create infinite loop, if 32bit is wrong
        for (rp3d::uint32 p = 0; p < callbackData.getNbContactPairs(); p++)
        {
            CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);
            OBody1 = voidConvertion_collision(contactPair.getBody1()->getUserData());
            OBody2 = voidConvertion_collision(contactPair.getBody2()->getUserData());
            if (contactPair.getEventType() == rp3d::CollisionCallback::ContactPair::EventType::ContactStart)
            {
                OBody1->startCollision(OBody2);
                OBody2->startCollision(OBody1);
                continue;
            }
            else if (contactPair.getEventType() == rp3d::CollisionCallback::ContactPair::EventType::ContactStay)
            {
                OBody1->duringCollision(OBody2);
                OBody2->duringCollision(OBody1);
                continue;
            }
            else if (contactPair.getEventType() == rp3d::CollisionCallback::ContactPair::EventType::ContactExit)
            {
                OBody1->endCollision(OBody2);
                OBody2->endCollision(OBody1);
                continue;
            }
        }
    }
}
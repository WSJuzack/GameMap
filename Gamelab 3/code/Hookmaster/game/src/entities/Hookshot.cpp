#include "Hookshot.h"
#include "../Game.h"

namespace gl3 {

    Hookshot::Hookshot(gl3::Game* game, Player* player, rp3d::Vector3 direction, SwingWeapon* originWeapon, bool rightOne)
            :
            m_player(player),
            m_direction(direction),
            m_weapon(originWeapon),
            m_rightOne(rightOne),
            endPointRay(player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront),
                        {player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront) - (direction) * 200}),
            ropeBreakRay({m_position, player->getrp3dVec()}),
            Entity(
            Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag"),
            Model("meshes/Hookshot/NewHookshot.obj"),
            game,
            //Position Vector
            player->getrp3dVec(),
            //Rotation Vector
            {0.0f, 0.0f, 0.0f},
            //Scale Vector
            {1.0f, 1.0f, 1.0f},
            //Color Vector
            {1.0f, 1.0f, 1.0f, 1.0f})
            {

        m_drawVec = hookDrawStartLocation(rightOne);

        rp3d::Quaternion orientation = rp3d::Quaternion::identity();
        rp3d::Transform transform ({player->getrp3dVec() + convert::glm_to_rp3d(Camera::cameraFront)}, orientation);
        m_body = game->getWorld()->createRigidBody(transform);
        m_body->setType(rp3d::BodyType::KINEMATIC);

        sphereCollider = physicsCommon.createSphereShape(1);
        m_body->addCollider(sphereCollider, {{0,0,0}, orientation});
        m_body->getCollider(0)->setCollisionCategoryBits(game->hookshot);
        m_body->getCollider(0)->setCollideWithMaskBits(game->swingSurface);
        m_body->getCollider(0)->setIsTrigger(true);
        m_body->setUserData(this);

        rayCaster.setOrigin(this, m_game);
        ropeBreakRayCaster.setOrigin(this, m_game);
        RayCallback(endPointRay);
    }
    Hookshot::~Hookshot()
    {
        m_game->getWorld()->destroyRigidBody(m_body);
        m_body = nullptr;
    }

    void Hookshot::startCollisionTrigger(Collision* otherBody)
    {
        if(otherBody->getIsActive())
        {
            if (otherBody->getCollisionBit() == m_game->swingSurface)
            {
                if (otherBody->filterCheck(m_rightOne))
                {
                    hitTree = (Tree*)otherBody;
                    if (hitTree && hitTree->getTreeType() == m_game->swingTree || hitTree->getTreeType() == m_game->pullTree)
                    {
                        if (otherBody->filterCheck(m_rightOne))
                        {
                            hitTarget = true;
                            m_player->setWeaponHit(hitTarget);
                            m_drawVec = convert::rp3d_to_glm(m_body->getTransform().getPosition());
                            sphereCollider->setRadius(2);
                            m_body->addCollider(sphereCollider, {{0, 0, 0},
                                                                 {0, 0, 0, 1}});
                            m_body->getCollider(1)->setIsTrigger(true);
                            m_body->getCollider(1)->setCollisionCategoryBits(m_game->destroy);
                            m_body->getCollider(1)->setCollideWithMaskBits(m_game->playerCharacter);
                            m_body->getCollider(1)->setUserData(this);
                        }
                        if (m_player->getFlyingState())
                        {
                            createJoint(true);
                        }
                    }
                }
            }
        }
        if(otherBody->getCollisionBit() == m_game->playerCharacter)
        {
            toDestroy = true;
        }
    }

    void Hookshot::duringCollisionTrigger(Collision* otherBody)
    {

    }

    void Hookshot::endCollisionTrigger(Collision* otherBody)
    {

    }

    void Hookshot::startCollision(Collision* otherBody)
    {

    }

    void Hookshot::duringCollision(Collision* otherBody)
    {

    }

    void Hookshot::endCollision(Collision* otherBody)
    {

    }

    short Hookshot::getCollisionBit()
    {
        return m_body->getCollider(0)->getCollisionCategoryBits();
    }

    bool Hookshot::filterCheck(bool check)
    {
        if(m_rightOne == check)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Hookshot::RayCallback(const rp3d::Ray& ray)
    {
        m_game->getWorld()->raycast(ray, &rayCaster);
        calculateHookshotToHit(hookshotToHit, ray, m_intersectionPoint);
    }

    glm::vec3 Hookshot::startLocationSetOff(glm::vec3 vector, const float factor, glm::vec3 playerFront)
    {
        vector.x += playerFront.x * factor;
        vector.y += 0.5f;
        vector.z += playerFront.z * factor;
        return vector;
    }

    glm::vec3 Hookshot::hookDrawStartLocation(bool rightOne)
    {
        glm::vec3 playerFrontDummy;
        if(rightOne)
        {
            Camera::calculateForwardVector(playerFrontDummy, m_player->getDrawVec(), Camera::cameraTarget,
                                           Camera::calculateHorizontalDistance(Camera::fov),
                                           Camera::calculateVerticalDistance(Camera::fov), -90.0f);
            return startLocationSetOff(m_player->getDrawVec(), 0.5f, playerFrontDummy);
        }
        else
        {
            Camera::calculateForwardVector(playerFrontDummy, m_player->getDrawVec(), Camera::cameraTarget,
                                           Camera::calculateHorizontalDistance(Camera::fov),
                                           Camera::calculateVerticalDistance(Camera::fov), 90.0f);
            return startLocationSetOff(m_player->getDrawVec(), 0.5f, playerFrontDummy);
        }
    }

    void Hookshot::calculateHookshotToHit(glm::vec3& hookshotToHit, const rp3d::Ray& hitRay, const rp3d::Vector3& intersectionPoint)
    {
        if(intersectionPoint != rp3d::Vector3 {0,0,0})
        {
            hookshotToHit = convert::rp3d_to_glm(intersectionPoint) - m_drawVec;
            convert::glm_normalize(hookshotToHit);
        }
        else
        {
            hookshotToHit = convert::rp3d_to_glm(endPointRay.point2) - m_drawVec;
            convert::glm_normalize(hookshotToHit);
        }
    }

    void Hookshot::meshMovement(Game* game, float deltaTime)
    {
        rp3d::Vector3 helper = convert::glm_to_rp3d(m_drawVec);
        helper += convert::glm_to_rp3d(hookshotToHit * speed * deltaTime);
        m_drawVec = convert::rp3d_to_glm(helper);
    }

    void Hookshot::hitboxMovement(Game* game, float deltaTime)
    {
        rp3d::Vector3 movementVec = m_body->getTransform().getPosition();
        movementVec -= {m_direction.x * speed * deltaTime,
                        (m_direction.y) * speed * deltaTime,
                        (m_direction.z) * speed * deltaTime};
        rp3d::Transform moveTransform{movementVec, m_body->getTransform().getOrientation()};
        m_body->setTransform(moveTransform);
        ///for debug purposes
        //m_drawVec = convert::rp3d_to_glm(m_body->getTransform().getPosition());
    }

    void Hookshot::handleJoint(bool create, bool BaSJoint)
    {
        if (!hitTarget)
            return;

        if (create)
        {
            createJoint(BaSJoint);
        }
        else
        {
            destroyJoint();
        }
    }

    void Hookshot::createJoint(bool ballandsocket)
    {
        if (m_player->getFlyingState())
        {
            if(ballandsocket)
            {
                if (!BaSJoint)
                {
                    rp3d::BallAndSocketJointInfo jointInfo(m_body,
                                                           m_player->getBody(),
                                                           m_body->getTransform().getPosition());
                    BaSJoint = dynamic_cast<rp3d::BallAndSocketJoint *>(m_game->getWorld()->createJoint(jointInfo));
                    //std::cout<<"BaSJoint"<<std::endl;
                }
            }
            if (!ballandsocket)
            {
                if (!SJoint)
                {
                    rp3d::SliderJointInfo sliderinfo(m_body,
                                                     m_player->getBody(),
                                                     m_body->getTransform().getPosition(),
                                                     rp3d::Vector3(m_body->getTransform().getPosition() - m_player->getBody()->getTransform().getPosition()));
                    SJoint = dynamic_cast<rp3d::SliderJoint*>(m_game->getWorld()->createJoint(sliderinfo));
                    //std::cout<<"SJoint"<<std::endl;
                }
            }
        }
    }

    void Hookshot::update(float deltaTime)
    {
        if (!hitTarget)
        {
            meshMovement(m_game, deltaTime);
            hitboxMovement(m_game, deltaTime);
        }
        else
        {
            //if hit, no more movement
            ropeBreakRay.point1 = convert::glm_to_rp3d(m_drawVec);
            ropeBreakRay.point2 = m_player->getrp3dVec();
            m_game->getWorld()->raycast(ropeBreakRay, &ropeBreakRayCaster);
        }

        if (toDestroy)
        {
            rp3d::Vector3 linearVel = m_game->getPlayer()->getBody()->getLinearVelocity();
            m_game->getPlayer()->getBody()->setLinearVelocity(linearVel / 10);
            m_weapon->destroyHookshot(m_rightOne);
        }
    }

    bool Hookshot::destroyJoint()
    {
        if(BaSJoint)
        {
            m_game->getWorld()->destroyJoint(BaSJoint);
            BaSJoint = nullptr;
            return true;
        }
        else if (SJoint)
        {
            m_game->getWorld()->destroyJoint(SJoint);
            SJoint = nullptr;
            return true;
        }
        return false;
    }
}

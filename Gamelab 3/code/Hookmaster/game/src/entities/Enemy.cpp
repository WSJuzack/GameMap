#include "../Game.h"

namespace gl3 {

    Enemy::Enemy(Game* game, glm::vec3 rotation, glm::vec3 position, glm::vec3 scale, glm::vec3 end, float timeToEndPos, bool isTrigger)
        :
        m_startPos(position),
        m_endPos(end),
        m_time(timeToEndPos),
        Entity(
            Shader("Shaders/treeVertexShader.vert", "Shaders/treeFragmentShader.frag"),
            Model("meshes/Spike/Spike.obj"),
            game,
            //Position Vector
            convert::glm_to_rp3d(position),
            //Rotation Vector
            rotation,
            //Scale Vector
            scale,
            //Color Vector
            {1.0f, 0.0f, 0.0f, 1.0f})
    {
        m_distance = m_endPos - m_startPos;

        rp3d::Quaternion orientation = rp3d::Quaternion::identity();
        rp3d::Transform transform (m_position, orientation);
        m_body = game->getWorld()->createRigidBody(transform);
        m_body->setType(rp3d::BodyType::KINEMATIC);
        m_body->setUserData(this);

        rp3d::BoxShape* boxCollider = physicsCommon.createBoxShape(convert::glm_to_rp3d(scale));
        m_body->addCollider(boxCollider, {{0,0,0}, orientation});
        m_body->getCollider(0)->setCollisionCategoryBits(game->enemy);
        m_body->getCollider(0)->setCollideWithMaskBits(game->playerCharacter);
        m_body->getCollider(0)->setIsTrigger(isTrigger);
        m_drawVec = convert::rp3d_to_glm(m_body->getCollider(0)->getLocalToWorldTransform().getPosition());
    }

    Enemy::~Enemy()
    {
        m_game->getWorld()->destroyRigidBody(m_body);
        m_body = nullptr;
    }

    void Enemy::startCollisionTrigger(Collision* otherBody)
    {
        if (otherBody->getCollisionBit() == m_game->playerCharacter)
        {
            otherBody->filterCheck(true);
        }
    }

    void Enemy::duringCollisionTrigger(Collision* otherBody)
    {

    }

    void Enemy::endCollisionTrigger(Collision* otherBody)
    {

    }

    void Enemy::startCollision(Collision* otherBody)
    {

    }

    void Enemy::duringCollision(Collision* otherBody)
    {

    }

    void Enemy::endCollision(Collision* otherBody)
    {

    }

    short Enemy::getCollisionBit()
    {
        return m_body->getCollider(0)->getCollisionCategoryBits();
    }

    bool Enemy::filterCheck(bool check)
    {
        return false;
    }

    void Enemy::update(float deltaTime)
    {
        elapsedTime += deltaTime;
        if (elapsedTime < m_time)
        {
            if (startToEnd)
            {
                m_drawVec = glm::vec3{m_drawVec.x + m_distance.x / m_time * deltaTime, m_drawVec.y + m_distance.y / m_time * deltaTime, m_drawVec.z + m_distance.z / m_time * deltaTime};
            }
            else
            {
                m_drawVec = glm::vec3{m_drawVec.x - m_distance.x / m_time * deltaTime, m_drawVec.y - m_distance.y / m_time * deltaTime, m_drawVec.z - m_distance.z / m_time * deltaTime};
            }
        }
        else
        {
            elapsedTime = 0;
            startToEnd = !startToEnd;
        }
        m_body->setTransform({convert::glm_to_rp3d(m_drawVec), {0,0,0,1}});
    }

    void Enemy::draw(const gl3::Camera &camera)
    {
        if(m_collidedWithCamera || m_collidedWithRay)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            if (m_collidedWithRay)
            {
                m_collidedWithRay = false;
            }
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        Entity::draw(camera);
        //to make sure ,that nothing else is rendered with just the lines
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
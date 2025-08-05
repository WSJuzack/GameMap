#include "../Game.h"

namespace gl3 {

    Goal::Goal(Game* game, const std::string& modelPath, glm::vec3 position, glm::vec3 scale, bool final)
        :
        m_final(final),
        Entity(
            Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag"),
            Model(modelPath),
            game,
            //Position Vector
            convert::glm_to_rp3d(position),
            //Rotation Vector
            {0.0f, 0.0f, 0.0f},
            //Scale Vector
            scale,
            //Color Vector
            {1.0f, 1.0f, 1.0f, 1.0f})
    {
        initY = position.y;

        rp3d::Quaternion orientation = rp3d::Quaternion::identity();
        rp3d::Transform transform (m_position, orientation);
        m_body = game->getWorld()->createRigidBody(transform);
        m_body->setType(rp3d::BodyType::KINEMATIC);
        m_body->setUserData(this);

        rp3d::BoxShape* boxCollider = physicsCommon.createBoxShape(rp3d::Vector3{0.5f, 0.5f, 0.5f});
        m_body->addCollider(boxCollider, {{0,0,0}, orientation});
        m_body->getCollider(0)->setIsTrigger(true);
        m_body->getCollider(0)->setCollisionCategoryBits(game->goal);
        m_body->getCollider(0)->setCollideWithMaskBits(game->playerCharacter);
        m_drawVec = convert::rp3d_to_glm(m_body->getCollider(0)->getLocalToWorldTransform().getPosition());

        goalSound.load(resolveAssetPath("audio/GoalSounds.mp3").string().c_str());
        goalSound.setSingleInstance(true);

        audio.init();
        audio.setGlobalVolume(0.1f);
    }

    Goal::~Goal()
    {
        m_game->getWorld()->destroyRigidBody(m_body);
        m_body = nullptr;
    }

    void Goal::startCollisionTrigger(Collision* otherBody)
    {
        if (isActive)
        {
            if (otherBody->getCollisionBit() == m_game->playerCharacter)
            {
                if (m_final)
                {
                    if (m_game->getPlayer()->getBananaCollected())
                    {
                        goalReached = true;
                    }
                }
                else
                {
                    m_game->resetLevel();
                    m_game->getPlayer()->setCollectedBanana(true);
                    m_game->getPlayer()->setRespawnLocation(rp3d::Vector3 {m_drawVec.x, initY, m_drawVec.z});
                    isActive = false;
                }
            }
        }
    }

    void Goal::duringCollisionTrigger(Collision* otherBody)
    {

    }

    void Goal::endCollisionTrigger(Collision* otherBody)
    {

    }

    void Goal::startCollision(Collision* otherBody)
    {

    }

    void Goal::duringCollision(Collision* otherBody)
    {

    }

    void Goal::endCollision(Collision* otherBody)
    {

    }

    short Goal::getCollisionBit()
    {
        return m_body->getCollider(0)->getCollisionCategoryBits();
    }

    ///if searching for the final goal -> check = true
    bool Goal::filterCheck(bool check)
    {
        if (check == m_final)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Goal::update(float deltaTime)
    {
        if (isActive)
        {
            if (!m_final)
            {
                sinCache += deltaTime;
                float _yRotation = getYRotation();
                setYRotation(_yRotation + 10 * deltaTime);
                m_body->setTransform({rp3d::Vector3{m_body->getTransform().getPosition().x, initY + sin(sinCache), m_body->getTransform().getPosition().z}, {0, 0, 0, 1}});
            }
            if (goalReached)
            {
                m_game->setNextLevel(true);
                audio.play(goalSound);
            }
        }
    }

    void Goal::draw(const gl3::Camera &camera)
    {
        if (isActive)
        {
            if (m_collidedWithCamera || m_collidedWithRay)
            {
                if (m_collidedWithRay)
                {
                    m_collidedWithRay = false;
                }
            }
            else
            {
                Entity::draw(camera);
            }
        }
    }
}
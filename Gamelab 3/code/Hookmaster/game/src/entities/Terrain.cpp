#include "Terrain.h"
#include "../Game.h"

namespace gl3 {
    Terrain::Terrain(Game* game, const std::string& modelPath,
                     glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, int terrainType, bool invisible)
        :
        Entity(
            Shader("Shaders/vertexShader.vert", "Shaders/fragmentShader.frag"),
            Model(modelPath),
            game,
            //Position Vector
            convert::glm_to_rp3d(position),
            //Rotation Vector
            rotation,
            //Scale Vector
            scale,
            //Color Vector
            color)
        {

        rp3d::Quaternion orientation = rp3d::Quaternion::identity();
        rp3d::Transform transform (m_position, orientation);
        m_body = game->getWorld()->createRigidBody(transform);
        m_body->setType(rp3d::BodyType::STATIC);
        m_body->setUserData(this);

        rp3d::BoxShape* boxCollider = physicsCommon.createBoxShape(rp3d::Vector3 {scale.x, scale.y / 2, scale.z});
        m_body->addCollider(boxCollider, {{0,scale.y / 2,0}, orientation});
        m_drawVec = convert::rp3d_to_glm(m_body->getCollider(0)->getLocalToWorldTransform().getPosition());
        //need to be added - otherwise player is floating - probably the models fault
        m_drawVec.y += 0.5f;
        if (terrainType == game->staticTerrain)
        {
            m_body->getCollider(0)->setCollisionCategoryBits(game->staticTerrain);
        }
        if (terrainType == game->wall)
        {
            m_body->getCollider(0)->setCollisionCategoryBits(game->wall);
        }
        m_body->getCollider(0)->setCollideWithMaskBits(game->playerCharacter | game->camera);

        isInvisible = invisible;
    }
    Terrain::~Terrain()
    {
        m_game->getWorld()->destroyRigidBody(m_body);
        m_body = nullptr;
    }

    void Terrain::startCollisionTrigger(Collision* otherBody)
    {

    }

    void Terrain::duringCollisionTrigger(Collision* otherBody)
    {

    }

    void Terrain::endCollisionTrigger(Collision* otherBody)
    {

    }

    void Terrain::startCollision(Collision* otherBody)
    {

    }

    void Terrain::duringCollision(Collision* otherBody)
    {

    }

    void Terrain::endCollision(Collision* otherBody)
    {

    }

    short Terrain::getCollisionBit()
    {
        return m_body->getCollider(0)->getCollisionCategoryBits();
    }

    void Terrain::draw(const Camera& camera)
    {
        if(isInvisible || m_collidedWithCamera || m_collidedWithRay)
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
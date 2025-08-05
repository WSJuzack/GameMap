#include "Tree.h"
#include "../Game.h"

namespace gl3 {

    Tree::Tree(Game* game, rp3d::Vector3 position, glm::vec3 rotation, glm::vec3 scale, int treeType,
               const std::filesystem::path& modelPath, bool isFiltered, bool rightOne)
        :
        originalPosition(position),
        m_treeType(treeType),
        m_rightOne(rightOne),
        m_isFiltered(isFiltered),
        Entity(
            Shader("Shaders/treeVertexShader.vert", "Shaders/treeFragmentShader.frag"),
            Model(modelPath.string()),
            game,
            //Position Vector
            position,
            //Rotation Vector
            rotation,
            //Scale Vector
            scale){

        rp3d::Quaternion orientation = rp3d::Quaternion::identity();
        rp3d::Transform transform (m_position, orientation);
        m_body = game->getWorld()->createRigidBody(transform);
        m_body->setType(rp3d::BodyType::STATIC);

        rp3d::BoxShape* boxCollider = physicsCommon.createBoxShape(convert::glm_to_rp3d(scale));
        m_body->addCollider(boxCollider, {{0,0,0},orientation});
        m_body->getCollider(0)->setCollisionCategoryBits(game->swingSurface);
        m_body->getCollider(0)->setCollideWithMaskBits(game->playerCharacter | game->hookshot);
        m_body->getCollider(0)->setIsTrigger(true);
        m_body->setUserData(this);

        setFilteredColor();
    }

    Tree::~Tree()
    {
        m_game->getWorld()->destroyRigidBody(m_body);
        m_body = nullptr;
    }

    //Collision Events
    void Tree::startCollisionTrigger(Collision* otherBody)
    {

    }

    void Tree::duringCollisionTrigger(Collision* otherBody) {

    }

    void Tree::endCollisionTrigger(Collision* otherBody) {

    }

    void Tree::startCollision(Collision* otherBody) {

    }

    void Tree::duringCollision(Collision* otherBody) {

    }

    void Tree::endCollision(Collision* otherBody) {

    }

    short Tree::getCollisionBit()
    {
        return m_body->getCollider(0)->getCollisionCategoryBits();
    }

    bool Tree::filterCheck(bool check)
    {
        if(m_isFiltered)
        {
            if (check == m_rightOne)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    void Tree::setIsActive(bool value)
    {
        if (isActive != value)
        {
            isActive = value;
            setFilteredColor();
        }
        if (value)
        {
            if (m_treeType == m_game->dragTree)
            {
                m_body->setTransform({originalPosition, {0, 0, 0, 1}});
                m_drawVec = convert::rp3d_to_glm(originalPosition);
                m_body->getCollider(0)->setIsTrigger(true);
            }
        }
    }

    void Tree::setDragTreeForWeapon()
    {
        m_game->getPlayer()->setDragTreeWeapon(this);
        m_body->getCollider(0)->setIsTrigger(false);
    }

    void Tree::setFilteredColor()
    {
        if(m_isFiltered)
        {
            if(m_rightOne)
            {
                m_color = glm::vec4 {0,0,1,1};
            }
            else
            {
                m_color = glm::vec4 {0,1,0,1};
            }
        }
        else
        {
            m_color = glm::vec4{0,1,1,1};
        }
    }

    void Tree::draw(const Camera& camera)
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
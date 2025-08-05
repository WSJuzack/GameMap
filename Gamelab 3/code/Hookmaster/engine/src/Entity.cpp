#include "engine/Entity.h"
#include "../../game/src/Game.h"

namespace gl3 {
    Entity::Entity(Shader&& shader, Model&& mesh, Game* game, rp3d::Vector3 position,
                   glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
            : m_shader(std::move(shader)),
              m_model(std::move(mesh)),
              m_game(game),
              m_position(position),
              m_drawVec(convert::rp3d_to_glm(position)),
              m_rotationVec(rotation),
              m_scale(scale),
              m_color(color)
              {

              }

    void Entity::startCollisionTrigger(Collision* otherBody)
    {
        std::cout<<"Entity Baseclass startCollisionTrigger"<<std::endl;
    }

    void Entity::duringCollisionTrigger(Collision* otherBody)
    {
        std::cout<<"Entity Baseclass duringCollisionTrigger"<<std::endl;
    }

    void Entity::endCollisionTrigger(Collision* otherBody)
    {
        std::cout<<"Entity Baseclass endCollisionTrigger"<<std::endl;
    }

    void Entity::startCollision(Collision* otherBody)
    {
        std::cout<<"Entity Baseclass startCollision"<<std::endl;
    }

    void Entity::duringCollision(Collision* otherBody)
    {
        std::cout<<"Entity Baseclass duringCollision"<<std::endl;
    }

    void Entity::endCollision(Collision* otherBody)
    {
        std::cout<<"Entity Baseclass endCollision"<<std::endl;
    }

    short Entity::getCollisionBit()
    {
        return 0;
    }

    bool Entity::filterCheck(bool check)
    {
        std::cout<<"Entity filterCheck"<<std::endl;
        return false;
    }

    void Entity::calculateInterpolateTransform(float accumulator, float timeStep)
    {
        if (getCollisionBit() == m_game->enemy)
        {
            return;
        }
        float factor = accumulator / timeStep;
        m_drawVec = convert::rp3d_to_glm(rp3d::Transform::interpolateTransforms(prevTransform, m_body->getTransform(), factor).getPosition());
        prevTransform = m_body->getTransform();
    }

    void Entity::draw(const Camera& camera)
    {
        auto mvpMatrix = camera.calculateMvpMatrix(m_drawVec, m_rotationVec, m_scale);
        auto modelMatrix = camera.calculateModelMatrix(m_drawVec, m_rotationVec, m_scale);
        auto viewMatrix = camera.calculateViewMatrix();
        auto projectionMatrix = camera.calculateProjectionMatrix();
        m_shader.use();
        m_shader.setMatrix("mvp", mvpMatrix);
        m_shader.setMatrix("modelToWorldNormal", calculateModelToWorldNormal());
        m_shader.setMatrix("model", modelMatrix);
        m_shader.setMatrix("view", viewMatrix);
        m_shader.setMatrix("projection", projectionMatrix);
        m_shader.setVector("color", m_color);
        m_shader.setVector("viewPos", Camera::cameraPos);
        m_model.Draw(m_shader);
    }

    glm::mat4 Entity::calculateModelToWorldNormal() const
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_drawVec);
        model = glm::scale(model, m_scale);
        model = glm::rotate(model, glm::radians(m_rotationVec.z), glm::vec3(0.0f, 0.0f, 1.0f));
        return glm::transpose(glm::inverse(model));
    }

    void Entity::update(float deltaTime)
    {

    }
}
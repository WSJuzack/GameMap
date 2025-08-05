#pragma once

#include "../../../game/src/forward.h"
#include "reactphysics3d/reactphysics3d.h"
#include "glm/vec3.hpp"
#include <iostream>
#include "engine/Collision.h"
#include "engine/Mesh.h"
#include "engine/Shader.h"
#include "engine/Model.h"


namespace gl3 {

    class Entity : public Collision {
    public:
        Entity(Shader&& shader, Model&& model, Game* game,
               rp3d::Vector3 position = rp3d::Vector3(0.0f, 0.0f, 0.0f),
               glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f),
               glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        virtual ~Entity() = default;
        virtual void update(float deltaTime);
        virtual void draw(const Camera& camera);
        virtual void calculateInterpolateTransform(float accumulator, float timeStep);
        void startCollisionTrigger(Collision* otherBody) override;
        void duringCollisionTrigger(Collision* otherBody) override;
        void endCollisionTrigger(Collision* otherBody) override;
        void startCollision(Collision* otherBody) override;
        void duringCollision(Collision* otherBody) override;
        void endCollision(Collision* otherBody) override;
        short getCollisionBit() override;
        bool filterCheck(bool check) override;

        [[nodiscard]] rp3d::RigidBody* getBody() { return m_body; }
        [[nodiscard]] float getXRotation() const { return m_rotationVec.x; }
        [[nodiscard]] float getYRotation() const { return m_rotationVec.y; }
        [[nodiscard]] float getZRotation() const { return m_rotationVec.z; }
        [[nodiscard]] const glm::vec3 &getScale() const { return m_scale; }
        [[nodiscard]] const glm::vec4 &getColor() const {return  m_color;}
        [[nodiscard]] glm::vec3 getDrawVec() const { return m_drawVec; }
        [[nodiscard]] rp3d::Vector3 getrp3dVec() const { return m_body->getTransform().getPosition(); }
        void setDrawVec(const glm::vec3& position) { m_drawVec = position; }
        void setXRotation (float xRotation) { m_rotationVec.x = xRotation; } // in Grad
        void setYRotation (float yRotation) { m_rotationVec.y = yRotation; }
        void setZRotation(float zRotation) { m_rotationVec.z = zRotation; }
        void setScale(const glm::vec3 &scale) { m_scale = scale; }
        void setColor(const glm::vec4 &color) { m_color = color; }
        void setBody(rp3d::RigidBody* value) { m_body = value; }

    private:

        [[nodiscard]] glm::mat4 calculateModelToWorldNormal() const;

    protected:
        float radius = 1;
        Game* m_game = nullptr;
        Model m_model;
        glm::vec3 m_rotationVec {0.0f,0.0f,0.0f};
        glm::vec3 m_scale = glm::vec3 {0.0f};
        glm::vec4  m_color = glm::vec4 {1.0f};
        rp3d::Vector3 m_position = rp3d::Vector3 {0.0f, 0.0f, 0.0f};
        rp3d::RigidBody* m_body = nullptr;
        rp3d::PhysicsCommon physicsCommon;
        rp3d::Transform prevTransform;
        Shader m_shader;
        glm::vec3 m_drawVec;
    };
}

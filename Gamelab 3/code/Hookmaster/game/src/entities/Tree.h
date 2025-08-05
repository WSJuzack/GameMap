#pragma once

#include "../forward.h"
#include "reactphysics3d/reactphysics3d.h"
#include "engine/Entity.h"
#include "tiny_gltf/tiny_gltf.h"

namespace gl3 {


    class Tree : public Entity {
    public:
        Tree(Game* game, rp3d::Vector3 position, glm::vec3 rotation, glm::vec3 scale,
             int treeType, const std::filesystem::path& modelPath, bool isFiltered, bool rightOne = true);
        ~Tree();

        bool hookshotCheck(bool RightOne);
        [[nodiscard]] int getTreeType() const { return m_treeType; }

        void draw(const gl3::Camera &camera) override;
        void startCollisionTrigger(Collision* otherBody) override;
        void duringCollisionTrigger(Collision* otherBody) override;
        void endCollisionTrigger(Collision* otherBody) override;
        void startCollision(Collision* otherBody) override;
        void duringCollision(Collision* otherBody) override;
        void endCollision(Collision* otherBody) override;
        short getCollisionBit() override;
        bool filterCheck(bool check) override;
        void setIsActive(bool value) override;
        void setFilteredColor();
        void setDragTreeForWeapon();

    private:
        rp3d::Vector3 originalPosition;
        bool m_rightOne;
        bool m_isFiltered;
        int m_treeType;
    };
}


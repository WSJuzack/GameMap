#pragma once

#include "Weapon.h"
#include "../physics/RaycastCallbackSelection.h"

namespace gl3
{
    class DragWeapon : public Weapon {
    public:
        DragWeapon(Game* game, Player* player);
        ~DragWeapon();

        void setDragTree(Tree* tree);

        void setActive(bool value) override;
        void shooting(Game* game,float deltaTime) override;
        void beforeKillWeapon() override;
        void draw(const Camera& camera) override;
        void update(float deltaTime) override;
        void calculateInterpolateTransform(float accumulator, float timeStep) override;

    private:
        bool pressedRight;
        bool pressedLeft;
        bool blasted;
        RaycastCallbackSelection raycastSelectionRay;
        rp3d::Ray selectionRay;
        float selectionRange = 50.0f;
        Tree* dragTree = nullptr;
        float treeDistance;
    };
}

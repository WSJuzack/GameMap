#pragma once

#include "../forward.h"
#include "reactphysics3d/reactphysics3d.h"
#include "glm/vec3.hpp"
#include <soloud.h>
#include <soloud_wav.h>
#include "engine/Entity.h"

namespace gl3
{
    class Weapon {
    public:
        Weapon(Game* game, Player* player, const std::filesystem::path& tailAssetPath, int weaponType);

        [[nodiscard]] bool getActive() const { return activeWeapon; }
        virtual void setActive(bool value) { activeWeapon = value; }
        [[nodiscard]] int getWeaponType() const { return m_weaponType; }
        [[nodiscard]] Entity* getTailptr() { return &m_tail; }

        virtual void shooting(Game* game, float deltaTime);
        virtual void beforeKillWeapon();
        virtual void update(float deltaTime);
        virtual void draw(const Camera& camera);
        virtual void calculateInterpolateTransform(float accumulator, float timeStep);

    protected:
        Game* m_game = nullptr;
        SoLoud::Soloud m_audio;
        SoLoud::Wav m_firingSound;
        Player* m_player;
        glm::vec3 m_playerFront;
        bool activeWeapon;
        const int m_weaponType;
        Entity m_tail;
    };
}
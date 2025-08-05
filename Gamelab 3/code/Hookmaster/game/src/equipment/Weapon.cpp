#include <iostream>
#include "Weapon.h"
#include "../entities/Player.h"

namespace gl3
{
    Weapon::Weapon(Game* game, Player* player, const std::filesystem::path& tailAssetPath, int weaponType)
    :
    m_tail(Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag"),
           Model(tailAssetPath.string()),
           game,
           player->getrp3dVec(),
           glm::vec3{player->getXRotation(), player->getYRotation() + 90, player->getZRotation()},
           player->getScale() / 2.0f,
            //color
           {1, 1, 1, 1}),
    m_game(game),
    m_player(player),
    m_weaponType(weaponType)
    {
        m_audio.init();
        m_audio.setGlobalVolume(0.1f);
    }

    void Weapon::shooting(Game* game,float deltaTime)
    {
        std::cout<<"We are in base shooting()"<<std::endl;
    }

    void Weapon::beforeKillWeapon()
    {
        std::cout<<"in baseclass Weapon beforeKillWeapon()"<<std::endl;
    }

    void Weapon::calculateInterpolateTransform(float accumulator, float timeStep)
    {
        std::cout<<"in baseclass Weapon calculateInterpolateTransform"<<std::endl;
    }

    void Weapon::update(float deltaTime)
    {
        std::cout<<"in baseclass Weapon update"<<std::endl;
    }

    void Weapon::draw(const Camera& camera)
    {
        std::cout<<"in baseclass Weapon draw"<<std::endl;
    }
}
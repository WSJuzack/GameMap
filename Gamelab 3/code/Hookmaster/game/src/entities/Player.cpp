#include "Player.h"
#include "../Game.h"
//used for testing
#include "glm/gtx/string_cast.hpp"


namespace gl3
{
    Player::Player(Game* game, rp3d::Vector3 position, glm::vec3 rotation, glm::vec3 scale)
            :
            Entity(
                    Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag"),
                    Model("meshes/Player/Player.obj"),
                    game,
                    position,
                    rotation,
                    scale,
                    //color
                    {1, 1, 1, 1}) {
        //creating a rigidBody to simulate physics
        m_orientation = {0, 0, 0, 1};
        rp3d::Transform transform (m_position, m_orientation);
        m_body = game->getWorld()->createRigidBody(transform);
        m_body->setType(rp3d::BodyType::DYNAMIC);
        m_body->enableGravity(true);
        m_body->setMass(100.0f);

        //creating the colliders for the rigidBody
        sphereCollider = physicsCommon.createSphereShape(radius);
        //Collider are LOCAL SPACE not global space
        m_body->addCollider(sphereCollider, {{0,0,0}, m_orientation});
        m_body->getCollider(0)->setCollisionCategoryBits(game->playerCharacter);
        m_body->getCollider(0)->setCollideWithMaskBits(game->staticTerrain | game->swingSurface | game->destroy | game->goal | game->enemy | game->wall);
        m_body->setUserData(this);

        //creating audio for the player
        audio.init();
        audio.setGlobalVolume(0.1f);
        deathSound.load(resolveAssetPath("audio/deathSound.mp3").string().c_str());
        deathSound.setSingleInstance(true);

        //creating all Weapons for the player


        weaponInit();
    }
    Player::~Player()
    {
        activeWeapon->beforeKillWeapon();
        m_game->getWorld()->destroyRigidBody(m_body);
        m_body = nullptr;
    }

    void Player::setFlyingState(bool value)
    {
        if (value != isFlying)
        {
            isFlying = value;
            if (activeWeapon->getWeaponType() == m_game->SwingWeapon)
            {
                SwingWeapon* swingPointer = (SwingWeapon*)activeWeapon;
                if (swingPointer)
                {
                    swingPointer->handleJoint(isFlying, true);
                }
            }
            if (isFlying)
            {
                isMoving = false;
            }
        }
    }

    void Player::weaponInit()
    {
        ///-------------------------------------------------------------------------------------------------------------
        auto SWeapon = std::make_unique<SwingWeapon>(m_game, this);
        playerWeapons.push_back(std::move(SWeapon));

        auto BAWeapon = std::make_unique<BlastAwayWeapon>(m_game, this);
        playerWeapons.push_back(std::move(BAWeapon));

        auto DWeapon = std::make_unique<DragWeapon>(m_game, this);
        playerWeapons.push_back(std::move(DWeapon));
        ///-------------------------------------------------------------------------------------------------------------

        activeWeapon = playerWeapons[0].get();
        currentWeaponIndex = 0;
        activeWeapon->setActive(true);

    }

    void Player::startCollisionTrigger(Collision* otherBody)
    {

    }

    void Player::duringCollisionTrigger(Collision* otherBody)
    {

    }

    void Player::endCollisionTrigger(Collision* otherBody)
    {

    }

    void Player::startCollision(Collision* otherBody)
    {
        if(otherBody->getCollisionBit() == m_game->staticTerrain || otherBody->getCollisionBit() == m_game->swingSurface)
        {
            setFlyingState(false);
            m_body->setLinearVelocity({m_body->getLinearVelocity().x / 10, 0, m_body->getLinearVelocity().z / 10});
        }
    }

    void Player::duringCollision(Collision* otherBody)
    {
        if(otherBody->getCollisionBit() == m_game->staticTerrain || otherBody->getCollisionBit() == m_game->swingSurface)
        {
            setFlyingState(false);
        }
    }

    void Player::endCollision(Collision* otherBody)
    {
        if(otherBody->getCollisionBit() == m_game->staticTerrain || otherBody->getCollisionBit() == m_game->swingSurface)
        {
            setFlyingState(true);
            m_body->setLinearVelocity({m_body->getLinearVelocity().x / 2.0f,
                                       m_body->getLinearVelocity().y,
                                       m_body->getLinearVelocity().z / 2.0f});
        }

        if (activeWeapon->getWeaponType() == m_game->SwingWeapon)
        {
            SwingWeapon* swingPointer = (SwingWeapon*)activeWeapon;
            if (swingPointer)
            {
                swingPointer->handleJoint(true, true);
            }
        }
    }

    short Player::getCollisionBit()
    {
        return m_body->getCollider(0)->getCollisionCategoryBits();
    }

    bool Player::filterCheck(bool check)
    {
        if (check)
        {
            playerDeath();
            return true;
        }
        return false;
    }

    void Player::gatherMovementKeys(Game *game, float deltaTime)
    {
        //A unified place to make sure every Movement can use the same Variables
        auto window = game->getWindow();
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            APressed = true;
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
        {
            APressed = false;
        }

        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            DPressed = true;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
        {
            DPressed = false;
        }

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            WPressed = true;
        }
        else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
        {
            WPressed = false;
        }

        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            SPressed = true;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
        {
            SPressed = false;
        }

        if (isFlying && !godMode)
        {
            manageAirMovement(WPressed, APressed, SPressed, DPressed, deltaTime);
        }
        else
        {
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                SpacePressed = true;
            }
            else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
            {
                SpacePressed = false;
            }
            manageGroundMovement(WPressed, APressed, SPressed, DPressed, SpacePressed);
        }
    }

    void Player::manageAirMovement(bool WKey, bool AKey, bool SKey, bool DKey, float deltaTime)
    {
        if (WKey)
        {
            calculateAirMovement(0, deltaTime);
        }
        if (AKey)
        {
            calculateAirMovement(-90, deltaTime);
        }
        if (SKey)
        {
            calculateAirMovement(180, deltaTime);
        }
        if (DKey)
        {
            calculateAirMovement(90, deltaTime);
        }
    }

    void Player::manageGroundMovement(bool WKey, bool AKey, bool SKey, bool DKey, bool spaceKey)
    {
        //no movements keys -> no need for calculations
        if (!WKey && !AKey && !SKey && !DKey)
        {
            stopMovement();
        }
        //if opposite keys are pressed, no movement
        else if ((WKey && SKey) || (AKey && DKey))
        {
            stopMovement();
        }
        //Diagonally front and left
        else if (WKey && AKey && !SKey && !DKey)
        {
            calculateGroundMovement(-45);
        }
        //Diagonally front and right
        else if (WKey && !AKey && !SKey && DKey)
        {
            calculateGroundMovement(45);
        }
        //Diagonally back and left
        else if (!WKey && AKey && SKey && !DKey)
        {
            calculateGroundMovement(-135);
        }
        //Diagonally back and right
        else if (!WKey && !AKey && SKey && DKey)
        {
            calculateGroundMovement(135);
        }
        //Walking forward
        else if (WKey && !AKey && !SKey && !DKey)
        {
            calculateGroundMovement(0);
        }
        //Walking backward
        else if (!WKey && !AKey && SKey && !DKey)
        {
            calculateGroundMovement(180);
        }
        //Walking leftward
        else if (!WKey && AKey && !SKey && !DKey)
        {
            calculateGroundMovement(-90);
        }
        //Walking rightward
        else if (!WKey && !AKey && !SKey && DKey)
        {
            calculateGroundMovement(90);
        }
        if (spaceKey)
        {
            calculateJump();
        }
    }

    void Player::calculateGroundMovement(float degree)
    {
        Camera::calculateForwardVector(m_playerFront, m_drawVec, m_drawVec, Camera::calculateHorizontalDistance(Camera::fov, 2.5f),
                                       Camera::calculateVerticalDistance(Camera::fov, 2.5f), degree);
        rp3d::Vector3 forceVec;
        forceVec.x -= m_playerFront.x * groundSpeed;
        forceVec.z -= m_playerFront.z * groundSpeed;
        m_body->setLinearVelocity(forceVec);
        isMoving = true;
    }

    void Player::calculateAirMovement(float degree, float deltaTime)
    {
        Camera::calculateForwardVector(m_playerFront, m_drawVec, m_drawVec, Camera::calculateHorizontalDistance(Camera::fov, 2.5f),
                                       Camera::calculateVerticalDistance(Camera::fov, 2.5f), degree);
        rp3d::Vector3 forceVec;
        forceVec.x -= m_playerFront.x * airSpeed * m_body->getMass() / 2;
        forceVec.z -= m_playerFront.z * airSpeed * m_body->getMass() / 2;
        m_body->applyWorldForceAtCenterOfMass(forceVec * deltaTime);
        isMoving = true;
    }

    void Player::calculateJump()
    {
        rp3d::Vector3 _linearVelocity;
        _linearVelocity = m_body->getLinearVelocity();
        if (isMoving)
        {
            //running and jumping gets 10 units of distance forward
            m_body->setLinearVelocity(rp3d::Vector3 {_linearVelocity.x * 2, 5, _linearVelocity.z * 2});
        }
        else
        {
            //vertical jump gets 8 units of distance upwards
            m_body->setLinearVelocity(rp3d::Vector3 {_linearVelocity.x, 15, _linearVelocity.z});
        }
    }

    void Player::stopMovement()
    {
        if(isMoving)
        {
            m_body->setLinearVelocity({0,0,0});
            m_body->setAngularVelocity({0,0,0});
            isMoving = false;
        }
    }

    void Player::weaponSwap(bool firstWeapon)
    {
        if (firstWeapon)
        {
            if (!playerWeapons.empty())
            {
                currentWeaponIndex = 0;
                activeWeapon->setActive(false);
                activeWeapon = playerWeapons[currentWeaponIndex].get();
                activeWeapon->setActive(true);
            }
        }
        auto window = m_game->getWindow();
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            if (!playerWeapons.empty() && !weaponSwapLock)
            {
                weaponSwapLock = true;
                if (currentWeaponIndex + 1 < playerWeapons.size())
                {
                    currentWeaponIndex++;
                    activeWeapon->setActive(false);
                    activeWeapon = playerWeapons[currentWeaponIndex].get();
                    activeWeapon->setActive(true);
                }
                else
                {
                    currentWeaponIndex = 0;
                    activeWeapon->setActive(false);
                    activeWeapon = playerWeapons[currentWeaponIndex].get();
                    activeWeapon->setActive(true);
                }
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
        {
            weaponSwapLock = false;
        }
    }

    void Player::setDragTreeWeapon(Tree* tree)
    {
        for(int i = 0; i < playerWeapons.size(); i++)
        {
            if (playerWeapons[i]->getWeaponType() == m_game->DragWeapon)
            {
                DragWeapon* _dragWeapon = (DragWeapon*)playerWeapons[i].get();
                _dragWeapon->setDragTree(tree);
            }
        }
    }

    void Player::calculateInterpolateTransform(float accumulator, float timeStep)
    {
        Entity::calculateInterpolateTransform(accumulator, timeStep);
        activeWeapon->calculateInterpolateTransform(accumulator, timeStep);
        Camera::calculateForwardVector(m_playerFront, activeWeapon->getTailptr()->getDrawVec(),
                                       activeWeapon->getTailptr()->getDrawVec(),
                                       Camera::calculateHorizontalDistance(Camera::fov),
                                       Camera::calculateVerticalDistance(Camera::fov));
        activeWeapon->getTailptr()->setDrawVec(glm::vec3 {m_drawVec.x + m_playerFront.x, m_drawVec.y - 0.2f, m_drawVec.z + m_playerFront.z});
    }

    void Player::playerDeath()
    {
        audio.play(deathSound);
        activeWeapon->beforeKillWeapon();
        weaponSwap(true);
        m_body->setTransform({respawnLocation, {0,0,0,1}});
        m_body->setLinearVelocity({0,0,0});
        m_body->setAngularVelocity({0,0,0});
        m_game->resetLevel();
    }

    void Player::update(float deltaTime)
    {
        auto window = m_game->getWindow();
        //if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        //{
        //    godMode = !godMode;
        //    audio.play(deathSound);
        //}

        if (movementLock)
        {
            movementLockCooldown += deltaTime;
            if (movementLockCooldown >= 0.5f)
            {
                movementLockCooldown = 0.0f;
                movementLock = false;
            }
        }
        else
        {
            gatherMovementKeys(m_game, deltaTime);
        }

        weaponSwap();

        activeWeapon->shooting(m_game, deltaTime);
        activeWeapon->update(deltaTime);

        m_body->setLinearVelocity(rp3d::clamp(m_body->getLinearVelocity(), 30));

        if(m_body->getTransform().getPosition().y <= -30 && !weaponHit)
        {
            playerDeath();
        }
    }

    void Player::draw(const Camera& camera)
    {
        Camera::getPlayerPosition(*this);
        Camera::setPlayerRotation(*this);
        Entity::draw(camera);
        activeWeapon->draw(camera);
    }
}
#pragma once
#include <memory>
#include "forward.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "reactphysics3d/reactphysics3d.h"
#include <soloud.h>
#include <soloud_wav.h>
#include "Scene.h"
#include "engine/Entity.h"
#include "entities/Player.h"
#include "entities/Terrain.h"
#include "entities/Tree.h"
#include "entities/Goal.h"
#include "entities/Enemy.h"
#include "engine/World.h"
#include "engine/Assets.h"
#include "engine/convert.h"
#include "engine/Camera.h"
#include "equipment/Weapon.h"
#include "equipment/SwingWeapon.h"
#include "equipment/BlastAwayWeapon.h"
#include "equipment/DragWeapon.h"
#include "engine/EventListener.h"
#include "physics/RaycastCallback.h"
#include "physics/RaycastCallbackCamera.h"
#include "physics/RaycastCallbackRopebreak.h"
#include "Physics/RaycastCallbackBlastAway.h"
#include "physics/RaycastCallbackSelection.h"
#include "../Triangle.h"
#include "engine/Skybox.h"
#include "engine/Game.h"


namespace gl3 {
	
class Game: public engine::Game {

    public:
        Game(int width, int height, const std::string &title);
        virtual ~Game();
        void run() override;
        [[nodiscard]] Player* getPlayer() const { return player; }
        [[nodiscard]] rp3d::PhysicsWorld* getWorld() const { return physicsWorld; }
        [[nodiscard]] Camera* getCamera() const { return cam.get(); }
        [[nodiscard]] float getTimeStep() const { return timeStep; }
        [[nodiscard]] float getWindowWidth() const { return m_windowWidth; }
        [[nodiscard]] float getWindowHeight() const { return m_windowHeight; }
        [[nodiscard]] float getDeltaTime() const { return deltaTime; }

        void resetLevel();
        void destroyLevel();
        void changeLevel(int index);
        void nextLevel();

        void fillEntities(std::unique_ptr<Terrain> terrain) { entities.push_back(std::move(terrain)); }
        void fillEntities(std::unique_ptr<Tree> tree) { entities.push_back(std::move(tree)); }
        void fillEntities(std::unique_ptr<Enemy> enemy) { entities.push_back(std::move(enemy)); }
        void fillEntities(std::unique_ptr<Goal> goal) { entities.push_back(std::move(goal)); }

        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        static double scrollXOffset;
        static double scrollYOffset;

        enum Category
        {
            staticTerrain = 1 << 0,
            playerCharacter = 1 << 1,
            hookshot = 1 << 2,
            destroy = 1 << 3,
            swingSurface = 1 << 4,
            camera = 1 << 5,
            enemy = 1 << 6,
            goal = 1 << 7,
            wall = 1 << 8
        };
        enum Weapons
        {
            SwingWeapon = 1 << 0,
            BlastAwayWeapon = 1 << 1,
            DragWeapon = 1 << 2
        };
        enum Trees
        {
            swingTree = 1 << 0,
            pullTree = 1 << 1,
            blastTree = 1 << 2,
            dragTree = 1 << 3
        };

        void endGame() override;

    private:

        void physics() override;
        void update() override;
        void draw() override;
        void updateDeltaTime() override;

      std::unique_ptr<Camera> cam;
      Player* player = nullptr;
      std::unique_ptr<SoLoud::Wav> backgroundMusic;
      float lastFrameTime = 0.0f;
      float deltaTime = 1.0f/60;
      float pitch = 0.0f;
      float accumulator = 0;
      //physics
      const float timeStep = 1.0/144;
      rp3d::PhysicsWorld* physicsWorld = nullptr;
      rp3d::PhysicsCommon physicsCommon;

      Triangle Triangle;
    };
}

#pragma once
#include <memory>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "reactphysics3d/reactphysics3d.h"
#include <soloud.h>
#include <soloud_wav.h>
#include "engine/Events.h"
#include "engine/Context.h"
#include "engine/Events.h"
#include "engine/ecs/ComponentManager.h"
#include "engine/ecs/EntityManager.h"
#include "engine/Camera.h"
#include "engine/Skybox.h"

namespace gl3::engine {

    class Game {
    public:

        using event_t = events::Event<Game, Game&>;

        event_t onStartup;
        event_t onAfterStartup;
        event_t onBeforeUpdate;
        event_t onAfterUpdate;
        event_t onBeforeShutdown;
        event_t onShutdown;

        [[nodiscard]] GLFWwindow* getWindow() const { return window; }

        Game(int width, int height, const std::string &title);
        virtual ~Game();
        virtual void run();

        void setStopGame(bool value) { stopGame = value; }
        void setNextLevel(bool value) { createNextLevel = value; }
        void resetLevel();
        void destroyLevel();
        void changeLevel(int index);
        void nextLevel();

        GLFWwindow *window = nullptr;

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

        virtual void endGame();
        static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

        virtual void physics();
        virtual void update();
        virtual void draw();
        virtual void updateDeltaTime();

        std::vector<std::unique_ptr<Entity>> entities;
        std::unique_ptr<Shader> shader;
        int physicsCount = 0;
        unsigned int VAO;
        unsigned int VBO;
        float m_windowWidth;
        float m_windowHeight;
        SoLoud::Soloud audio;
        std::unique_ptr<SoLoud::Wav> backgroundMusic;
        float lastFrameTime = 0.0f;
        float deltaTime = 1.0f/60;
        float pitch = 0.0f;
        float accumulator = 0;
        bool stopGame = false;
        bool createNextLevel = false;
        Skybox* m_skybox = nullptr;
        Scene* m_scene = nullptr;
        //physics
        const float timeStep = 1.0/144;
    };
}

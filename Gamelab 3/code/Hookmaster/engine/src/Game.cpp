#include "engine/Game.h"
#include "tiny_gltf/stb_image.h"
#include "engine/Entity.h"

namespace gl3::engine {

    using Context = engine::context::Context;
    using ecs::ComponentManager;
    using ecs::EntityManager;

    void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }


    Game::Game(int width, int height, const std::string &title)
    {
        if(!glfwInit())
        {
            throw std::runtime_error("Failed to initialize glfw");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
        if(window == nullptr)
        {
            throw std::runtime_error("Failed to create window");
        }


        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, Camera::mouse_callback);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glEnable(GL_DEPTH_TEST);
        if(glGetError() != GL_NO_ERROR)
        {
            throw std::runtime_error("gl error");
        }

        m_windowHeight = height;
        m_windowWidth = width;
        audio.init();
        audio.setGlobalVolume(0.1f);
    }

    void Game::run()
    {
        onStartup.invoke(*this);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Game::update()
    {
        for(auto &entity: entities)
        {
            if (entity)
            {
                entity->update(deltaTime);
            }
        }
    }

    void Game::physics()
    {
        accumulator += deltaTime;
        while(accumulator >= timeStep)
        {
            accumulator -= timeStep;
            physicsCount++;
        }

        for(auto &entity: entities)
        {
            entity->calculateInterpolateTransform(accumulator, timeStep);
        }
    }

    void Game::draw()
    {
        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    void Game::updateDeltaTime()
    {
        double frameTime = glfwGetTime();
        deltaTime = frameTime - lastFrameTime;
        lastFrameTime = frameTime;
    }

    void Game::endGame()
    {
        glfwSetWindowShouldClose(window, true);
    }

    Game::~Game()
    {
        glfwTerminate();
    }
}

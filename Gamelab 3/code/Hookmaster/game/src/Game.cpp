#include "engine/World.h"
#include "Game.h"
#include "engine/Assets.h"
#include "tiny_gltf/stb_image.h"
#include "engine/Game.h"

namespace gl3 {

    double Game::scrollXOffset = 0;
    double Game::scrollYOffset = 0;

    void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        //both are set to 0 at the end of Update() to better use them in the controls
        scrollXOffset = xoffset;
        scrollYOffset = yoffset;
    }


    Game::Game(int width, int height, const std::string &title)
    :
    engine::Game(width, height, title)
    {
        glfwSetCursorPosCallback(window, Camera::mouse_callback);
    }

    void Game::run()
    {
        engine::Game::run();

        glfwSetScrollCallback(window, Game::scroll_callback);

        //World creation -> all Entities below those two lines of code
        World myWorldSettings;
        physicsWorld = physicsCommon.createPhysicsWorld(myWorldSettings.settings);

        EventListener eventListener(this);

        //player
        auto swingMonkey = std::make_unique<Player>(this, rp3d::Vector3(0, 1, 0));
        player = swingMonkey.get();

        Skybox mySkybox(this);
        m_skybox = &mySkybox;

        Scene myScene(this);
        m_scene = &myScene;

        m_scene->setupLevelFromIndex(0);

        cam = std::make_unique<Camera>(window, this, m_windowHeight, m_windowWidth);

        backgroundMusic = std::make_unique<SoLoud::Wav>();
        backgroundMusic->load(resolveAssetPath("audio/Background Loop mit Intro.mp3").string().c_str());
        backgroundMusic->setLooping(true);
        backgroundMusic->setLoopPoint(6.5);
        audio.playBackground(*backgroundMusic);

        while(!glfwWindowShouldClose(window))
        {
            updateDeltaTime();
            glfwPollEvents();
            update();
            physics();
            draw();
            if (stopGame)
            {
                endGame();
            }
        }
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }


    void Game::resetLevel()
    {
       for(int i = 0; i < entities.size(); i++)
       {
           if (entities[i]->getCollisionBit() == swingSurface)
           {
               entities[i]->setIsActive(true);
           }
       }
       backgroundMusic->stop();
       audio.playBackground(*backgroundMusic);
    }

    void Game::destroyLevel()
    {
        entities.clear();
    }

    void Game::nextLevel()
    {
        changeLevel(m_scene->getLevelIndex() + 1);
    }

    void Game::changeLevel(int index)
    {
        destroyLevel();
        player->setCollectedBanana(false);
        player->setRespawnLocation(rp3d::Vector3{0.0f, 1.0f, 0.0f});
        m_scene->setupLevelFromIndex(index);
        backgroundMusic->stop();
        audio.playBackground(*backgroundMusic);
    }

    void Game::update()
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            endGame();
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            changeLevel(1);
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            changeLevel(2);
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        {
            changeLevel(3);
        }
        if (createNextLevel)
        {
            nextLevel();
            createNextLevel = false;
        }

        cam->update();
        for(auto &entity: entities)
        {
            if (entity)
            {
                entity->update(deltaTime);
            }
        }
        player->update(deltaTime);

        Game::scrollYOffset = 0;
        Game::scrollXOffset = 0;
    }

    void Game::physics()
    {
        accumulator += deltaTime;
        while(accumulator >= timeStep)
        {
            physicsWorld->update(timeStep);
            accumulator -= timeStep;
        }
        for(auto &entity: entities)
        {
            entity->calculateInterpolateTransform(accumulator, timeStep);
        }
        player->calculateInterpolateTransform(accumulator, timeStep);
    }

    void Game::draw()
    {
        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_skybox->draw();

        for(auto &entity: entities)
        {
            if (entity)
            {
                entity->draw(*cam);
            }
        }
        
        player->draw(*cam);

        Triangle.drawCrosshair(window);

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
        destroyLevel();
    }
}

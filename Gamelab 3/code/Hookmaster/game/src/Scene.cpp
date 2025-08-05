#include "Scene.h"

namespace gl3
{

    Scene::Scene(Game* game)
    :
    m_game(game)
    {

    }

    Scene::~Scene()
    {

    }

    //creating the objects for the level with the corresponding index
    void Scene::setupLevelFromIndex(int index)
    {
        switch(index)
        {
            case 0:
                setupTutorial();
                break;
            case 1:
                setupLevelOne();
                break;
            case 2:
                setupLevelTwo();
                break;
            case 3:
                setupLevelThree();
                break;
            default:
                setupLevelOne();
                break;
        }
        m_game->getPlayer()->getBody()->setTransform({{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}});
        m_game->getPlayer()->setMovementLock(true);
    }

    void Scene::setupTutorial()
    {
        ///-------------------------------------------------------------------------------------------------------------

        //Terrain
        //first platform
        auto platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                                  glm::vec3{20.0f, 30.0f, 20.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //vertical jump tutorial platform
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f , -30.0f, 30.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 38.0f, 9.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //long jump tutorial platform
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f , -30.0f, 60.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 38.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //swing tree tutorial platform
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{100.0f , -30.0f, 60.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 38.0f, 20.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //pull tree tutorial platform
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{100.0f , -30.0f, 160.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 38.0f, 20.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //blast tree tutorial platform
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{-10.0f , -30.0f, 160.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 38.0f, 20.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //drag tree tutorial platform/goal
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{-10.0f , -30.0f, 230.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 38.0f, 20.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));

        //anti-cheat walls
        //first left wall
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{25.0f , -30.0f, 10.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{5.0f, 110.0f, 30.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //first right wall
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{-20.5f , -30.0f, 30.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 110.0f, 50.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //back wall
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f , -30.0f, -20.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 110.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to the right of the swing jump
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{30.0f , -30.0f, 79.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{50.0f, 110.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to the left of the swing jump
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{70.0f , -30.0f, 40.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{50.0f, 110.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to prevent too early use of pullTree
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{79.5f , -30.0f, 72.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 110.0f, 7.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to prevent too early use of pullTree
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{79.5f , -30.0f, 47.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 110.0f, 7.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to the right of the pull
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{79.5f , -30.0f, 110.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 110.0f, 30.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to the left of the pull
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{120.5f , -30.0f, 110.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 110.0f, 70.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to the right of the blast jump
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{25.0f , -30.0f, 139.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{55.0f, 110.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to the left of the blast jump
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{65.5f , -30.0f, 180.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{55.5f, 110.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to the left of the drag jump
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{10.5f , -30.0f, 215.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 110.0f, 35.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall to the right of the drag jump
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{-30.5f , -30.0f, 195.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 110.0f, 56.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall at the back of the goal
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{-10.0f , -30.0f, 250.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{21.0f, 110.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //Direction Arrows
        platform = std::make_unique<Terrain>(m_game, "meshes/Arrow/arrow_01.obj", glm::vec3{0.0f , 4.0f, 20.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{2.0f, 2.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //Ground
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/WorksideNoVehicle.obj", glm::vec3{0.0f, -30.0f, 100.0f}, glm::vec3{0.0f, 90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/WorksideNoVehicle.obj", glm::vec3{0.0f, -30.0f, 200.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/WorksideNoVehicle.obj", glm::vec3{100.0f, -30.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{100.0f, -30.0f, 100.0f}, glm::vec3{0.0f, 90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{100.0f, -30.0f, 200.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        ///-------------------------------------------------------------------------------------------------------------

        //Tree
        //swing tutorial
        auto tree = std::make_unique<Tree>(m_game, rp3d::Vector3{45.0f, 13.0f, 65.0f}, glm::vec3{90.0f, 0.0f, 90.0f},
                                           glm::vec3{1.0f, 1.0f, 1.0f}, m_game->swingTree, "meshes/Magnet/Magnet.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Crane.obj", glm::vec3{43.0f, -30.0f, 45.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{1.0f, 1.1f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/CraneRope.obj", glm::vec3{56.0f, -4.5f, 66.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 0.6f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //swing tutorial
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{45.0f, 13.0f, 55.0f}, glm::vec3{90.0f, 0.0f, 90.0f},
                                           glm::vec3{1.0f, 1.0f, 1.0f}, m_game->swingTree, "meshes/Magnet/Magnet.obj", true, links);
        m_game->fillEntities(std::move(tree));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/CraneRope.obj", glm::vec3{56.0f, -4.5f, 56.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 0.6f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //pull tutorial
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{100.0f , 8.0f, 70.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", false);
        m_game->fillEntities(std::move(tree));
        //pull tutorial
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{100.0f , 8.0f, 160.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", false);
        m_game->fillEntities(std::move(tree));
        //blast tutorial
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{75.0f, 3.0f, 160.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 2.0f}, m_game->blastTree, "meshes/Trampoline/Trampoline.obj", false);
        m_game->fillEntities(std::move(tree));
        platform = std::make_unique<Terrain>(m_game, "meshes/TrampolineBuilding/Frame.obj", glm::vec3{75.0f, -30.0f, 160.0f}, glm::vec3{0.0f, 180.0f, 0.0f},
                                             glm::vec3{2.0f, 32.5f, 2.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //blast tutorial
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{15.0f, 3.0f, 160.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 2.0f}, m_game->blastTree, "meshes/Trampoline/Trampoline.obj", false);
        m_game->fillEntities(std::move(tree));
        platform = std::make_unique<Terrain>(m_game, "meshes/TrampolineBuilding/Frame.obj", glm::vec3{15.0f, -30.0f, 160.0f}, glm::vec3{0.0f, 180.0f, 0.0f},
                                             glm::vec3{2.0f, 32.5f, 2.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //drag tutorial
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{-10.0f, 10.0f, 195.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{3.0f, 1.0f, 5.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", false);
        m_game->fillEntities(std::move(tree));

        ///-------------------------------------------------------------------------------------------------------------

        //Goal
        auto goal = std::make_unique<Goal>(m_game, "meshes/Banana/Bananas.obj", glm::vec3{-10.0f , 9.0f, 230.0f}, glm::vec3{0.25f, 0.25f, 0.25f}, false);
        m_game->fillEntities(std::move(goal));

        goal = std::make_unique<Goal>(m_game, "meshes/Basket/Basket.obj", glm::vec3{0.0f, 1.0f, -10.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, true);
        m_game->fillEntities(std::move(goal));

        ///-------------------------------------------------------------------------------------------------------------

        //Enemies
        //enemy tutorial in the pull section
        auto enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{115.0f, -2.0f, 110.0f}, glm::vec3{5.0f, 3.0f, 30.0f},
                                             glm::vec3{115.0f, 15.0f, 110.0f}, 5);
        m_game->fillEntities(std::move(enemy));
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{105.0f, -2.0f, 110.0f}, glm::vec3{5.0f, 3.0f, 30.0f},
                                        glm::vec3{105.0f, 15.0f, 110.0f}, 5);
        m_game->fillEntities(std::move(enemy));
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{95.0f, -2.0f, 110.0f}, glm::vec3{5.0f, 3.0f, 30.0f},
                                        glm::vec3{95.0f, 15.0f, 110.0f}, 5);
        m_game->fillEntities(std::move(enemy));
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{85.0f, -2.0f, 110.0f}, glm::vec3{5.0f, 3.0f, 30.0f},
                                        glm::vec3{85.0f, 15.0f, 110.0f}, 5);
        m_game->fillEntities(std::move(enemy));

        //enemy tutorial in the pull section
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{115.0f, 15.0f, 110.0f}, glm::vec3{5.0f, 3.0f, 30.0f},
                                        glm::vec3{115.0f, 15.0f, 110.0f}, 3);
        m_game->fillEntities(std::move(enemy));
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{105.0f, 15.0f, 110.0f}, glm::vec3{5.0f, 3.0f, 30.0f},
                                        glm::vec3{105.0f, 15.0f, 110.0f}, 3);
        m_game->fillEntities(std::move(enemy));
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{95.0f, 15.0f, 110.0f}, glm::vec3{5.0f, 3.0f, 30.0f},
                                        glm::vec3{95.0f, 15.0f, 110.0f}, 3);
        m_game->fillEntities(std::move(enemy));
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{85.0f, 15.0f, 110.0f}, glm::vec3{5.0f, 3.0f, 30.0f},
                                        glm::vec3{85.0f, 15.0f, 110.0f}, 3);
        m_game->fillEntities(std::move(enemy));


        ///-------------------------------------------------------------------------------------------------------------
        m_levelIndex = 0;
    }

    void Scene::setupLevelOne()
    {
        ///-------------------------------------------------------------------------------------------------------------

        //Terrain
        //first platform
        auto platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                                  glm::vec3{20.0f, 30.0f, 20.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //platform after first jump
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f , -30.0f, 140.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 45.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //platform after the big enemies
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 280.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 35.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //first wall -> tree at the top
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, -30.0f, 320.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 50.0f, 4.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //second wall -> tree at the bottom
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, 0.0f, 370.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 50.0f, 2.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //goal location
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 420.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 30.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));

        //anti-cheat walls
        //level wall on the left
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{20.5f, -30.0f, 210.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 80.0f, 230.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //level wall on the right
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{-20.5f, -30.0f, 210.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 80.0f, 230.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //back wall
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f , -30.0f, -20.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 110.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall before jump back pull tree
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, 30.0f, 150.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 20.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //back wall behind the goal
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, -30.0f, 440.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{21.0f, 80.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //Directional Arrows
        platform = std::make_unique<Terrain>(m_game, "meshes/Arrow/arrow_01.obj", glm::vec3{0.0f, 35.0f, 149.5f}, glm::vec3{180.0f, 0.0f, 0.0f},
                                             glm::vec3{4.0f, 4.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //Ground
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/WorksideNoVehicle.obj", glm::vec3{0.0f, -30.0f, 100.0f}, glm::vec3{0.0f, 90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/WorksideNoVehicle.obj", glm::vec3{0.0f, -30.0f, 200.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 300.0f}, glm::vec3{0.0f, 180.0f, 0.0f},
                                              glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 400.0f}, glm::vec3{0.0f, 180.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        ///-------------------------------------------------------------------------------------------------------------

        //Trees
        //first swing between two enemies
        auto tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.5f, 9.0f, 50.0f}, glm::vec3{180.0f, 0.0f, 0.0f},
                                           glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Crane.obj", glm::vec3{20.0f, -30.0f, 47.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.1f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/CraneRope.obj", glm::vec3{11.5f, -17.0f, 52.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 0.85f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //pull tree to get onto the second platform
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 15.0f, 150.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", true, links);
        m_game->fillEntities(std::move(tree));
        //jump back before the two enemies
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 42.0f, 150.5f}, glm::vec3{90.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        //first tree to lead the player under the enemy
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, -5.0f, 169.0f}, glm::vec3{90.0f, 0.0f, 0.0f},
                                           glm::vec3{1.0f, 1.0f, 1.0f}, m_game->swingTree, "meshes/Magnet/Magnet.obj", true, links);
        m_game->fillEntities(std::move(tree));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Crane.obj", glm::vec3{-20.0f, -30.0f, 171.0f}, glm::vec3{0.0f, 90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.2f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/CraneRope.obj", glm::vec3{11.5f, -56.0f, 171.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.7f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //second tree below the enemy
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, -6.0f, 214.0f}, glm::vec3{90.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->swingTree, "meshes/Magnet/Magnet.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Crane.obj", glm::vec3{20.0f, -30.0f, 211.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 0.84f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/CraneRope.obj", glm::vec3{11.0f, -31.0f, 216.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 0.85f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //pull tree to get back up from under the enemy
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 5.0f, 275.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", true, links);
        m_game->fillEntities(std::move(tree));
        //pull on top of the first wall
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 25.5f, 320.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", false);
        m_game->fillEntities(std::move(tree));
        //pull at the bottom of the second wall
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, -4.0f, 370.0f}, glm::vec3{180.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", false);
        m_game->fillEntities(std::move(tree));

        ///-------------------------------------------------------------------------------------------------------------

        //Goal
        auto goal = std::make_unique<Goal>(m_game,  "meshes/Banana/Bananas.obj", glm::vec3{0.0f, 2.0f, 420.0f}, glm::vec3{0.25f, 0.25f, 0.25f}, false);
        m_game->fillEntities(std::move(goal));

        goal = std::make_unique<Goal>(m_game,  "meshes/Basket/Basket.obj", glm::vec3{0.0f, 1.0f, -10.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, true);
        m_game->fillEntities(std::move(goal));

        ///-------------------------------------------------------------------------------------------------------------

        //Enemies
        //first jump enemy coming from the right
        auto enemy = std::make_unique<Enemy>(m_game, glm::vec3{90.0f, 0.0f, 0.0f}, glm::vec3{-19.0f, 2.0f, 30.0f}, glm::vec3{3.0f, 7.0f, 5.0f},
                                             glm::vec3{19.0f, 2.0f, 30.0f}, 4);
        m_game->fillEntities(std::move(enemy));
        //first jump enemy coming from the left
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{90.0f, 0.0f, 0.0f}, glm::vec3{19.0f, 2.0f, 30.0f}, glm::vec3{3.0f, 7.0f, 5.0f},
                                             glm::vec3{-19.0f, 2.0f, 30.0f}, 4);
        m_game->fillEntities(std::move(enemy));
        //big enemy -> have to swing from under it
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{-10.0f, 2.0f, 210.0f}, glm::vec3{10.0f, 7.0f, 30.0f},
                                        glm::vec3{10.0f, 2.0f, 210.0f}, 3);
        m_game->fillEntities(std::move(enemy));
        //enemy obscuring the view to the pullTrees
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 25.0f, 210.0f}, glm::vec3{10.0f, 7.0f, 30.0f},
                                        glm::vec3{0.0f, 16.0f, 210.0f}, 3);
        m_game->fillEntities(std::move(enemy));

        ///-------------------------------------------------------------------------------------------------------------
        m_levelIndex = 1;
    }

    void Scene::setupLevelTwo()
    {
        ///-------------------------------------------------------------------------------------------------------------

        //Terrain
        //starting platform
        auto platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                                  glm::vec3{20.0f, 30.0f, 20.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //platform after first jump
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 80.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                            glm::vec3{20.0f, 60.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //front wall of the first tube
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, 40.0f, 90.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 30.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //back wall of the first tube
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, -30.0f, 140.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 80.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //left wall of the first tube
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{10.0f, -30.0f, 115.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 80.0f, 25.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //right wall of the first tube
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{-10.0f, -30.0f, 115.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 80.0f, 25.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //platform between tubes
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30, 150}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 90.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //front wall of the second tube
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, -30.0f, 160.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 80.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //back wall of the second tube
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, 30.0f, 210.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 50.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //left wall of the second tube
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{10.0f, 10.0f, 185.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 60.0f, 25.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //right wall of the second tube
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{-10.0f, 10.0f, 185.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 60.0f, 25.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //banana location
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 240.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 60.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));

        //anti-cheat walls
        //level wall on the left
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{20.5f, -30.0f, 120.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 100.0f, 140.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //level wall on the right
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{-20.5f, -30.0f, 120.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 100.0f, 140.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //back wall
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f , -30.0f, -20.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 110.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall behind the goal
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, -30.0f, 260.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{21.0f, 100.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //Ground
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/WorksideNoVehicle.obj", glm::vec3{0.0f, -30.0f, 100.0f}, glm::vec3{0.0f, 90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/WorksideNoVehicle.obj", glm::vec3{0.0f, -30.0f, 200.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 300.0f}, glm::vec3{0.0f, 180.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        ///-------------------------------------------------------------------------------------------------------------

        //Trees
        //first jump trampoline
        auto tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, -5.0f, 30.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                           glm::vec3{2.0f, 1.0f, 2.0f}, m_game->blastTree, "meshes/Trampoline/Trampoline.obj", false);
        m_game->fillEntities(std::move(tree));
        platform = std::make_unique<Terrain>(m_game, "meshes/TrampolineBuilding/Frame.obj", glm::vec3{0.0f, -30.0f, 30.0f}, glm::vec3{0.0f, 180.0f, 0.0f},
                                             glm::vec3{2.0f, 24.5f, 2.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //second trampoline to get into the tube
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 25.0f, 100.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 2.0f}, m_game->blastTree, "meshes/Trampoline/Trampoline.obj", true, links);
        m_game->fillEntities(std::move(tree));
        platform = std::make_unique<Terrain>(m_game, "meshes/TrampolineBuilding/Frame.obj", glm::vec3{0.0f, -30.0f, 100.0f}, glm::vec3{0.0f, 180.0f, 0.0f},
                                             glm::vec3{2.0f, 54.5f, 2.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //first tube first wall jump
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 40.0f, 139.0f}, glm::vec3{-90.0f, 0.0f, 0.0f},
                                      glm::vec3{3.0f, 3.0f, 1.0f}, m_game->blastTree, "meshes/Trampoline/Trampoline.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        //first tube second wall jump
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 70.0f, 91.0f}, glm::vec3{90.0f, 0.0f, 0.0f},
                                      glm::vec3{3.0f, 3.0f, 1.0f}, m_game->blastTree, "meshes/Trampoline/Trampoline.obj", true, links);
        m_game->fillEntities(std::move(tree));
        //second tube first wall jump
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{9.0f, 20.0f, 190.0f}, glm::vec3{0.0f, 0.0f, 90.0f},
                                      glm::vec3{1.0f, 3.0f, 3.0f}, m_game->blastTree, "meshes/Trampoline/Trampoline.obj", true, links);
        m_game->fillEntities(std::move(tree));
        //second tube second wall jump
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{-9.0f, 45.0f, 185.0f}, glm::vec3{0.0f, 0.0f, -90.0f},
                                      glm::vec3{1.0f, 3.0f, 3.0f}, m_game->blastTree, "meshes/Trampoline/Trampoline.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        //second tube third wall jump
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 60.0f, 209.0f}, glm::vec3{-90.0f, 0.0f, 0.0f},
                                      glm::vec3{3.0f, 3.0f, 1.0f}, m_game->blastTree, "meshes/Trampoline/Trampoline.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        //bottom of second tube
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 26.0f, 210.0f}, glm::vec3{180.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", false);
        m_game->fillEntities(std::move(tree));

        ///-------------------------------------------------------------------------------------------------------------

        //Goal
        auto goal = std::make_unique<Goal>(m_game,  "meshes/Banana/Bananas.obj", glm::vec3{0.0f, 32.0f, 240.0f}, glm::vec3{0.25f, 0.25f, 0.25f}, false);
        m_game->fillEntities(std::move(goal));

        goal = std::make_unique<Goal>(m_game,  "meshes/Basket/Basket.obj", glm::vec3{0.0f, 1.0f, -10.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, true);
        m_game->fillEntities(std::move(goal));

        ///-------------------------------------------------------------------------------------------------------------

        //Enemy

        ///-------------------------------------------------------------------------------------------------------------
        m_levelIndex = 2;
    }

    void Scene::setupLevelThree()
    {
        ///-------------------------------------------------------------------------------------------------------------

        //Terrain
        auto platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 0.0f}, glm::vec3{0.0f, 0.0f,0.0f},
                                                  glm::vec3{20.0f, 30.0f, 20.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //platform after bridge
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 90.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 30.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //platform after steps
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 140.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 40.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //great wall of wall
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -2.0f, 180.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 20.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //platform after under wall swing
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 205.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 30.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));
        //banana location
        platform = std::make_unique<Terrain>(m_game, "meshes/House/HouseConstructionSite.obj", glm::vec3{0.0f, -30.0f, 250.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{10.0f, 50.0f, 10.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->staticTerrain);
        m_game->fillEntities(std::move(platform));

        //anti-cheat walls
        //level wall on the right
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{-20.5f, -30.0f, 125.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 80.0f, 145.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //level wall on the left
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{20.5f, -30.0f, 125.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{0.5f, 80.0f, 145.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //back wall
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f , -30.0f, -20.5f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 110.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        //wall behind the goal
        platform = std::make_unique<Terrain>(m_game, "meshes/Skyscraper/Skyscraper.obj", glm::vec3{0.0f, -30.0f, 270.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{21.0f, 80.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //directional Arrows
        platform = std::make_unique<Terrain>(m_game, "meshes/Arrow/arrow_01.obj", glm::vec3{0.0f, 15.0f, 179.5f}, glm::vec3{180.0f, 0.0f, 0.0f},
                                             glm::vec3{3.0f, 3.0f, 0.5f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));

        //Ground
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 100.0f}, glm::vec3{0.0f, 90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 200.0f}, glm::vec3{0.0f, -90.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);
        m_game->fillEntities(std::move(platform));
        platform = std::make_unique<Terrain>(m_game, "meshes/Ground/Workside.obj", glm::vec3{0.0f, -30.0f, 300.0f}, glm::vec3{0.0f, 180.0f, 0.0f},
                                             glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec4{0.9f, 0.9f, 0.9f, 1.0f}, m_game->wall);

        ///-------------------------------------------------------------------------------------------------------------

        //Tree
        //first bridge part
        auto tree = std::make_unique<Tree>(m_game, rp3d::Vector3{15.0f, 0.0f, 35.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                           glm::vec3{2.0f, 1.0f, 4.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", false);
        m_game->fillEntities(std::move(tree));
        //second bridge part
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{-15.0f, 0.0f, 55.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 4.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", false);
        m_game->fillEntities(std::move(tree));
        //third bridge part
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{15.0f, 0.0f, 75.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 4.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", false);
        m_game->fillEntities(std::move(tree));
        //first step part
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 0.0f, 120.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 3.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", false);
        m_game->fillEntities(std::move(tree));
        //second step part
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 5.0f, 125.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 3.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", false);
        m_game->fillEntities(std::move(tree));
        //falling saver
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 0.0f, 160.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 2.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        //swing behind the wall
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, -3.0f, 180.0f}, glm::vec3{180.0f, 0.0f, 0.0f},
                                      glm::vec3{1.0f, 1.0f, 1.0f}, m_game->pullTree, "meshes/Spule/Spule.obj", false);
        m_game->fillEntities(std::move(tree));
        //after swing first ladder
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{-10.0f, 15.0f, 210.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 3.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        //after swing second ladder
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{0.0f, 15.0f, 210.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 3.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", true, rechts);
        m_game->fillEntities(std::move(tree));
        //after swing third ladder
        tree = std::make_unique<Tree>(m_game, rp3d::Vector3{10.0f, 15.0f, 210.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                      glm::vec3{2.0f, 1.0f, 3.0f}, m_game->dragTree, "meshes/Beam/SteelBeam.obj", true, rechts);
        m_game->fillEntities(std::move(tree));

        ///-------------------------------------------------------------------------------------------------------------

        //Goal
        auto goal = std::make_unique<Goal>(m_game,  "meshes/Banana/Bananas.obj", glm::vec3{0.0f, 22.0f, 250.0f}, glm::vec3{0.25f, 0.25f, 0.25f}, false);
        m_game->fillEntities(std::move(goal));

        goal = std::make_unique<Goal>(m_game,  "meshes/Basket/Basket.obj", glm::vec3{0.0f, 1.0f, -10.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, true);
        m_game->fillEntities(std::move(goal));

        ///-------------------------------------------------------------------------------------------------------------

        //Enemy
        //first bridge enemy
        auto enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 90.0f, 0.0f}, glm::vec3{0.0f, 10.0f, 40.0f}, glm::vec3{20.0f, 1.0f, 1.0f},
                                             glm::vec3{0.0f, -10.0f, 40.0f}, 2);
        m_game->fillEntities(std::move(enemy));
        //second bridge enemy
        enemy = std::make_unique<Enemy>(m_game, glm::vec3{0.0f, 90.0f, 0.0f}, glm::vec3{0.0f, -10.0f, 60.0f}, glm::vec3{20.0f, 1.0f, 1.0f},
                                        glm::vec3{0.0f, 10.0f, 60.0f}, 2);
        m_game->fillEntities(std::move(enemy));

        ///-------------------------------------------------------------------------------------------------------------
        m_levelIndex = 3;
    }
}
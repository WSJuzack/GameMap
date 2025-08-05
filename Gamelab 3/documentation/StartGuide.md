# Start Guide for Monkey's Escape

## Setup

1. Download the repository with recursive to get every extern libary
2. Open the "Hookmaster" Folder in CLion, it is located in code
3. Select visual Studio as toolchain
4. As Generator use *ninja* it works the best
5. If Soloud crashes the game, restarting the IDE normally fixes it.

## Starting up the "Monkey's Escape" game prototype
1. Select the game target in the upper right corner where the "play button" is located
2. Press the "play-button"
3. have fun!

## Create your own game

1. Create a new folder in the code directory in CLion and name it however you want to
2. Create your CMakeList our just copy the one in my game and replace [Project-name] with your project name
3. After creating your CMakeList go to the root CMakeList and add your project with this command :
	```add_subdirectory([directory-name])```\
	Now you should be able to select your game as a target.
4. Create your "src" directory inside of your project folder.
5. Inside the folder create your first source files: Game.cpp and Game.h and you main.cpp

The Game class is meant to inherit from the Game class already existing in the engine code. The most important functions, that your Game.cpp has to have are:

        void run();
        void physics();
        void update();
        void draw();
        void updateDeltaTime();
        void endGame();
If it is not obvious how to use these functions, engine::Game.cpp already has all the minimum logic implemented. Once understood those functions can be expanded or altered to the users desire. 

6. Create Entities and a level.

First of all we need to create a physics world. It could be done like this:

        World myWorldSettings;
        physicsWorld = physicsCommon.createPhysicsWorld(myWorldSettings.settings);

        EventListener eventListener(this);
Every physics world needs its settings or rules it follows. In the engine a small World class is already present, you can simple use it like I did in the example and the world will work. The last line of code is the eventListener, which is needed for collision events, while the physicsWorld simulates, again in the engine is a eventListener, which works in almost every case. When writing a personal eventListener, it is important to know, that your class has to inherit from rp3d::EventListener to work for the physics world.

All the logic considering Entities or parts of the level, should be kept in: std::vector<std::unique_ptr<Entity>> entities.

Using this as the only vector for all the objects, makes all functions, that are called every frame, very easy to implement, because we know, as long as the program goes through the whole vector, everything will be considered. 

    auto platform = std::make_unique<Terrain>(m_game,
                                             "meshes/Terrain/FloorCube.obj", 
                                             glm::vec3{0. 0f, 0.0f, 0.0f}, 
                                             glm::vec3{0.0f, 0.0f, 0.0f},
                                             glm::vec3{20.0f, 0.5f, 20.0f}, 
                                             glm::vec4{0.9f, 0.9f, 0.9f, 1.0f},
                                             m_game->staticTerrain);
    m_game->fillEntities(std::move(platform));
This is the easiest way to create an object in the scene, firstly create a unique pointer of the object and then move the pointer into the entities vector with fillEntities().
As of now all the different children of Entities have a overloaded fillEntities() function, if new ones would be introducted into the engine, a new function needs to be made in Game.h. Since the children of Entity are not in the engine, the fillEntites() function is only located in my game and not the engine itself.

The constructor in this case needs: a pointer to your game, the starting position of your object, the rotation of your object, the scale of your object, the color of your object and the sub version of your object (more on that later in the explaination).

Since the objects are just unique_ptr and are not located on the stack, a simple entities.clear() deletes the whole level, making way for a new one or makes it easier to close the game.

Now we know how to create an Entity, this has to be done everything in a level, since all objets need to have their own Collisionbody, every object needs to be placed individually and not all at once. Creating a Collisionbody for your objects is done like this:

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
        m_body->getCollider(0)->setCollideWithMaskBits(game->staticTerrain | 
        game->swingSurface | game->destroy | game->goal | game->enemy | game->wall);
        m_body->setUserData(this);
This is the code I used for my player character. The body has to be created by the physics world in our case, thats why we need to have the game from the contructor to get the world in which this body should exist. The rest of the code is just setting the settings of the body. The setCollisionCategoryBits and the 
setCollideWithMaskBits are two settings, that need more explaination. The first one is refering to the category that your body belongs to, setting this is needed for the body to collid with anything. The second one are the categories the body is allowed to collid with, all other categories are simply ignored. 

The categories are managed in an enum in the Game.h, if new categories need to be added, they should be added as bitshifted 1s to avoid bits overlapping. This can lead to collisions happening, where there should be none. 

The last step is to give the body a pointer of the Entity, this is done with the setUserData() Function. When receving a collision event for example, it is possible to get a function of the class, which is colliding, this can be very helpful.

Considering the player, I found it easier to keep it out of the entities, because it is easier to access the pointer that way. When doing it like that, it is needed to update, draw etc. the player seperate from everything else.

Once all Entites are loaded in, the next step is to create the skybox, if it is desired. The Skybox class in the engine is already working on its own. If the skybox should look different, a simple task of replacing the pictures is needed to change it. The skybox also has to be drawn in draw().

The last step to setup your game is to create a camera. This is also done through a unique pointer. The camera in the engine works on its own, but can only be used to follow the player at all times. If the camera should be used for a different function, it needs to be altered that way.

If needed, background music can be added at this point. The Game in engine already shows how, that is done.

## New Entities or Equipment

If the only goal of using this engine is to expand on my game, starting with new equipment is the easiest. The new equipments only need to inherit from the Weapon class and be added in the weaponInit() of the Player class.

    auto yourWeapon = std::make_unique<yourWeapon>(m_game, this);
    playerWeapons.push_back(std::move(yourWeapon));
Those are the only two lines of code needed to implement it into the player.

When creating new Entities it is neccessary, that all of those inherit from Entity and have their own category in the Collision enum of your game. Entity itself already needs a lot of parameters in its Constructor, that means if you only use these parameters, the new class is already pretty much useable.

If you don't want to create a new class for every different possible form of your class, you can also use the sub types of the Entities, which I also use in my game. Those are more enums in the game corresponding to every child class of Entity, that needed them. Simple changing the enum in the creation of the object can influence the behaviour of the class, this is a strong tool, which can make collision events more easily controlled through a few if-statments.

If the starting points I provided hear aren't enough to use the engine, my game is using everything, that I explained hear and can always be used a beginning or a code to copy into your project, if things don't work right.




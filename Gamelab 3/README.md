# GameLab Project Repository

|  General Info  | |
| ---|---|
| Working Title | Hookmaster |
| Final Title | Monkey's Escape |
| Student | Jan Hoffmann, jan.hoffmann@stud-mail.uni-wuerzburg.de, s402692 |
| Target Platform(s) | Computer |
| Start Date | 21.10.2024 |
| Study Program | Games Engineering B.Sc.|
| Engine Version | C++ |

### Abstract

Monkey's Escape is a jump and run game, focused on mechanics, which have Nothing to do with running or Jumping.
The movement controls are the Standard ones, WASD to move your Character and space to jump.
The unique elements arise, when you use the different tail abilities.
all abilities are activated by pressing either the  right or left mouse buttons.

The first tail is a hookshot, that travels in the direction the player is looking, when Holding down the mouse button the hookshot travels further.
Once it has connected with a tree (a magnet or a rope coil), it stays at that Location and creates a line betwenn the Player and itself. At that point the Player can jump from the platform and swing with the connecting line to the next platform.
When the tree with the cylinder at the top is hit, the Player can also hold Q to be dragged towards the tree.

The second tail is a blasttail, that blast the Player in the opposite direction of the tree hit.
The trees for this tail are trampolines and often located a bit below the platform in the direction of the jump.

The third tail is a dragtail, that grabs the tree and lets the Player move it to a Location of their choosing.
While holding the mouse button you can move the tree and once you let go of it the tree is locked and can be walked on.
The trees for this weapon are shaped like a metal beam.

The trees will have different colors throughout the level, green indicates that you have to use the left mouse button and dark blue tells you to use the right one.
A lighter blue is also among the colors of the trees, this Color means that it doesn't matter which mouse button you use, it will work.

Once you got to the end of a level and you collect the bananas, you will get a checkpoint at that location and you now have to play the level from back to front.
   

## Repository Usage Guides

```
RepositoryRoot/
    ├── README.md            
    │                       - 
    │                       
    │                       
    ├── builds/             
    │    ├── game                
    │                  
    ├── code/
    │   ├── Hookmaster/
    │   	├── engine/
    │   			├── include/
    │   				├── engine/
    │   					├── ecs/
    │   					├── Assets.h
    │   					├── Camera.h
    │   					├── Collision.h
    │   					├── Contet.h
    │   					├── convert.h
    │   					├── Entity.h
    │   					├── EventListener.h
    │   					├── Events.h
    │   					├── Game.h
    │   					├── Mesh.h
    │   					├── Model.h
    │   					├── Shader.h
    │   					├── Skybox.h
    │   					├── World.h
    │   			├── src/
    │   				├── ecs/
    │   				├── Camera.cpp
    │   				├── Collision.cpp
    │   				├── Context.cpp
    │   				├── convert.cpp
    │   				├── Entity.cpp
    │   				├── EventListener.cpp
    │   				├── Game.cpp
    │   				├── Mesh.cpp
    │   				├── Model.cpp
    │   				├── Shader.cpp
    │   				├── Skybox.cpp
    │   				├── World.cpp
    │   			├── CMakeLists.txt         
    │   	├── game/
    │   		├── src/
    │   			├── entities/
    │   				├── Enemy.cpp
    │   				├── Enemy.h
    │   				├── Goal.cpp
    │   				├── Goal.h
    │   				├── Hookshot.cpp
    │   				├── Hookshot.h
    │   				├── Player.cpp
    │   				├── Player.h
    │   				├── Terrain.cpp
    │   				├── Terrain.h
    │   				├── Tree.cpp
    │   				├── Tree.h
    │   			├── equipment/
    │   				├── BlastAwayWeapon.cpp
    │   				├── BlastAwayWeapon.h
    │   				├── DragWeapon.cpp
    │   				├── DragWeapon.h
    │   				├── SwingWeapon.cpp
    │   				├── SwingWeapon.h
    │   				├── Weapon.cpp
    │   				├── Weapon.h
    │   			├── Physics/
    │   				├── RaycastCallback.cpp
    │   				├── RaycastCallback.h
    │   				├── RaycastCallbackBlastAway.cpp
    │   				├── RaycastCallbackBlastAway.h
    │   				├── RaycastCallbackCamera.cpp
    │   				├── RaycastCallbackCamera.h
    │   				├── RaycastCallbackRopebreak.cpp
    │   				├── RaycastCallbackRopebreak.h
    │   				├── RaycastCallbackSelection.cpp
    │   				├── RaycastCallbackSelection.h
    │   			├── Forward.h
    │   			├── Game.cpp
    │   			├── Game.h
    │   			├── main.cpp
    │   			├── Scene.cpp
    │   			├── Scene.h
    │   		├── CMakeLists.txt 
    │   		├── Triangle.cpp 
    │   		├── Triangle.h     
    │   	├── CMakeLists.txt 
    ├── documentation/      // GL2/3 - Each project requires FULL documentation  
    │                       //   i.e. API Docs, Handbook, Dev Docs
    ├── poster/             // PDF of your Poster(s)
    ├── report/             // PDF
    └── trailer/            // .mp4 (final trailer, no raw material)
```



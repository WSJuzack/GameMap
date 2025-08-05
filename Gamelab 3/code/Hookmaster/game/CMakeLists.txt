cmake_minimum_required(VERSION 3.18)

# set variables for source files
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h ../engine/src/Shader.cpp ../engine/include/engine/Shader.h ../engine/src/Mesh.cpp ../engine/include/engine/Mesh.h ../engine/src/Entity.cpp ../engine/include/engine/Entity.h src/entities/Player.cpp src/entities/Player.h ../engine/include/engine/Assets.h ../engine/src/World.cpp ../engine/include/engine/World.h src/forward.h ../engine/src/convert.cpp ../engine/include/engine/convert.h ../engine/src/Camera.cpp ../engine/include/engine/Camera.h src/entities/Hookshot.cpp src/entities/Hookshot.h src/entities/Terrain.cpp src/entities/Terrain.h src/entities/Tree.cpp src/entities/Tree.h ../engine/src/EventListener.cpp ../engine/include/engine/EventListener.h ../engine/src/Collision.cpp ../engine/include/engine/Collision.h Triangle.cpp Triangle.h src/Physics/RaycastCallback.cpp src/Physics/RaycastCallback.h src/Scene.cpp src/Scene.h src/Physics/RaycastCallbackCamera.cpp src/Physics/RaycastCallbackCamera.h src/entities/Goal.cpp src/entities/Goal.h src/entities/Enemy.cpp src/entities/Enemy.h src/Physics/RaycastCallbackRopebreak.cpp src/Physics/RaycastCallbackRopebreak.h src/equipment/Weapon.cpp src/equipment/Weapon.h src/equipment/BlastAwayWeapon.cpp src/equipment/BlastAwayWeapon.h src/equipment/SwingWeapon.cpp src/equipment/SwingWeapon.h src/Physics/RaycastCallbackBlastAway.cpp src/Physics/RaycastCallbackBlastAway.h src/equipment/DragWeapon.cpp src/equipment/DragWeapon.h src/Physics/RaycastCallbackSelection.cpp src/Physics/RaycastCallbackSelection.h ../engine/src/Skybox.cpp ../engine/include/engine/Skybox.h ../engine/src/Model.cpp ../engine/include/engine/Model.h)

# set executable name
set(EXE_FILE Game)

# add the executable target
add_executable(${EXE_FILE} ${SOURCE_FILES})

# require C++ 17 compiler
target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

# link with dependencies
target_link_libraries(${EXE_FILE} PRIVATE Engine)

target_compile_definitions(${EXE_FILE} PRIVATE ASSET_ROOT=./assets/)

# copy assets to output directory before build
add_custom_command(TARGET ${EXE_FILE} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXE_FILE}>/assets)

cmake_minimum_required(VERSION 3.18)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "include/**.h")
file(GLOB_RECURSE PRIVATE_HEADER_LIST CONFIGURE_DEPENDS "src/**.h")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "src/**.cpp")

set(ENGINE_NAME Engine)

add_library(${ENGINE_NAME} ${HEADER_LIST} ${PRIVATE_HEADER_LIST} ${SOURCE_LIST} include/engine/Events.h include/engine/ecs/System.h include/engine/ecs/ecs.h include/engine/ecs/Component.h include/engine/ecs/ComponentManager.h src/ecs/ComponentManager.cpp include/engine/ecs/Entity.h include/engine/ecs/EntityManager.h src/ecs/EntityManager.cpp src/Context.cpp include/engine/Context.h)

target_compile_features(${ENGINE_NAME} PRIVATE cxx_std_17)
set_target_properties(${ENGINE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${ENGINE_NAME} PUBLIC glad glfw glm soloud tinygltf reactphysics3d assimp)

target_include_directories(${ENGINE_NAME} PUBLIC include/)

# Group files for Visual Studio
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Public Header" FILES ${HEADER_LIST})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Private Header" FILES ${PRIVATE_HEADER_LIST})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source" FILES ${SOURCE_LIST})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/generated" PREFIX "Generated Files" FILES ${GENERATED_FILES_LIST})

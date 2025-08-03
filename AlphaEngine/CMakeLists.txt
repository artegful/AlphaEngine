set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries by default" FORCE)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 1.0.1)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.4)

FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp
  GIT_TAG v6.0.2)

FetchContent_Declare(
  box2d
  GIT_REPOSITORY https://github.com/erincatto/box2d
  GIT_TAG v2.4.2)

set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  rttr
  GIT_REPOSITORY https://github.com/artegful/rttr)

FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt
  GIT_TAG v3.10.0)

FetchContent_Declare(
  yaml
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
  GIT_TAG 2f86d13775d119edbb69af52e5f566fd65c6953b)

set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)
set(BUILD_RTTR_DYNAMIC OFF CACHE BOOL "" FORCE)
set(BUILD_STATIC ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG v1.92.1-docking)

FetchContent_MakeAvailable(glm assimp box2d rttr entt yaml imgui glfw)

add_library(glew32s STATIC IMPORTED)
set_target_properties(glew32s PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glew/lib/glew32s.lib")
target_compile_definitions(glew32s INTERFACE GLEW_STATIC)

add_library(opengl STATIC IMPORTED)
set_target_properties(opengl PROPERTIES
    IMPORTED_LOCATION "opengl32.lib")

file(GLOB IMGUI_SOURCES "${imgui_SOURCE_DIR}/*.cpp")
add_library(imgui_lib STATIC ${IMGUI_SOURCES})
target_include_directories(imgui_lib PUBLIC "${imgui_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(Engine STATIC ${SOURCES})
target_link_libraries(Engine PUBLIC compile_flags glm-header-only rttr_core_lib PRIVATE opengl glew32s assimp box2d glfw imgui_lib yaml-cpp)
target_include_directories(Engine 
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src" "${rttr_SOURCE_DIR}/src" "${rttr_BINARY_DIR}/src" "${EnTT_SOURCE_DIR}/src"
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image" "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glew/include" "${imgui_SOURCE_DIR}")
target_compile_definitions(Engine 
  PUBLIC GLM_ENABLE_EXPERIMENTAL $<$<CONFIG:Debug>:AL_DEBUG> $<$<PLATFORM_ID:Windows>:AL_WINDOWS>)
cmake_minimum_required(VERSION 3.24)

project(TicTacToeGUI)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")

add_definitions(-DENGINE_BUILD_DLL)

add_subdirectory(external/glad/)
add_subdirectory(external/sdl/)
add_subdirectory(external/sdl_image/)

include_directories(
    /include
    external/glad/include
    external/imgui
)
include_directories(
    external/SDL/include external/SDL/src
    external/SDL_image/include
)

#imgui
file(GLOB IMGUI_SOURCES "external/imgui/*.cpp" "external/imgui/*.h"
    "external/imgui/backends/imgui_impl_sdl3.cpp" "external/imgui/backends/imgui_impl_sdl3.h"
    "external/imgui/backends/imgui_impl_opengl3.cpp" "external/imgui/backends/imgui_impl_opengl3.h"
)
add_library(imgui STATIC ${IMGUI_SOURCES})

file(GLOB SOURCES "source/*.cpp" "include/*.hpp")
link_directories(
    ${PROJECT_SOURCE_DIR}/build/external/sdl/
    ${PROJECT_SOURCE_DIR}/build/external/sdl_image/
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} SDL3 SDL3_image)

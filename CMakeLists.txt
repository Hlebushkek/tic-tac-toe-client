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

include_directories(include)
include_directories(external/net)
include_directories(
    external/glad/include
    external/imgui
)
include_directories(
    external/SDL/include external/SDL/src
    external/SDL_image/include
)

file(GLOB SOURCES "source/*.cpp" "include/*.hpp")
link_directories(
    ${PROJECT_SOURCE_DIR}/build/external/sdl/
    ${PROJECT_SOURCE_DIR}/build/external/sdl_image/
)

#imgui
file(GLOB IMGUI_SOURCES
    "external/imgui/*.cpp" "external/imgui/*.h"
    "external/imgui/backends/imgui_impl_sdl3.cpp" "external/imgui/backends/imgui_impl_sdl3.h"
    "external/imgui/backends/imgui_impl_sdlrenderer3.cpp" "external/imgui/backends/imgui_impl_sdlrenderer3.h"
)
add_library(imgui STATIC ${IMGUI_SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_DEFINE_MATH_OPERATORS)

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} SDL3 SDL3_image)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/sdl/SDL3.dll ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/sdl_image/SDL3_image.dll ${CMAKE_BINARY_DIR}
)
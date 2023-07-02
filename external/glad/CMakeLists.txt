cmake_minimum_required(VERSION 3.24)

project(glad)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES "src/*.c" "include/glad/*.h" "include/KHR/*.h")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
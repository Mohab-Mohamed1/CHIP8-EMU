cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
file(GLOB SOURCES "src/*")

project(CHIP8)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2>=2.0.1)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
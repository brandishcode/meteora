cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_CXX_STANDARD 26)

project(Meteora)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)

set(GLFW_USE_WAYLAND ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(${CMAKE_SOURCE_DIR}/configuration/system.hpp.in ${CMAKE_SOURCE_DIR}/src/system/system.hpp)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::OpenGL glfw spdlog::spdlog)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/system)

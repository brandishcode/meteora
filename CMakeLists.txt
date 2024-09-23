cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_CXX_STANDARD 26)

project(Meteora)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

set(GLFW_USE_WAYLAND ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(${CMAKE_SOURCE_DIR}/configuration/system.hpp.in ${CMAKE_SOURCE_DIR}/src/system/system.hpp)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::OpenGL glfw GLEW::glew spdlog::spdlog glm::glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/system)
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/system/graphics/Backend.cpp ${CMAKE_SOURCE_DIR}/src/system/graphics/Vertex.cpp)

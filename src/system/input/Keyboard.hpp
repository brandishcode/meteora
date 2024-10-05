#pragma once

#include "camera/Camera.hpp"
#include "graphics/opengl.hpp"

namespace Meteora {
class Keyboard {
public:
  static void processInput(GLFWwindow *window, Camera &camera, float deltaTime);

private:
  inline static bool isUp(GLFWwindow *window) {
    return glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS;
  }

  inline static bool isDown(GLFWwindow *window) {
    return glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
  }

  inline static bool isLeft(GLFWwindow *window) {
    return glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
  }

  inline static bool isRight(GLFWwindow *window) {
    return glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS;
  }

  static void up(Camera &camera, float speed);
  static void down(Camera &camera, float speed);
  static void right(Camera &camera, float speed);
  static void left(Camera &camera, float speed);
};
} // namespace Meteora

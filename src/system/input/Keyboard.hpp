#pragma once

#include "camera/Camera.hpp"
#include "opengl.hpp"

namespace Meteora {
class Keyboard {
public:
  static void processInput(Window *window, Camera &camera, float deltaTime);

private:
  inline static bool isUp(Window *window) {
    return glfwGetKey(window, PERIOD) == PRESS;
  }

  inline static bool isDown(Window *window) {
    return glfwGetKey(window, E) == PRESS;
  }

  inline static bool isLeft(Window *window) {
    return glfwGetKey(window, O) == PRESS;
  }

  inline static bool isRight(Window *window) {
    return glfwGetKey(window, U) == PRESS;
  }

  static void up(Camera &camera, float speed);
  static void down(Camera &camera, float speed);
  static void right(Camera &camera, float speed);
  static void left(Camera &camera, float speed);
};
} // namespace Meteora

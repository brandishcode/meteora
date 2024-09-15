#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Meteora {

typedef GLFWwindow Window;

class Backend {
public:
  void init();
  void run();

private:
  Window *window;
};
}; // namespace Meteora

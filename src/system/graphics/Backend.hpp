#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Meteora {

typedef GLFWwindow Window;

class Backend {
public:
  void run();

private:
  Window *window;
  void init(int width, int height);
};
}; // namespace Meteora

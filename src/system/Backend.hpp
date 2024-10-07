#pragma once

#include <opengl.hpp>

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

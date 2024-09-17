#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Meteora {

typedef GLsizei Size;
typedef GLuint GenName;
class Buffer {
public:
  Buffer(Size size) : size(size) { names = new GenName[size]; }
  ~Buffer() { delete names; }

protected:
  GenName *names;
  Size size;
};
} // namespace Meteora

#pragma once

#include "graphics/glm/Vertex.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>

namespace Meteora {

typedef GLsizei Size;
typedef GLuint Name;

typedef vec3 Position;

enum BindType {
  NONE,
  ARRAY = GL_ARRAY_BUFFER,
  ELEMENT = GL_ELEMENT_ARRAY_BUFFER
};

struct Bindings {
  virtual void generate() = 0;
  virtual void destroy() = 0;
  virtual void bind(BindType type, unsigned int index) = 0;
  virtual void unbind() = 0;

protected:
  Bindings(Size size) : size(size) { names = new Name[size]; }
  Size size;
  Name *names;
};

enum AttribType { RGB, RGBA, TEXTURE };

struct Buffer {
  ~Buffer() { delete arrayBuffer; }
  virtual void setArrayBuffer(Vertex *vertices, std::size_t totalSize,
                              std::size_t elementSize, AttribType type) = 0;
  virtual void setElementBuffer(unsigned int *indices, std::size_t size) = 0;

protected:
  float *arrayBuffer = NULL;
};
} // namespace Meteora

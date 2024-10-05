#pragma once

#include "../opengl.hpp"
#include "math/Vertex.hpp"

namespace Meteora {

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

struct Buffer {
  ~Buffer() { delete arrayBuffer; }
  virtual void setArrayBuffer(Vertex *vertices, std::size_t totalSize,
                              std::size_t elementSize, AttribType type) = 0;
  virtual void setElementBuffer(unsigned int *indices, std::size_t size) = 0;

protected:
  float *arrayBuffer = NULL;
};

} // namespace Meteora

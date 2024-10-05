#pragma once

#include "bindable.hpp"
#include <cstddef>
#include <cstring>

namespace Meteora {

class VertexBuffer : public Bindings, public Buffer {
public:
  VertexBuffer(Size size) : Bindings(size) {}

  ~VertexBuffer() { delete arrayBuffer; }

  inline void generate() override { glGenBuffers(size, names); }

  inline void destroy() override { glDeleteBuffers(size, names); }

  inline void bind(BindType type, unsigned int index) override {
    glBindBuffer(type, names[index]);
  }

  inline void unbind() override { glBindBuffer(ARRAY, 0); }

  inline void setArrayBuffer(Vertex *vertices, std::size_t totalSize,
                             std::size_t elementSize,
                             AttribType type) override {
    glBufferData(ARRAY, totalSize, vertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, elementSize, (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int size = 0;

    switch (type) {
    case RGB:
      size = 3;
      break;
    case RGBA:
      size = 4;
      break;
    case TEXTURE:
      size = 2;
      break;
    default:
      return;
    }

    // color
    glVertexAttribPointer(1, size, GL_FLOAT, GL_FALSE, elementSize,
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }

  inline void setElementBuffer(unsigned int *indices,
                               std::size_t size) override {
    glBufferData(ELEMENT, size, indices, GL_STATIC_DRAW);
  }
};
} // namespace Meteora

#pragma once

#include "graphics/glm/Vertex.hpp"
#include "graphics/opengl/OpenglAbstracts.hpp"
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
                             std::size_t elementSize) override {
    glBufferData(ARRAY, totalSize, vertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, elementSize, (void *)0);
    glEnableVertexAttribArray(0);
  }

  inline void setElementBuffer(unsigned int *indices,
                               std::size_t size) override {
    glBufferData(ELEMENT, size, indices, GL_STATIC_DRAW);
  }
};
} // namespace Meteora

#pragma once

#include "graphics/glm/Vertex.hpp"
#include "graphics/opengl/OpenglAbstracts.hpp"
#include "graphics/opengl/VertexBuffer.hpp"
#include <cstddef>
#include <cstring>

namespace Meteora {

class TexturedVertexBuffer : public VertexBuffer {
public:
  TexturedVertexBuffer(Size size) : VertexBuffer(size) {}

  inline void setArrayBuffer(Vertex *vertices, std::size_t totalSize,
                             std::size_t elementSize) override {
    glBufferData(ARRAY, totalSize, vertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, elementSize, (void *)0);
    glEnableVertexAttribArray(0);

    // texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, elementSize,
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }
};
} // namespace Meteora

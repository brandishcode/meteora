#pragma once

#include "graphics/Buffer.hpp"
#include <cstring>

namespace Meteora {

enum BufferType { ARRAY = GL_ARRAY_BUFFER, ELEMENT = GL_ELEMENT_ARRAY_BUFFER };

class VertexBuffer : public Buffer {
public:
  inline void createVBOs() { glGenBuffers(size, names); }

  inline void deleteVBOs() { glDeleteBuffers(size, names); }

  inline void bindVBO(BufferType buffType, unsigned int index) {
    glBindBuffer(buffType, names[index]);
  }

  inline void unbindVBOs() { glBindBuffer(ARRAY, 0); }

  inline void setABOData(float *data, std::size_t size, unsigned int count) {
    glBufferData(ARRAY, size, data, GL_STATIC_DRAW);
    setAttribPointer(size, count);
  }

  inline void setEBOData(unsigned int *data, std::size_t size) {
    glBufferData(ELEMENT, size, data, GL_STATIC_DRAW);
  }

private:
  inline void setAttribPointer(unsigned int size, unsigned int count) {
    unsigned int stride = size / count;

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
    glEnableVertexAttribArray(0);

    // texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride,
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  };
};
} // namespace Meteora

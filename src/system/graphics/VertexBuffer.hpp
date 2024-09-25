#pragma once

#include "graphics/Buffer.hpp"
#include "graphics/Vertex.hpp"
#include <cstring>

namespace Meteora {

enum BufferType { ARRAY = GL_ARRAY_BUFFER, ELEMENT = GL_ELEMENT_ARRAY_BUFFER };

class VertexBuffer : public Buffer {
public:
  VertexBuffer(Size size) : Buffer(size) { bufferData = NULL; }

  ~VertexBuffer() { delete bufferData; }

  inline void createVBOs() { glGenBuffers(size, names); }

  inline void deleteVBOs() { glDeleteBuffers(size, names); }

  inline void bindVBO(BufferType buffType, unsigned int index) {
    glBindBuffer(buffType, names[index]);
  }

  inline void unbindVBOs() { glBindBuffer(ARRAY, 0); }

  inline void setABOData(Vertex *vertices, unsigned int count) {
    unsigned int size = count * 5;
    bufferData = new float[size];
    for (unsigned int i = 0; i < count; i++) {
      bufferData[i * 5] = vertices[i].data[0];
      bufferData[i * 5 + 1] = vertices[i].data[1];
      bufferData[i * 5 + 2] = vertices[i].data[2];
      bufferData[i * 5 + 3] = vertices[i].data[3];
      bufferData[i * 5 + 4] = vertices[i].data[4];
    }
    glBufferData(ARRAY, size * sizeof(float), bufferData, GL_STATIC_DRAW);
    setAttribPointer(size * sizeof(float), count);
  }

  inline void setEBOData(unsigned int *data, std::size_t size) {
    glBufferData(ELEMENT, size, data, GL_STATIC_DRAW);
  }

private:
  float *bufferData;
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

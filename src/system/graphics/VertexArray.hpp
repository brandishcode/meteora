#pragma once

#include "graphics/Buffer.hpp"

namespace Meteora {
class VertexArray : public Buffer {
public:
  inline void createVAOs() { glGenVertexArrays(size, names); }
  void deleteVAOs() { glDeleteVertexArrays(size, names); }

  void bindVAO(unsigned int index) { glBindVertexArray(names[index]); }
  void unbindVAOs() { glBindVertexArray(0); }
};
} // namespace Meteora

#pragma once

#include "bindable.hpp"

namespace Meteora {
class VertexArray : public Bindings {
public:
  VertexArray(Size size) : Bindings(size) {}

  inline void generate() override { glGenVertexArrays(size, names); }

  inline void destroy() override { glDeleteVertexArrays(size, names); }

  inline void bind(BindType type = NONE, unsigned int index = 0) override {
    glBindVertexArray(names[index]);
  }

  inline void unbind() override { glBindVertexArray(0); }
};
} // namespace Meteora

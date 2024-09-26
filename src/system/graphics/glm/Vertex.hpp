#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace Meteora {
struct Vertex {
  Vertex(vec3 position, vec2 texturePosition)
      : position(position), texturePosition(texturePosition) {}
  vec3 position;
  vec2 texturePosition;
};
} // namespace Meteora

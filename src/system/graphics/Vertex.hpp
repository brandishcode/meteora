#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

using namespace glm;

namespace Meteora {
class Vertex {
public:
  Vertex(vec3 position) : position(position) {}
  Vertex(vec3 position, vec2 texturePosition)
      : position(position), texturePosition(texturePosition) {}

private:
  vec3 position;
  vec2 texturePosition;
};
} // namespace Meteora

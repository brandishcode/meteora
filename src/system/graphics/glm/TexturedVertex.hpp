#pragma once

#include "graphics/glm/Vertex.hpp"
#include <glm/glm.hpp>

using namespace glm;

namespace Meteora {
struct TexturedVertex : public Vertex {
  TexturedVertex(vec3 position, vec2 texturePosition)
      : Vertex(position), texturePosition(texturePosition) {}
  vec2 texturePosition;
};
} // namespace Meteora

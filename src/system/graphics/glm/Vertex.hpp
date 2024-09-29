#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace Meteora {
struct Vertex {
  Vertex(vec3 position) : position(position) {}
  vec3 position;
};
} // namespace Meteora

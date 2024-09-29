#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace Meteora {
struct Vertex {
  Vertex(vec3 position, vec3 rgb) : position(position), rgb(rgb) {}
  Vertex(vec3 position, vec4 rgb) : position(position), rgb(rgb) {}
  Vertex(vec3 position, vec2 texture) : position(position), texture(texture) {}
  vec3 position;
  union {
    vec4 rgba;
    vec3 rgb;
    vec2 texture;
  };
};
} // namespace Meteora

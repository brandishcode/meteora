#pragma once

#include "vertex.hpp"

namespace Meteora {
struct Vertex {
  Vertex(Vec3 position, Vec3 rgb) : position(position), rgb(rgb) {}
  Vertex(Vec3 position, Vec4 rgb) : position(position), rgb(rgb) {}
  Vertex(Vec3 position, Vec2 texture) : position(position), texture(texture) {}
  Vec3 position;
  union {
    Vec4 rgba;
    Vec3 rgb;
    Vec2 texture;
  };
};
} // namespace Meteora

#pragma once

#include "math/vertex.hpp"

namespace Meteora {
class Vertex {
public:
  Vertex(Vec3 position) : position(position) {}
  Vertex(Vec3 position, Vec2 texturePosition)
      : position(position), texturePosition(texturePosition) {}

private:
  Vec3 position;
  Vec2 texturePosition;
};
} // namespace Meteora

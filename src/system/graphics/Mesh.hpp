#pragma once

#include <glm/ext/vector_float3.hpp>

using namespace glm;

namespace Meteora {

typedef vec3 Position;
typedef vec3 Dimension;

class Mesh {
public:
  Mesh(Position position = Position{0.0f, 0.0f, 0.0f},
       Dimension dimension = Dimension{1.0f, 1.0f, 1.0f})
      : position(position), dimension(dimension) {}
  const Position position;
  const Dimension dimension;
};
} // namespace Meteora

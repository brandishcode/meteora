#pragma once

#include "math/Vertex.hpp"
#include <memory>

using namespace glm;

namespace Meteora {

typedef Vec3 Position;
typedef Vec3 Dimension;

class PrimitiveMesh {
public:
  PrimitiveMesh(unsigned int size = 0,
                Dimension dimension = Dimension{1.0f, 1.0f, 1.0f},
                Position position = Position{0.0f, 0.0f, 0.0f});
  ~PrimitiveMesh() = default;

  std::unique_ptr<Vertex> vertices;
  const unsigned int size;

protected:
  const Position position;
  const Dimension dimension;
};
} // namespace Meteora

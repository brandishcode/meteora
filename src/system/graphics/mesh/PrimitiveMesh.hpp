#pragma once

#include "math/Vertex.hpp"
#include <memory>

namespace Meteora {

class PrimitiveMesh {
public:
  PrimitiveMesh(unsigned int size = 0, Vec3 dimension = Vec3{1.0f, 1.0f, 1.0f},
                Vec3 position = Vec3{0.0f, 0.0f, 0.0f});
  ~PrimitiveMesh() = default;

  std::unique_ptr<Vertex> vertices;
  const unsigned int size;

protected:
  const Vec3 position;
  const Vec3 dimension;
};
} // namespace Meteora

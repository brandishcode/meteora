#pragma once

#include "math/Vertex.hpp"
#include <memory>

namespace Meteora {

class Mesh {
public:
  Mesh(unsigned int size = 0, Vec3 dimension = Vec3{1.0f, 1.0f, 1.0f},
       unsigned int indicesSize = 0, Vec3 position = Vec3{0.0f, 0.0f, 0.0f});
  ~Mesh() = default;

  const std::unique_ptr<Vertex[]> vertices;
  const std::unique_ptr<unsigned int[]> indices;
  const unsigned int size;
  const unsigned int indicesSize;

protected:
  const Vec3 position;
  const Vec3 dimension;
};
} // namespace Meteora

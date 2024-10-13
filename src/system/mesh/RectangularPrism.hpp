#pragma once

#include "Mesh.hpp"

namespace Meteora {
class RectangularPrism : public Mesh {
public:
  RectangularPrism();
  RectangularPrism(Vec3 color, Vec3 position = Vec3{1.0f, 1.0f, 1.0f});

private:
  void setVertices();
  void setIndices();
};
} // namespace Meteora

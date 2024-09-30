#pragma once

#include "graphics/glm/Vertex.hpp"
#include <glm/ext/vector_float3.hpp>

using namespace glm;

namespace Meteora {

typedef vec3 Position;
typedef vec3 Dimension;

class PrimitiveMesh {
public:
  PrimitiveMesh(Position position = Position{0.0f, 0.0f, 0.0f},
                Dimension dimension = Dimension{1.0f, 1.0f, 1.0f},
                unsigned int size = 0)
      : position(position), dimension(dimension), _size(size) {

    vertices = (Vertex *)malloc(size * sizeof(Vertex));
  }

  ~PrimitiveMesh() { delete vertices; }

  Vertex *data() { return vertices; };
  std::size_t size() { return _size * sizeof(Vertex); }

protected:
  const Position position;
  const Dimension dimension;
  unsigned int _size;
  Vertex *vertices = NULL;
};
} // namespace Meteora

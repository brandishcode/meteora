#pragma once

#include "PrimitiveMesh.hpp"

namespace Meteora {
class AxisMesh : public PrimitiveMesh {
public:
  AxisMesh(Position position, Dimension dimension)
      : PrimitiveMesh(position, dimension, 6) {
    vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
    vec4 green(0.0f, 1.0f, 0.0f, 1.0f);
    vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);

    vertices[0] = Vertex(position, red);
    vertices[1] = Vertex(position + vec3(dimension.x, 0.0f, 0.0f), red);
    vertices[2] = Vertex(position, green);
    vertices[3] = Vertex(position + vec3(0.0f, dimension.y, 0.0f), green);
    vertices[4] = Vertex(position, blue);
    vertices[5] = Vertex(position + vec3(0.0f, 0.0f, dimension.z), blue);
  }
};
} // namespace Meteora

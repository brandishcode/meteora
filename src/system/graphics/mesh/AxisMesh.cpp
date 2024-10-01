#include "AxisMesh.hpp"

namespace Meteora {

AxisMesh::AxisMesh() : PrimitiveMesh(6) {
  vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
  vec4 green(0.0f, 1.0f, 0.0f, 1.0f);
  vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);

  vertices.get()[0] = Vertex(position, red);
  vertices.get()[1] = Vertex(position + vec3(dimension.x, 0.0f, 0.0f), red);
  vertices.get()[2] = Vertex(position, green);
  vertices.get()[3] = Vertex(position + vec3(0.0f, dimension.y, 0.0f), green);
  vertices.get()[4] = Vertex(position, blue);
  vertices.get()[5] = Vertex(position + vec3(0.0f, 0.0f, dimension.z), blue);
}
} // namespace Meteora

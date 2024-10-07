#include "Square.hpp"
#include "math/vector.hpp"

namespace Meteora {
Square::Square() : Mesh(4, Vec3{1.0f, 1.0f, 0.0f}, 6) {
  float halfLength = dimension.x / 2.0f;
  float halfWidth = dimension.y / 2.0f;
  vertices.get()[0] =
      Vertex{Vec3{position.x - halfLength, position.y, position.z - halfWidth},
             Vec3{1.0f, 1.0f, 0.0f}};
  vertices.get()[1] =
      Vertex{Vec3{position.x + halfLength, position.y, position.z - halfWidth},
             Vec3{1.0f, 1.0f, 0.0f}};
  vertices.get()[2] =
      Vertex{Vec3{position.x - halfLength, position.y, position.z + halfWidth},
             Vec3{1.0f, 1.0f, 0.0f}};
  vertices.get()[3] =
      Vertex{Vec3{position.x + halfLength, position.y, position.z + halfWidth},
             Vec3{1.0f, 1.0f, 0.0f}};

  indices.get()[0] = 0;
  indices.get()[1] = 1;
  indices.get()[2] = 2;
  indices.get()[3] = 2;
  indices.get()[4] = 3;
  indices.get()[5] = 1;
}
} // namespace Meteora

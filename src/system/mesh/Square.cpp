#include "Square.hpp"
#include "math/vector.hpp"

namespace Meteora {
Square::Square() : Mesh(4, Vec3{1.0f, 1.0f, 0.0f}, 6) {
  float halfLength = dimension.x / 2.0f;
  float halfWidth = dimension.y / 2.0f;
  Vertex *ptr = vertices.get();
  ptr[0] =
      Vertex{Vec3{position.x - halfLength, position.y, position.z - halfWidth},
             Vec3{1.0f, 1.0f, 0.0f}};
  ptr[1] =
      Vertex{Vec3{position.x + halfLength, position.y, position.z - halfWidth},
             Vec3{1.0f, 1.0f, 0.0f}};
  ptr[2] =
      Vertex{Vec3{position.x - halfLength, position.y, position.z + halfWidth},
             Vec3{1.0f, 1.0f, 0.0f}};
  ptr[3] =
      Vertex{Vec3{position.x + halfLength, position.y, position.z + halfWidth},
             Vec3{1.0f, 1.0f, 0.0f}};

  unsigned int *idxPtr = indices.get();
  idxPtr[0] = 0;
  idxPtr[1] = 1;
  idxPtr[2] = 2;
  idxPtr[3] = 2;
  idxPtr[4] = 3;
  idxPtr[5] = 1;
}
} // namespace Meteora

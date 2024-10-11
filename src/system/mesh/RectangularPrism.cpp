#include "RectangularPrism.hpp"

namespace Meteora {
RectangularPrism::RectangularPrism() : Mesh(8, Vec3{1.0f, 1.0f, 1.0f}, 36) {
  float halfLength = dimension.x / 2.0f;
  float halfWidth = dimension.y / 2.0f;
  float halfDepth = dimension.z / 2.0f;
  Vertex *ptr = vertices.get();
  ptr[0] = Vertex{Vec3{position.x - halfWidth, position.y - halfDepth,
                       position.z - halfWidth},
                  Vec3{1.0f, 1.0f, 0.0f}};
  ptr[1] = Vertex{Vec3{position.x + halfWidth, position.y - halfDepth,
                       position.z - halfWidth},
                  Vec3{1.0f, 1.0f, 0.0f}};
  ptr[2] = Vertex{Vec3{position.x - halfWidth, position.y - halfDepth,
                       position.z + halfWidth},
                  Vec3{1.0f, 1.0f, 0.0f}};
  ptr[3] = Vertex{Vec3{position.x + halfWidth, position.y - halfDepth,
                       position.z + halfWidth},
                  Vec3{1.0f, 1.0f, 0.0f}};

  ptr[4] = Vertex{Vec3{position.x - halfWidth, position.y + halfDepth,
                       position.z - halfWidth},
                  Vec3{1.0f, 1.0f, 0.0f}};
  ptr[5] = Vertex{Vec3{position.x + halfWidth, position.y + halfDepth,
                       position.z - halfWidth},
                  Vec3{1.0f, 1.0f, 0.0f}};
  ptr[6] = Vertex{Vec3{position.x - halfWidth, position.y + halfDepth,
                       position.z + halfWidth},
                  Vec3{1.0f, 1.0f, 0.0f}};
  ptr[7] = Vertex{Vec3{position.x + halfWidth, position.y + halfDepth,
                       position.z + halfWidth},
                  Vec3{1.0f, 1.0f, 0.0f}};

  unsigned int *idxPtr = indices.get();
  // top
  idxPtr[0] = 0;
  idxPtr[1] = 1;
  idxPtr[2] = 2;
  idxPtr[3] = 2;
  idxPtr[4] = 3;
  idxPtr[5] = 1;

  // bottom
  idxPtr[6] = 4;
  idxPtr[7] = 5;
  idxPtr[8] = 6;
  idxPtr[9] = 6;
  idxPtr[10] = 7;
  idxPtr[11] = 5;

  // back
  idxPtr[12] = 0;
  idxPtr[13] = 1;
  idxPtr[14] = 4;
  idxPtr[15] = 1;
  idxPtr[16] = 5;
  idxPtr[17] = 4;

  // front
  idxPtr[18] = 2;
  idxPtr[19] = 3;
  idxPtr[20] = 6;
  idxPtr[21] = 3;
  idxPtr[22] = 7;
  idxPtr[23] = 6;

  // left
  idxPtr[24] = 0;
  idxPtr[25] = 2;
  idxPtr[26] = 4;
  idxPtr[27] = 2;
  idxPtr[28] = 6;
  idxPtr[29] = 4;

  // right
  idxPtr[30] = 1;
  idxPtr[31] = 3;
  idxPtr[32] = 7;
  idxPtr[33] = 1;
  idxPtr[34] = 5;
  idxPtr[35] = 7;
}
} // namespace Meteora

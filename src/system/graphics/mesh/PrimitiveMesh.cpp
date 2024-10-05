#include "PrimitiveMesh.hpp"

namespace Meteora {

PrimitiveMesh::PrimitiveMesh(unsigned int size, Vec3 dimension, Vec3 position)
    : size(size * sizeof(Vertex)), dimension(dimension), position(position),
      vertices((Vertex *)malloc(size * sizeof(Vertex))) {}
} // namespace Meteora

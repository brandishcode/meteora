#include "Mesh.hpp"

namespace Meteora {
Mesh::Mesh(unsigned int size, Vec3 dimension, unsigned int indicesSize,
           Vec4 colora, Vec3 position)
    : size(size * sizeof(Vertex)),
      indicesSize(indicesSize * sizeof(unsigned int)), dimension(dimension),
      indices(new unsigned int[indicesSize]), position(position),
      vertices(new Vertex[size]), colora(colora) {}
} // namespace Meteora

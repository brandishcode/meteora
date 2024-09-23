#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

using namespace glm;

namespace Meteora {
class Vertex {
public:
  Vertex(vec3 pos, vec2 texPos) : pos(pos), texPos(texPos) {
    data = new float[5];
    data[0] = pos.x;
    data[1] = pos.y;
    data[2] = pos.z;
    data[3] = texPos.x;
    data[4] = texPos.y;
  }
  ~Vertex() { delete data; }
  float *data;

private:
  vec3 pos;
  vec2 texPos;
};
} // namespace Meteora

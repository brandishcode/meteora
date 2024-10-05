#pragma once

#include "math/matrix.hpp"
#include "math/vector.hpp"

namespace Meteora {
class Camera {
public:
  Camera(Vec3 position, Vec3 target, Vec3 up);
  Mat4 view();
  Vec3 position;
  Vec3 target;
  Vec3 up;
};
} // namespace Meteora

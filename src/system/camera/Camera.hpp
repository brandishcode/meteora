#pragma once

#include "math/matrix.hpp"
#include "math/vector.hpp"

namespace Meteora {
class Camera {
public:
  Camera(Vec3 position, Vec3 target, Vec3 up, Vec3 front);
  Mat4 &getView();
  Vec3 position;
  Vec3 target;
  const Vec3 up;
  const Vec3 front;
  void calculateView();

private:
  Mat4 view;
};
} // namespace Meteora

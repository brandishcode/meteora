#include "Camera.hpp"

namespace Meteora {
Camera::Camera(Vec3 position, Vec3 target, Vec3 up, Vec3 front)
    : position(position), target(target), up(up), front(front),
      view(lookAt(position, target, up)) {}
Mat4 &Camera::getView() { return view; }
void Camera::calculateView() { view = lookAt(position, target, up); }
} // namespace Meteora

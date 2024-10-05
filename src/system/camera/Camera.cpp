#include "Camera.hpp"

namespace Meteora {
Camera::Camera(Vec3 position, Vec3 target, Vec3 up, Vec3 front)
    : position(position), target(target), up(up), front(front) {}
Mat4 Camera::view() { return lookAt(position, target, up); }
} // namespace Meteora

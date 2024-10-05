#include "Camera.hpp"

namespace Meteora {
Camera::Camera(Vec3 position, Vec3 target, Vec3 up)
    : position(position), target(target), up(up) {}
Mat4 Camera::view() { return lookAt(position, target, up); }
} // namespace Meteora

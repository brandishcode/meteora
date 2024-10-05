#pragma once

#include "vector.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

typedef glm::mat4 Mat4;

inline float radians(float degrees) { return glm::radians(degrees); }

inline Mat4 perspective(float fov, float aspectRatio, float zNear, float zFar) {
  return glm::perspective(fov, aspectRatio, zNear, zFar);
}

inline Mat4 lookAt(Vec3 &eye, Vec3 &center, Vec3 &up) {
  return glm::lookAt(eye, center, up);
}

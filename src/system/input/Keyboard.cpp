#include "Keyboard.hpp"

namespace Meteora {
void Keyboard::processInput(GLFWwindow *window, Camera &camera,
                            float deltaTime) {
  float speed = 2.5 * deltaTime;
  if (isUp(window) && isLeft(window)) {
    up(camera, speed);
    left(camera, speed);
  } else if (isUp(window) && isRight(window)) {
    up(camera, speed);
    right(camera, speed);
  } else if (isDown(window) && isLeft(window)) {
    down(camera, speed);
    left(camera, speed);
  } else if (isDown(window) && isRight(window)) {
    down(camera, speed);
    right(camera, speed);
  } else if (isUp(window)) {
    up(camera, speed);
  } else if (isDown(window)) {
    down(camera, speed);
  } else if (isLeft(window)) {
    left(camera, speed);
  } else if (isRight(window)) {
    right(camera, speed);
  }
  camera.calculateView();
}

void Keyboard::up(Camera &camera, float speed) {
  camera.position -= speed * camera.front;
  camera.target -= speed * camera.front;
}

void Keyboard::down(Camera &camera, float speed) {
  camera.position += speed * camera.front;
  camera.target += speed * camera.front;
}

void Keyboard::right(Camera &camera, float speed) {
  camera.position -= normalize(cross(camera.front, camera.up)) * speed;
  camera.target -= normalize(cross(camera.front, camera.up)) * speed;
}

void Keyboard::left(Camera &camera, float speed) {
  camera.position += normalize(cross(camera.front, camera.up)) * speed;
  camera.target += normalize(cross(camera.front, camera.up)) * speed;
}
} // namespace Meteora

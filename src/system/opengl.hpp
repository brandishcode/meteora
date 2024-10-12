#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Meteora {
typedef GLsizei Size;
typedef GLuint Name;
typedef GLFWwindow Window;

enum KeyCode {
  PERIOD = GLFW_KEY_PERIOD,
  E = GLFW_KEY_E,
  O = GLFW_KEY_O,
  U = GLFW_KEY_U
};

enum KeyAction { PRESS = GLFW_PRESS };

enum BindType {
  NONE,
  ARRAY = GL_ARRAY_BUFFER,
  ELEMENT = GL_ELEMENT_ARRAY_BUFFER
};

enum AttribType { RGB, RGBA, TEXTURE };

namespace Render {
enum Mode { LINES = GL_LINES, TRIANGLES = GL_TRIANGLES };
enum Method { ARRAY, ELEMENT, ELEMENT_INSTANCED };
} // namespace Render
} // namespace Meteora

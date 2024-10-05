#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef GLsizei Size;
typedef GLuint Name;

enum BindType {
  NONE,
  ARRAY = GL_ARRAY_BUFFER,
  ELEMENT = GL_ELEMENT_ARRAY_BUFFER
};

enum AttribType { RGB, RGBA, TEXTURE };

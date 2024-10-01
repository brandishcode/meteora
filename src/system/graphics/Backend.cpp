#include <cstddef>
#include <cstdio>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <logger.hpp>
#include <stdexcept>
#include <string>
#include <system.hpp>

#include "graphics/Backend.hpp"
#include "graphics/glm/Vertex.hpp"
#include "graphics/mesh/AxisMesh.hpp"
#include "graphics/opengl/OpenglAbstracts.hpp"
#include "graphics/opengl/Renderer.hpp"
#include "graphics/opengl/ShaderProgram.hpp"
#include "graphics/opengl/VertexArray.hpp"
#include "graphics/opengl/VertexBuffer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define RESET_INDEX 999

using namespace Meteora;

void error_callback(int error, const char *description) {
  throw std::runtime_error(description);
}

void GLAPIENTRY opengl_error_callback(GLenum source, GLenum type, GLuint id,
                                      GLenum severity, GLsizei length,
                                      const GLchar *message,
                                      const void *userParam) {
  std::string messageType;
  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    char buffer[100];
    sprintf(buffer, "GL CALLBACK: severity = 0x%x, message = %s", severity,
            message);
    throw std::runtime_error(buffer);
    return;
  case GL_DEBUG_TYPE_PERFORMANCE:
    messageType = "Performance";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    messageType = "Deprecated";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    messageType = "Undefined behavior";
    break;
  default:
    return;
  }
  LOGGER_WARN("GL CALLBACK: type = {}, severity = 0x{:x}, message ={} ",
              messageType, severity, message);
}

void Backend::init(int width, int height) {
  glfwSetErrorCallback(error_callback);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VER);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VER);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Make window floating for wayland */
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, PROJECT_NAME);

  window = glfwCreateWindow(width, height, "Game", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::string errMsg((char *)glewGetErrorString(err));
    throw std::runtime_error(errMsg);
  }

  // glEnable(GL_DEPTH_TEST);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(RESET_INDEX);

  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glEnable(GL_BLEND);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(opengl_error_callback, 0);
}

void Backend::run() {

  int width = 480, height = 480;

  init(width, height);

  VertexArray vaos(1);
  vaos.generate();
  vaos.bind();

  VertexBuffer vbo(1);
  vbo.generate();

  vbo.bind(ARRAY, 0);

  AxisMesh axis;

  vbo.setArrayBuffer(axis.vertices.get(), axis.size, sizeof(Vertex), RGBA);

  vbo.unbind();
  vaos.unbind();

  ShaderProgram shaderProgram = ShaderProgram("vertex.glsl", "fragment.glsl");

  Context context(&vaos, &vbo, &shaderProgram, NULL,
                  CameraPosition{5.0f, 5.0f, 5.0f}, (float)width,
                  (float)height);
  glfwSetWindowUserPointer(window, &context);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Renderer::render(context);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  vaos.destroy();
  vbo.destroy();
  shaderProgram.destroy();

  glfwTerminate();
}

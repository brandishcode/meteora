#include <cstddef>
#include <cstdio>
#include <logger.hpp>
#include <stdexcept>
#include <string>
#include <system.hpp>

#include "camera/Camera.hpp"
#include "graphics/Backend.hpp"
#include "graphics/render/Renderer.hpp"
#include "graphics/render/ShaderProgram.hpp"
#include "graphics/render/VertexArray.hpp"
#include "input/Keyboard.hpp"

#define RESET_INDEX 999

using namespace Meteora;

void errorCallback(int error, const char *description) {
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
  glfwSetErrorCallback(errorCallback);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VER);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VER);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Make window floating for wayland */
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, PROJECT_NAME);

  window = glfwCreateWindow(width, height, PROJECT_NAME, NULL, NULL);
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

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(opengl_error_callback, 0);
}

void Backend::run() {

  int width = 480, height = 480;

  init(width, height);

  VertexArray baseVao(1);
  baseVao.generate();
  ShaderProgram axisShader = ShaderProgram("axis_vert.glsl", "axis_frag.glsl");
  ShaderProgram gridShader = ShaderProgram("grid_vert.glsl", "grid_frag.glsl");

  Camera camera({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 1.0f});
  float zNear = 0.01f;
  float zFar = 100.0f;
  Mat4 projection =
      perspective(radians(45.0f), (float)width / (float)height, zNear, zFar);

  float deltaTime = 0.0f, lastFrame = 0.0f;

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    Keyboard::processInput(window, camera, deltaTime);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width, height);
    Renderer::enableAlphaBlending();
    Renderer::render(&baseVao, &gridShader, NULL, camera.view(), projection,
                     zNear, zFar, TRIANGLES, 6);
    Renderer::disableAlphaBlending();
    Renderer::render(&baseVao, &axisShader, NULL, camera.view(), projection,
                     zNear, zFar, LINES, 6);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  baseVao.destroy();
  axisShader.destroy();

  glfwTerminate();
}

#include <cstddef>
#include <cstdio>
#include <logger.hpp>
#include <stdexcept>
#include <string>
#include <system.hpp>

#include "Backend.hpp"
#include "camera/Camera.hpp"
#include "input/Keyboard.hpp"
#include "mesh/RectangularPrism.hpp"
#include "opengl.hpp"
#include "render/Renderer.hpp"
#include "render/ShaderProgram.hpp"
#include "render/VertexArray.hpp"
#include "render/VertexBuffer.hpp"

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

  // glEnable(GL_PRIMITIVE_RESTART);
  // glPrimitiveRestartIndex(RESET_INDEX);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(opengl_error_callback, 0);
}

void Backend::run() {

  int width = 680, height = 460;

  init(width, height);

  Vec3 lightColor{1.0f, 1.0f, 1.0f};

  VertexArray lightVao(1);
  lightVao.generate();
  lightVao.bind();
  VertexBuffer lightVbo(2);
  lightVbo.generate();
  lightVbo.bind(BindType::ARRAY, 0);
  RectangularPrism light(lightColor, Vec3{-2.0f, 0.0f, 2.0f});
  lightVbo.setArrayBuffer(light.vertices.get(), light.size, RGB);
  lightVbo.bind(BindType::ELEMENT, 1);
  lightVbo.setElementBuffer(light.indices.get(), light.indicesSize);
  lightVbo.unbind();
  lightVao.unbind();

  ShaderProgram lightShader =
      ShaderProgram("light_vert.glsl", "light_frag.glsl");

  VertexArray objectVao(1);
  objectVao.generate();
  objectVao.bind();
  VertexBuffer vbo(2);
  vbo.generate();
  vbo.bind(BindType::ARRAY, 0);
  // Texture texture(1);
  // texture.generate();
  // texture.bind(TEXTURE2D);
  // texture.setTextureData("rock_wall_tileset.png");
  // texture.unbind();
  RectangularPrism rectangularPrism;
  vbo.setArrayBuffer(rectangularPrism.vertices.get(), rectangularPrism.size,
                     RGB);
  vbo.bind(BindType::ELEMENT, 1);
  vbo.setElementBuffer(rectangularPrism.indices.get(),
                       rectangularPrism.indicesSize);
  vbo.unbind();
  objectVao.unbind();

  ShaderProgram objectShader =
      ShaderProgram("object_vert.glsl", "object_frag.glsl");

  VertexArray baseVao(1);
  baseVao.generate();

  ShaderProgram gridShader = ShaderProgram("grid_vert.glsl", "grid_frag.glsl");

  Camera camera({10.0f, 10.0f, 10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 1.0f});
  float zNear = 0.01f;
  float zFar = 100.0f;
  Mat4 model = scale(Mat4(1.0f), Vec3(0.5f, 0.5f, 0.5f));
  Mat4 projection =
      perspective(radians(10.0f), (float)width / (float)height, zNear, zFar);

  gridShader.useProgram();
  gridShader.setUniform("zNear", zNear);
  gridShader.setUniform("zFar", zFar);
  gridShader.setUniform("model", model);
  gridShader.setUniform("projection", projection);
  gridShader.unuseProgram();

  objectShader.useProgram();
  objectShader.setUniform("lightColor", lightColor);
  objectShader.setUniform("zNear", zNear);
  objectShader.setUniform("zFar", zFar);
  objectShader.setUniform("model", model);
  objectShader.setUniform("projection", projection);
  objectShader.unuseProgram();

  lightShader.useProgram();
  lightShader.setUniform("zNear", zNear);
  lightShader.setUniform("zFar", zFar);
  lightShader.setUniform("model", model);
  lightShader.setUniform("projection", projection);
  lightShader.unuseProgram();

  float deltaTime = 0.0f, lastFrame = 0.0f;

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    Keyboard::processInput(window, camera, deltaTime);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    gridShader.useProgram();
    gridShader.setUniform("view", camera.getView());

    Renderer::enableAlphaBlending();
    Renderer::render(&baseVao, NULL, Render::TRIANGLES, 6, Render::ARRAY);
    Renderer::disableAlphaBlending();

    objectShader.useProgram();
    objectShader.setUniform("view", camera.getView());

    Renderer::enableDepthTesting();
    Renderer::render(&objectVao, NULL, Render::TRIANGLES, 36, Render::ELEMENT);
    Renderer::disableDepthTesting();

    lightShader.useProgram();
    lightShader.setUniform("view", camera.getView());

    Renderer::enableDepthTesting();
    Renderer::render(&lightVao, NULL, Render::TRIANGLES, 36, Render::ELEMENT);
    Renderer::disableDepthTesting();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  baseVao.destroy();
  objectVao.destroy();
  lightVao.destroy();
  objectShader.destroy();
  gridShader.destroy();

  glfwTerminate();
}
